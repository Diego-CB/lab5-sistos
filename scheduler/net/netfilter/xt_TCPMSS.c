/* Kernel module to match TCP MSS values. */

/* Copyright (C) 2000 Marc Boucher <marc@mbsi.ca>
 * Portions (C) 2005 by Harald Welte <laforge@netfilter.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/skbuff.h>
#include <net/tcp.h>

#include <linux/netfilter/xt_tcpmss.h>
#include <linux/netfilter/x_tables.h>

#include <linux/netfilter_ipv4/ip_tables.h>
#include <linux/netfilter_ipv6/ip6_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marc Boucher <marc@mbsi.ca>");
MODULE_DESCRIPTION("iptables TCP MSS match module");
MODULE_ALIAS("ipt_tcpmss");
MODULE_ALIAS("ip6t_tcpmss");

static bool
match(const struct sk_buff *skb,
      const struct net_device *in,
      const struct net_device *out,
      const struct xt_match *match,
      const void *matchinfo,
      int offset,
      unsigned int protoff,
      bool *hotdrop)
{
	const struct xt_tcpmss_match_info *info = matchinfo;
	struct tcphdr _tcph, *th;
	/* tcp.doff is only 4 bits, ie. max 15 * 4 bytes */
	u8 _opt[15 * 4 - sizeof(_tcph)], *op;
	unsigned int i, optlen;

	/* If we don't have the whole header, drop packet. */
	th = skb_header_pointer(skb, protoff, sizeof(_tcph), &_tcph);
	if (th == NULL)
		goto dropit;

	/* Malformed. */
	if (th->doff*4 < sizeof(*th))
		goto dropit;

	optlen = th->doff*4 - sizeof(*th);
	if (!optlen)
		goto out;

	/* Truncated options. */
	op = skb_header_pointer(skb, protoff + sizeof(*th), optlen, _opt);
	if (op == NULL)
		goto dropit;

	for (i = 0; i < optlen; ) {
		if (op[i] == TCPOPT_MSS
		    && (optlen - i) >= TCPOLEN_MSS
		    && op[i+1] == TCPOLEN_MSS) {
			u_int16_t mssval;

			mssval = (op[i+2] << 8) | op[i+3];

			return (mssval >= info->mss_min &&
				mssval <= info->mss_max) ^ info->invert;
		}
		if (op[i] < 2)
			i++;
		else
			i += op[i+1] ? : 1;
	}
out:
	return info->invert;

dropit:
	*hotdrop = true;
	return false;
}

static struct xt_match xt_tcpmss_match[] __read_mostly = {
	{
		.name		= "tcpmss",
		.family		= AF_INET,
		.match		= match,
		.matchsize	= sizeof(struct xt_tcpmss_match_info),
		.proto		= IPPROTO_TCP,
		.me		= THIS_MODULE,
	},
	{
		.name		= "tcpmss",
		.family		= AF_INET6,
		.match		= match,
		.matchsize	= sizeof(struct xt_tcpmss_match_info),
		.proto		= IPPROTO_TCP,
		.me		= THIS_MODULE,
	},
};

static int __init xt_tcpmss_init(void)
{
	return xt_register_matches(xt_tcpmss_match,
				   ARRAY_SIZE(xt_tcpmss_match));
}

static void __exit xt_tcpmss_fini(void)
{
	xt_unregister_matches(xt_tcpmss_match, ARRAY_SIZE(xt_tcpmss_match));
}

module_init(xt_tcpmss_init);
module_exit(xt_tcpmss_fini);
		return 0;
		}
	}

	/*
	 * MSS Option not found ?! add it..
	 */
	if (skb_tailroom(skb) < TCPOLEN_MSS) {
		if (pskb_expand_head(skb, 0,
				     TCPOLEN_MSS - skb_tailroom(skb),
				     GFP_ATOMIC))
			return -1;
		tcph = (struct tcphdr *)(skb_network_header(skb) + tcphoff);
	}

	skb_put(skb, TCPOLEN_MSS);

	opt = (u_int8_t *)tcph + sizeof(struct tcphdr);
	memmove(opt + TCPOLEN_MSS, opt, tcplen - sizeof(struct tcphdr));

	nf_proto_csum_replace2(&tcph->check, skb,
			       htons(tcplen), htons(tcplen + TCPOLEN_MSS), 1);
	opt[0] = TCPOPT_MSS;
	opt[1] = TCPOLEN_MSS;
	opt[2] = (newmss & 0xff00) >> 8;
	opt[3] = newmss & 0x00ff;

	nf_proto_csum_replace4(&tcph->check, skb, 0, *((__be32 *)opt), 0);

	oldval = ((__be16 *)tcph)[6];
	tcph->doff += TCPOLEN_MSS/4;
	nf_proto_csum_replace2(&tcph->check, skb,
				oldval, ((__be16 *)tcph)[6], 0);
	return TCPOLEN_MSS;
}

static unsigned int
xt_tcpmss_target4(struct sk_buff *skb,
		  const struct net_device *in,
		  const struct net_device *out,
		  unsigned int hooknum,
		  const struct xt_target *target,
		  const void *targinfo)
{
	struct iphdr *iph = ip_hdr(skb);
	__be16 newlen;
	int ret;

	ret = tcpmss_mangle_packet(skb, targinfo, iph->ihl * 4,
				   sizeof(*iph) + sizeof(struct tcphdr));
	if (ret < 0)
		return NF_DROP;
	if (ret > 0) {
		iph = ip_hdr(skb);
		newlen = htons(ntohs(iph->tot_len) + ret);
		nf_csum_replace2(&iph->check, iph->tot_len, newlen);
		iph->tot_len = newlen;
	}
	return XT_CONTINUE;
}

#if defined(CONFIG_IP6_NF_IPTABLES) || defined(CONFIG_IP6_NF_IPTABLES_MODULE)
static unsigned int
xt_tcpmss_target6(struct sk_buff *skb,
		  const struct net_device *in,
		  const struct net_device *out,
		  unsigned int hooknum,
		  const struct xt_target *target,
		  const void *targinfo)
{
	struct ipv6hdr *ipv6h = ipv6_hdr(skb);
	u8 nexthdr;
	int tcphoff;
	int ret;

	nexthdr = ipv6h->nexthdr;
	tcphoff = ipv6_skip_exthdr(skb, sizeof(*ipv6h), &nexthdr);
	if (tcphoff < 0)
		return NF_DROP;
	ret = tcpmss_mangle_packet(skb, targinfo, tcphoff,
				   sizeof(*ipv6h) + sizeof(struct tcphdr));
	if (ret < 0)
		return NF_DROP;
	if (ret > 0) {
		ipv6h = ipv6_hdr(skb);
		ipv6h->payload_len = htons(ntohs(ipv6h->payload_len) + ret);
	}
	return XT_CONTINUE;
}
#endif

#define TH_SYN 0x02

/* Must specify -p tcp --syn */
static inline bool find_syn_match(const struct xt_entry_match *m)
{
	const struct xt_tcp *tcpinfo = (const struct xt_tcp *)m->data;

	if (strcmp(m->u.kernel.match->name, "tcp") == 0 &&
	    tcpinfo->flg_cmp & TH_SYN &&
	    !(tcpinfo->invflags & XT_TCP_INV_FLAGS))
		return true;

	return false;
}

static bool
xt_tcpmss_checkentry4(const char *tablename,
		      const void *entry,
		      const struct xt_target *target,
		      void *targinfo,
		      unsigned int hook_mask)
{
	const struct xt_tcpmss_info *info = targinfo;
	const struct ipt_entry *e = entry;

	if (info->mss == XT_TCPMSS_CLAMP_PMTU &&
	    (hook_mask & ~((1 << NF_IP_FORWARD) |
			   (1 << NF_IP_LOCAL_OUT) |
			   (1 << NF_IP_POST_ROUTING))) != 0) {
		printk("xt_TCPMSS: path-MTU clamping only supported in "
		       "FORWARD, OUTPUT and POSTROUTING hooks\n");
		return false;
	}
	if (IPT_MATCH_ITERATE(e, find_syn_match))
		return true;
	printk("xt_TCPMSS: Only works on TCP SYN packets\n");
	return false;
}

#if defined(CONFIG_IP6_NF_IPTABLES) || defined(CONFIG_IP6_NF_IPTABLES_MODULE)
static bool
xt_tcpmss_checkentry6(const char *tablename,
		      const void *entry,
		      const struct xt_target *target,
		      void *targinfo,
		      unsigned int hook_mask)
{
	const struct xt_tcpmss_info *info = targinfo;
	const struct ip6t_entry *e = entry;

	if (info->mss == XT_TCPMSS_CLAMP_PMTU &&
	    (hook_mask & ~((1 << NF_IP6_FORWARD) |
			   (1 << NF_IP6_LOCAL_OUT) |
			   (1 << NF_IP6_POST_ROUTING))) != 0) {
		printk("xt_TCPMSS: path-MTU clamping only supported in "
		       "FORWARD, OUTPUT and POSTROUTING hooks\n");
		return false;
	}
	if (IP6T_MATCH_ITERATE(e, find_syn_match))
		return true;
	printk("xt_TCPMSS: Only works on TCP SYN packets\n");
	return false;
}
#endif

static struct xt_target xt_tcpmss_reg[] __read_mostly = {
	{
		.family		= AF_INET,
		.name		= "TCPMSS",
		.checkentry	= xt_tcpmss_checkentry4,
		.target		= xt_tcpmss_target4,
		.targetsize	= sizeof(struct xt_tcpmss_info),
		.proto		= IPPROTO_TCP,
		.me		= THIS_MODULE,
	},
#if defined(CONFIG_IP6_NF_IPTABLES) || defined(CONFIG_IP6_NF_IPTABLES_MODULE)
	{
		.family		= AF_INET6,
		.name		= "TCPMSS",
		.checkentry	= xt_tcpmss_checkentry6,
		.target		= xt_tcpmss_target6,
		.targetsize	= sizeof(struct xt_tcpmss_info),
		.proto		= IPPROTO_TCP,
		.me		= THIS_MODULE,
	},
#endif
};

static int __init xt_tcpmss_init(void)
{
	return xt_register_targets(xt_tcpmss_reg, ARRAY_SIZE(xt_tcpmss_reg));
}

static void __exit xt_tcpmss_fini(void)
{
	xt_unregister_targets(xt_tcpmss_reg, ARRAY_SIZE(xt_tcpmss_reg));
}

module_init(xt_tcpmss_init);
module_exit(xt_tcpmss_fini);
