/*
 * Copyright (c) 1982, 1988 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)saio.h	7.7 (Berkeley) %G%
 */

#include "saioctl.h"
#include "saerrno.h"

#define	UNIX	"/vmunix"
#define	NULL	0

/*
 * Io block: includes an inode, cells for the use of seek, etc.,
 * and a buffer.
 */
struct iob {
	int	i_flgs;		/* see F_ below */
	int	i_adapt;	/* adapter */
	int	i_ctlr;		/* controller */
	int	i_unit;		/* pseudo device unit */
	int	i_part;		/* disk partition */
	daddr_t	i_boff;		/* block offset on device */
	struct	inode i_ino;	/* inode, if file */
	daddr_t	i_cyloff;	/* cylinder offset on device */
	off_t	i_offset;	/* seek offset in file */
	daddr_t	i_bn;		/* 1st block # of next read */
	char	*i_ma;		/* memory address of i/o buffer */
	int	i_cc;		/* character count of transfer */
	int	i_error;	/* error # return */
	int	i_errcnt;	/* error count for driver retries */
	int	i_errblk;	/* block # in error for error reporting */
	char	i_buf[MAXBSIZE];/* i/o buffer */
	union {
		struct fs ui_fs;	/* file system super block info */
		char dummy[SBSIZE];
	} i_un;
};
#define	i_fs	i_un.ui_fs

#define	F_READ		0x1	/* file opened for reading */
#define	F_WRITE		0x2	/* file opened for writing */
#define	F_ALLOC		0x4	/* buffer allocated */
#define	F_FILE		0x8	/* file instead of device */
#define	F_NBSF		0x10	/* no bad sector forwarding */
#define	F_ECCLM		0x20	/* limit # of bits in ecc correction */
#define	F_SSI		0x40	/* set skip sector inhibit */
#define	F_SEVRE		0x80	/* Severe burnin (no retries, no ECC) */

/* io types */
#define	F_RDDATA	0x0100	/* read data */
#define	F_WRDATA	0x0200	/* write data */
#define	F_HDR		0x0400	/* include header on next i/o */
#define	F_CHECK		0x0800	/* perform check of data read/write */
#define	F_HCHECK	0x1000	/* perform check of header and data */

#define	F_TYPEMASK	0xff00

/*
 * Request codes. Must be the same as F_XXX above
 */
#define	READ	F_READ
#define	WRITE	F_WRITE

/*
 * Lseek call.
 */
#define	L_SET		0	/* absolute offset */

/*
 * Device switch.
 */
struct devsw {
	char	*dv_name;
	int	(*dv_strategy)();
	int	(*dv_open)();
	int	(*dv_close)();
	int	(*dv_ioctl)();
};

extern struct devsw devsw[];	/* device array */
extern int ndevs;		/* number of elements in devsw[] */

#ifdef COMPAT_42
/*
 * Old drive description table.
 * still used by some drivers for now.
 */
struct st {
	short	nsect;		/* # sectors/track */
	short	ntrak;		/* # tracks/surfaces/heads */
	short	nspc;		/* # sectors/cylinder */
	short	ncyl;		/* # cylinders */
	short	*off;		/* partition offset table (cylinders) */
};
#endif

#define	NFILES	4
extern struct	iob iob[NFILES];
