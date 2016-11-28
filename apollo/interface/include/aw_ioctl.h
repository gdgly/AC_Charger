/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief Generic ioctl commands
 *
 * \internal
 * \par modification history
 * - 1.10 14-01-17  zen, move ioctl function code to platform
 * - 1.00 12-10-25  orz, simple implementation from VxWorks and linux
 * \endinternal
 */

#ifndef __AW_IOCTL_H
#define __AW_IOCTL_H

/*
 * \name generic ioctl function codes
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif


#include "aw_ioctl_generic.h"

/******************************************************************************/

/*
 * \name ioctl types
 *
 * apollo platform use type number 0~99, the rest is for user use,
 * max type number is 255
 * @{
 */
#define AW_IOC_TYPE_FIO     0   /**< \brief File ioctl command type */
#define AW_IOC_TYPE_TIO     1   /**< \brief TTY ioctl command type */
#define AW_IOC_TYPE_SIO     2   /**< \brief serial device ioctl command type */

#define AW_IOC_TYPE_USER    100

/** @} */

/*
 * \name file stream ioctl function codes
 * @{
 */

#define _AW_FIO(nr)            __AW_IO(AW_IOC_TYPE_FIO, nr)
#define _AW_FIOR(nr, size)     __AW_IOR(AW_IOC_TYPE_FIO, nr, size)
#define _AW_FIOW(nr, size)     __AW_IOW(AW_IOC_TYPE_FIO, nr, size)
#define _AW_FIOWR(nr, size)    __AW_IOWR(AW_IOC_TYPE_FIO, nr, size)

#define AW_FIONREAD    _AW_FIOR(1, int) /**< get num chars available to read */
#define AW_FIOFLUSH    _AW_FIO (2)      /**< flush any chars in buffers */
#define AW_FIOOPTIONS  _AW_FIOW(3, int) /**< set options (FIOSETOPTIONS) */
#define AW_FIOBAUDRATE _AW_FIOW(4, int) /**< set serial baud rate */

#define AW_FIODISKFORMAT   _AW_FIO(5)   /**< format disk */
#define AW_FIODISKINIT     _AW_FIO(6)   /**< format disk */

#define AW_FIOSEEK     _AW_FIOW(7, int) /**< set current file char position */
#define AW_FIOWHERE    _AW_FIOR(8, int) /**< get current file char position */
#define AW_FIODIRENTRY _AW_FIOR(9, int) /**< return a directory entry */
#define AW_FIORENAME   _AW_FIOW(10,int) /**< rename a directory entry */

#define AW_FIONWRITE   _AW_FIOR(12,int) /**< get num chars still to be written */

#define AW_FIOCANCEL   _AW_FIO(14) /**< cancel read or write on the device */

#define AW_FIONBIO     _AW_FIO(16) /**< set non-blocking I/O; SOCKETS ONLY!*/

#define AW_FIONMSGS    _AW_FIOR(17, int) /**< return num msgs in pipe */

#define AW_FIOISATTY   _AW_FIOR(20, int) /**< is a tty */
#define AW_FIOSYNC     _AW_FIO (21)      /**< sync to disk */

#define AW_FIORBUFSET  _AW_FIOW(24, int) /**< alter the size of read buffer  */
#define AW_FIOWBUFSET  _AW_FIOW(25, int) /**< alter the size of write buffer */
#define AW_FIORFLUSH   _AW_FIO (26)      /**< flush any chars in read buffers */
#define AW_FIOWFLUSH   _AW_FIO (27)      /**< flush any chars in write buffers */
#define AW_FIOSELECT   _AW_FIO (28)     /**< wake up process in select on I/O */
#define AW_FIOUNSELECT _AW_FIO (29)     /**< wake up process in select on I/O */
#define AW_FIONFREE    _AW_FIOR(30, int)/**< get free byte count on device */
#define AW_FIOMKDIR    _AW_FIOW(31, int)/**< create a directory */
#define AW_FIORMDIR    _AW_FIOW(32, int)/**< remove a directory */

#define AW_FIOREADDIR  _AW_FIOR(37, int)/**< read a directory entry (POSIX) */

#define AW_FIOTRUNC    _AW_FIOW(42, int)/**< truncate file to specified length(POSIX) */
#define AW_FIOUTIME    _AW_FIOW(43, int)/**< set file access and modification times(POSIX) */
#define AW_FIOCHMOD    _AW_FIOW(44, int)/**< change mode of a file(POSIX) */

#define AW_FIOFSTATFSGET   _AW_FIOR(46, int) /**< get FS status info */

#define AW_FIODATASYNC     _AW_FIO(57)      /* sync to I/O data integrity */

#define AW_FIOLINK         _AW_FIO(58)      /* create a link */
#define AW_FIOUNLINK       _AW_FIO(59)      /* remove a link */

#define AW_FIOSTATGET      _AW_FIOR(64, int) /**< get stat info (POSIX) */
#define AW_FIOFSTATGET     _AW_FIOR(66, int) /**< get fstat info (POSIX) */


/** @} */

/******************************************************************************/

/**
 * \name serial device ioctl function codes
 * @{
 */
#define _AW_TIO(nr)        __AW_IO(AW_IOC_TYPE_TIO, nr)
#define _AW_TIOR(nr, size) __AW_IOR(AW_IOC_TYPE_TIO, nr, size)
#define _AW_TIOW(nr, size) __AW_IOW(AW_IOC_TYPE_TIO, nr, size)

#define AW_TIOPROTOHOOK    _AW_TIOW(1, int)   /**< specify protocol hook routine */
#define AW_TIOPROTOARG     _AW_TIOW(2, int)   /**< specify protocol argument */
#define AW_TIOGETOPTIONS   _AW_TIOR(3, int)   /**< get serial device options */
#define AW_TIOSETOPTIONS   _AW_TIOW(4, int)   /**< set serial device options */
#define AW_TIOISATTY       _AW_TIOR(5, int)   /**< is a tty */

#define AW_TIOCBAUDRATE    _AW_TIOW(6, int)   /**< \brief set serial baud rate */
#define AW_TIOCGRS485      _AW_TIOR(7, int)   /**< \brief Get serial RS-485 options */
#define AW_TIOCSRS485      _AW_TIOW(8, int)   /**< \brief Set serial RS-485 options */

#define AW_TIOCRDTIMEOUT   _AW_TIOW(9, int)   /**< \brief set serial read timeout */
#define AW_TIOCGSTATUS	   _AW_TIOW(10, int)  /**< \brief get serial status */


/**
 * \name options to AW_TIOCSRS485 , bitwise or'ed together
 * @{
 */
#define RS485_ENABLE          0x1     /* enable rs485 mode */
#define RS485_DISABLE         0x0     /* disable rs485 mode */

/**
 * \name status return by AW_TIOCGSTATUS
 * @{
 */
#define SERIAL_IDLE          0x0     /* serial device idle */
#define SERIAL_BUSY          0x1     /* serial device busy */




/******************************************************************************/
/**< \brief structure for rename and move */
struct rename_struct {
    const char *old_name;
    const char *new_name;
};

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* __AW_IOCTL_H */

/* end of file */
