#ifndef __LIMITS_H
#define __LIMITS_H

#define	CHAR_BIT	8

#define	SCHAR_MIN	(-128)
#define	SCHAR_MAX	127

#define	UCHAR_MAX	255

#define	CHAR_MIN	SCHAR_MIN
#define	CHAR_MAX	SCHAR_MAX

#define	MB_LEN_MAX	1

#define	SHRT_MIN	(-32768)
#define	SHRT_MAX	32767

#define	USHRT_MAX	65535

#define	INT_MIN 	(- INT_MAX - 1)
#define	INT_MAX 	2147483647

#define	UINT_MAX 	4294967295

#define	LONG_MIN	INT_MIN
#define	LONG_MAX	INT_MAX
 
#define ULONG_MAX	UINT_MAX

#define	LLONG_MIN	0
#define	LLONG_MAX	0
#define	ULLONG_MAX	0



#endif