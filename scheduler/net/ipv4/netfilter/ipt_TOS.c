/* Kernel module to match TOS values. */

/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2004 Netfilter Core Team <coreteam@netfilter.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/ip.h>
#include <linux/module.h>
#include <linux/skbuff.h>

#include <linux/netfilter_ipv4/ipt_tos.h>
#include <linux/netfilter/x_tables.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("iptables TOS match module");

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
	const struct ipt_tos_info *info = matchinfo;

	return (ip_hdr(skb)->tos == info->tos) ^ info->invert;
}

static struct xt_match tos_match __read_mostly = {
	.name		= "tos",
	.family		= AF_INET,
	.match		= match,
	.matchsize	= sizeof(struct ipt_tos_info),
	.me		= THIS_MODULE,
};

static int __init ipt_multiport_init(void)
{
	return xt_register_match(&tos_match);
}

static void __exit ipt_multiport_fini(void)
{
	xt_unregister_match(&tos_match);
}

module_init(ipt_multiport_init);
module_exit(ipt_multiport_fini);

static bool
checkentry(const char *tablename,
	   const void *e_void,
	   const struct xt_target *target,
	   void *targinfo,
	   unsigned int hook_mask)
{
	const u_int8_t tos = ((struct ipt_tos_target_info *)targinfo)->tos;

	if (tos != IPTOS_LOWDELAY
	    && tos != IPTOS_THROUGHPUT
	    && tos != IPTOS_RELIABILITY
	    && tos != IPTOS_MINCOST
	    && tos != IPTOS_NORMALSVC) {
		printk(KERN_WARNING "TOS: bad tos value %#x\n", tos);
		return false;
	}
	return true;
}

static struct xt_target ipt_tos_reg __read_mostly = {
	.name		= "TOS",
	.family		= AF_INET,
	.target		= target,
	.targetsize	= sizeof(struct ipt_tos_target_info),
	.table		= "mangle",
	.checkentry	= checkentry,
	.me		= THIS_MODULE,
};

static int __init ipt_tos_init(void)
{
	return xt_register_target(&ipt_tos_reg);
}

static void __exit ipt_tos_fini(void)
{
	xt_unregister_target(&ipt_tos_reg);
}

module_init(ipt_tos_init);
module_exit(ipt_tos_fini);
