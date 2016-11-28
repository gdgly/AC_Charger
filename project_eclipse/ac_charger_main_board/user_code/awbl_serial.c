/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief 串口通讯标准接口
 *
 * \internal
 * \par modification history
 * - 1.00 12-10-30  orz, first implementation
 * - 1.00 15-06-20  deo, add aw_serdev_remove
 * \endinternal
 */
#include "aw_common.h"

#include "aw_serial.h"
#include "driver/serial/awbl_serial_private.h"

#include "awbus_lite.h"
#include <string.h> /* for memset() */

/**
 * \addtogroup grp_aw_serial_if
 * @{
 */
#define com_to_serial(com)  (&g_serial_devices[com])

/******************************************************************************/
extern struct aw_serial g_serial_devices[];
extern aw_const int     g_num_serial_devices;

/**
 * \brief transmitter startup routine
 *
 * Call interrupt level character output routine.
 */
aw_local void __serdev_startup (struct aw_tydev *p_tydev)
{
    struct aw_serial *p_ser = (struct aw_serial *)p_tydev;

    aw_sio_tx_startup(p_ser->p_siochan);
}

/**
 * \brief initialize a aw_sio device for a serial channel
 *
 * This routine initialize a device on a specified serial channel.  Each channel
 * to be used should have exactly one device associated with it by calling
 * this routine.
 * \param p_siochan pointer to core driver structure
 *
 * \return AW_OK, or AW_ERROR if the driver is not installed, or the
 * device already exists.
 */
aw_local aw_err_t __serdev_init(struct aw_serial   *p_ser,
                                struct aw_sio_chan *p_siochan,
                                char               *p_rdbuf,
                                int                 rd_buf_size,
                                char               *p_wrbuf,
                                int                 wr_buf_size)
{
    if ((p_siochan == (struct aw_sio_chan *)AW_ERROR) || (p_siochan == NULL)) {
        return (AW_ERROR);
    }

    /* initialize the ty descriptor */

    if (AW_OK != aw_tydev_init(&p_ser->tydev,
                               p_rdbuf,
                               rd_buf_size,
                               p_wrbuf,
                               wr_buf_size,
                               __serdev_startup)) {
        return (AW_ERROR);
    }

    /* initialize the SIO_CHAN structure */

    p_ser->p_siochan = p_siochan;

    aw_sio_callback_install(p_siochan,
                            AW_SIO_CALLBACK_GET_TX_CHAR,
                            (int (*)(void *))aw_ty_int_tx,
                            (void *)(&p_ser->tydev));

    aw_sio_callback_install(p_siochan,
                            AW_SIO_CALLBACK_PUT_RCV_CHAR,
                            (int (*)(void *))aw_ty_int_rd,
                            (void *)(&p_ser->tydev));

    /* start the device cranking */
    aw_sio_ioctl(p_siochan, SIO_MODE_SET, (void *)SIO_MODE_INT);

    return AW_OK;
}

/******************************************************************************/
aw_err_t aw_serdev_init (int    com,
                         char  *p_rdbuf,
                         size_t rd_buf_size,
                         char  *p_wrbuf,
                         size_t wr_buf_size)
{
    struct aw_sio_chan_info chaninfo;
    struct aw_serial       *p_ser;
    aw_err_t                err;

    if (com >= g_num_serial_devices) {
        return -EINVAL;
    }

    /* get sio channel */
    chaninfo.chan_no = com;
    chaninfo.p_chan  = NULL;
    err = awbl_alldevs_method_run(AWBL_METHOD_CALL(aw_sio_chan_get), &chaninfo);
    if (AW_OK != err) {
        return -ENODEV;
    }

    p_ser = com_to_serial(com);
    err = __serdev_init(p_ser,
                        chaninfo.p_chan,
                        p_rdbuf,
                        rd_buf_size,
                        p_wrbuf,
                        wr_buf_size);
    if (AW_OK != err) {
        return -AW_ERROR;
    }
    chaninfo.p_chan   = NULL;
    err = awbl_alldevs_method_run(AWBL_METHOD_CALL(aw_sio_chan_connect),
                                  &chaninfo);
    if (AW_OK != err) {
        return -AW_ERROR;
    }
    p_ser->p_siochan = chaninfo.p_chan;

    return AW_OK;
}

/******************************************************************************/
void aw_serial_init2 (void)
{
    aw_tylib_init(85, 50, 20);

    memset(g_serial_devices,
           0,
           sizeof(struct aw_serial) * g_num_serial_devices);
}
/******************************************************************************/
aw_err_t aw_serdev_remove (int com)
{
	struct aw_serial *p_ser;

    if (com >= g_num_serial_devices) {
        return -EINVAL;
    }

    p_ser = com_to_serial(com);
    p_ser->p_siochan = NULL;
    return aw_tydev_remove(&p_ser->tydev);
}

/******************************************************************************/
aw_err_t aw_serial_ioctl (int com, int request, void *p_arg)
{
    aw_err_t          err;
    struct aw_serial *p_ser;

    if (com >= g_num_serial_devices) {
        return -EINVAL;
    }
    p_ser = com_to_serial(com);
    if (NULL == p_ser->p_siochan) {
        return -ENODEV;
    }

    err = aw_sio_ioctl(p_ser->p_siochan, request, p_arg);

    if (err == -ENOSYS) {
        return (aw_ty_ioctl(&p_ser->tydev, request, p_arg));
    }

    return (err);
}

/******************************************************************************/
ssize_t aw_serial_write (int com, const char *p_buffer, size_t nbytes)
{
    struct aw_serial *p_ser;

    if (com >= g_num_serial_devices) {
        return -EINVAL;
    }
    p_ser = com_to_serial(com);
    if (NULL == p_ser->p_siochan) {
        return -ENODEV;
    }

    return aw_ty_write(&p_ser->tydev, p_buffer, nbytes);
}

/******************************************************************************/
ssize_t aw_serial_read (int com, char *p_buffer, size_t maxbytes)
{
    struct aw_serial *p_ser;
    char              *p_buf = (char *)p_buffer;
    ssize_t            idx   = 0, len;

    if (com >= g_num_serial_devices) {
        return -EINVAL;
    }
    p_ser = com_to_serial(com);
    if (NULL == p_ser->p_siochan) {
        return -ENODEV;
    }

    while (idx < maxbytes) {
        if ((len = aw_ty_read(&p_ser->tydev, &p_buf[idx], maxbytes - idx)) < 0) {
            break;
        }
        idx += len;
    }
    return idx;
}

/******************************************************************************/
ssize_t aw_serial_poll_write (int com, const char *p_buffer, size_t nbytes)
{
    struct aw_serial *p_ser;
    size_t            len;
    char              ch;

    if (com >= g_num_serial_devices) {
        return -EINVAL;
    }
    p_ser = com_to_serial(com);
    if (NULL == p_ser->p_siochan) {
        return -ENODEV;
    }

    len = nbytes;

    while (len-- > 0) {
        ch = *p_buffer++;
        while (-EAGAIN == aw_sio_poll_output(p_ser->p_siochan, ch)) {
        }
    }

    return nbytes;
}

/******************************************************************************/
ssize_t aw_serial_poll_read (int com, char *p_buffer, size_t maxbytes)
{
    struct aw_serial *p_ser;
    size_t            len;

    if (com >= g_num_serial_devices) {
        return -EINVAL;
    }
    p_ser = com_to_serial(com);
    if (NULL == p_ser->p_siochan) {
        return -ENODEV;
    }

    len = maxbytes;

    while (len-- > 0) {
        while (-EAGAIN == aw_sio_poll_input(p_ser->p_siochan, p_buffer)) {
        }
        p_buffer++;
    }

    return maxbytes;
}

/** @} */

/* end of file */
