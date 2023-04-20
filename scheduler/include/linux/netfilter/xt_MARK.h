#ifndef _XT_MARK_H
#define _XT_MARK_H

struct xt_mark_info {
    unsigned long mark, mask;
    u_int8_t invert;
};

#endif /*_XT_MARK_H*/

enum {
	XT_MARK_SET=0,
	XT_MARK_AND,
	XT_MARK_OR,
};

struct xt_mark_target_info_v1 {
	unsigned long mark;
	u_int8_t mode;
};

#endif /*_XT_MARK_H_target */
