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
 * \brief AWBus SPI���߽ӿ�ͷ�ļ�
 *
 * ʹ�ñ�ģ����Ҫ��������ͷ�ļ���
 * \code
 * #include "awbl_spibus.h"
 * \endcode
 * ��ģ��Ϊ SPI ���ߵľ����ʵ��
 *
 * \internal
 * \par modification history:
 * - 1.00 12-11-19  zen, first implementation
 * \endinternal
 */

#ifndef __AWBL_SPIBUS_H
#define __AWBL_SPIBUS_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "aw_list.h"
#include "aw_spi.h"         /* ͨ��SPI�ӿ��ļ� */
#include "aw_sem.h"

/**
 * \name SPI �������������Ʊ�־
 * @{
  */
#define AWBL_SPI_MASTER_HALF_DUPLEX AW_BIT(0)  /**< /brief ��֧��ȫ˫�� */
#define AWBL_SPI_MASTER_NO_RX       AW_BIT(1)  /**< /brief ��֧�ֻ������� */
#define AWBL_SPI_MASTER_NO_TX       AW_BIT(2)  /**< /brief ��֧�ֻ�����д */
/** @} */

/** \biref �õ�SPI�ӻ��豸�ĸ������� */
#define AWBL_SPI_PARENT_GET(p_dev) \
    ((struct awbl_spi_master *) \
        (((struct awbl_dev *)(p_dev))->p_parentbus->p_ctlr))

/** \biref �õ�SPI�ӻ��豸�ĸ���������� */
#define AWBL_SPI_PARENT_BUSID_GET(p_dev) \
        (((struct awbl_spi_master_devinfo *) \
            AWBL_DEVINFO_GET( \
                ((struct awbl_dev *)(p_dev))->p_parentbus->p_ctlr))->bus_index)

struct awbl_spi_master;

/** \biref AWBus SPI ���߿����� (SPI ����) �豸��Ϣ (ƽ̨���ò���) */
struct awbl_spi_master_devinfo {

    /** \brief ����������Ӧ�����߱�� */
    uint8_t     bus_index;
};

/** \biref AWBus SPI ���߿����� (SPI ����) �豸��Ϣ (�������ò���) */
struct awbl_spi_master_devinfo2 {

    /** \brief ������������(֧�ֵġ�SPIģʽ��֡��,�� aw_spi.h)  */
    uint16_t    features;

    /** \brief ������������(����SPI �������������Ʊ�־��) */
    uint16_t    flags;

    /** DMA ����������Ҫ��, ���������֧��DMA����Ļ� */
    uint16_t    dma_alignment;

    /**
     * \brief ���ÿ�����ģʽ��ʱ�ӵȲ��� ( SPI �������ܶ�ε���)
     * \attention �ú��������ڴ���ʱ�����ã���Ҫֱ�Ӹ�����Щ�����ļĴ�����
     *            ������ƻ���ǰ���䡣
     */
    aw_err_t (*pfunc_setup)(struct awbl_spi_master *p_master,
                            aw_spi_device_t        *p_dev);

   /**
     * \brief ��������
     *
     * �ú�������Ҫ��ɫ�������Ϣ�������С���ǰû�дӶ������Ƴ��Ĳ����������κ�
     * ��������������� aw_spi_device ��˵���ö����Ǵ����FIFO��
     *
     * �������Ľ�ɫ���Ǵ���������Ϣ���У�ѡ��ƬѡȻ�������ݡ�����ж�� SPI
     * ���豸��I/O���е��ٲ��㷨��δָ���� (���磬ѭ����FIFO�����ȼ���������
     * ��ռ�ȵ�)��
     *
     * Ƭѡ��������Ϣ�Ĵ�������б�����Ч (���� aw_spi_transfer.cs_change != 0
     * Ӱ����Ƭѡ)��
     *
     * ��Ϣ����ʹ����ǰΪ���豸���� setup() �����õ�ʱ�Ӻ�SPIģʽ��
     */
    aw_err_t (*pfunc_xfer_startup)(struct awbl_spi_master *p_master);
};

/* \biref SPI bus �ӻ��豸����ע����Ϣ�ṹ�� */
typedef struct awbl_spi_drvinfo {
    struct awbl_drvinfo super;  /**< \brief �̳��� AWBus �豸������Ϣ */
} awbl_spi_drvinfo_t;

/** \brief AWBus SPI �����豸 (SPI�ӻ�) ʵ�� */
struct awbl_spi_device {
    struct awbl_dev super;          /**< \brief �̳��� AWBus �豸 */
    struct aw_spi_device spi_dev;   /**< \brief SPI �豸 */
};

/** \brief AWBus SPI ���߿����� (SPI����) ʵ�� */
struct awbl_spi_master {
    struct awbl_busctlr super;      /**< \brief �̳��� AWBus ���߿����� */
    struct awbl_spi_master *p_next; /**< \brief ָ����һ�� SPI ������ */


    /** \brief SPI �����������Ϣ (�������ò���) */
    const struct awbl_spi_master_devinfo2 *p_devinfo2;

    /** \brief �������� */
    aw_spinlock_isr_t dev_lock;

    /** \brief ������������ */
    AW_MUTEX_DECL(dev_mutex);

    /** \brief ����������־, 1-���߱����� 0-����δ������ */
    bool_t        bus_lock_flag;

    /** \brief SPI ��������Ϣ���� */
    struct aw_list_head msg_list;

    /** \brief ��Ϣ�ڴ����, aw_spi_write_then_read() ʹ�ô��ڴ� */
    struct aw_spi_message msg;

    /** \brief �����ڴ����, aw_spi_write_then_read() ʹ�ô��ڴ�  */
    struct aw_spi_transfer trans[2];
};

/** \brief ���������� */
#define AWBL_SPI_MASTER_LOCK(p_master) \
    aw_spinlock_isr_take(&((struct awbl_spi_master *)p_master)->dev_lock)

/** \brief ������������� */
#define AWBL_SPI_MASTER_UNLOCK(p_master) \
    aw_spinlock_isr_give(&((struct awbl_spi_master *)p_master)->dev_lock)

/**
 * \brief ���һ�� message �������������б�ĩβ
 * \attention ���ô˺�����������������
 */
aw_local aw_inline void awbl_spi_msg_in (struct awbl_spi_master *p_master,
                                         struct aw_spi_message  *p_msg)
{
    aw_list_add_tail((struct aw_list_head *)(&p_msg->ctlrdata),
                     &p_master->msg_list);
}

/**
 * \brief �ӿ����������б��ͷȡ��һ�� message
 * \attention ���ô˺�����������������
 */
aw_local aw_inline struct aw_spi_message *
    awbl_spi_msg_out (struct awbl_spi_master *p_master)
{
    if (aw_list_empty_careful(&p_master->msg_list)) {
        return NULL;
    } else {
        struct aw_list_head *p_node = p_master->msg_list.next;
        aw_list_del(p_node);
        return aw_list_entry(p_node, struct aw_spi_message, ctlrdata);
    }
}

/**
 * \brief ȡ��ָ���� message (�Ӷ������Ƴ��� message)
 *
 * ֻ����Ϣ��δ������ʱ�ſ��Ա�ȡ��
 *
 * \retval  AW_OK       �ɹ�
 * \retval  AW_ERROR    ʧ�ܣ�message���ڱ�����
 * \attention ���ô˺�����������������
 */
aw_local aw_inline aw_err_t awbl_spi_msg_cancel (struct aw_spi_message *p_msg)
{
    if ((p_msg->status == -ENOTCONN) ||
        (p_msg->status == -EISCONN)) {

        aw_list_del((struct aw_list_head *)p_msg->ctlrdata);
        return AW_OK;
    }

    return AW_ERROR;
}

/**
 * \brief �������������б��Ƿ�Ϊ��
 * \attention ���ô˺�����������������
 */
aw_local aw_inline int awbl_spi_msg_empty (struct awbl_spi_master *p_master)
{
    return aw_list_empty_careful(&p_master->msg_list);
}

/**
 * \brief AWBus SPI ����ģ���ʼ������
 *
 * \attention ������Ӧ���� awbus_lite_init() ֮��awbl_dev_init1() ֮ǰ����
 */
void awbl_spibus_init(void);

/**
 * \brief ���� AWBus SPI ����ʵ���Լ�ö�������ϵ��豸
 *
 * ���ӿ��ṩ�� AWBus SPI ���߿�����(�����豸)����ʹ��
 *
 */
aw_err_t awbl_spibus_create(struct awbl_spi_master *p_master);

/**
 * \brief ����SPI�豸�ṹ�����
 * \param p_dev         AWBus SPI�ӻ��豸ʵ��
 * \param bits_per_word �ִ�С��Ϊ0ʱʹ��Ĭ�ϵġ�8-bit�ִ�С��
 * \param mode          �豸ģʽ��־������SPIģʽ��־��
 * \param max_speed_hz  �豸֧�ֵ�����ٶ�
 * \param cs_pin        Ƭѡ���ű��(pfunc_cs ΪNULLʱ����������Ч)
 * \param pfunc_cs      Ƭѡ���ƺ���(��������Ϊ NULL ʱ�� cs_pin ������Ч)
 *
 * \par ����
 * �� awbl_spi_setup()
 */
aw_local aw_inline void awbl_spi_mkdev (struct awbl_spi_device *p_dev,
                                        uint8_t                 bits_per_word,
                                        uint16_t                mode,
                                        uint32_t                max_speed_hz,
                                        int                     cs_pin,
                                        void (*pfunc_cs)(aw_spi_device_t *p_dev,
                                                         int state))
{
    aw_spi_mkdev(&p_dev->spi_dev,
                 AWBL_SPI_PARENT_BUSID_GET(p_dev),
                 bits_per_word,
                 mode,
                 max_speed_hz,
                 cs_pin,
                 pfunc_cs);
}

/**
 * \brief ����SPI�ӻ��豸
 *
 * ���ӿ��ṩ�� AWBus SPI ���豸����ʹ��
 *
 * \attention ��SPI�ӻ��豸��ʹ��ǰ�������ȵ��ñ������������ã����籾��������
 *            ������һ��������ʹ�ô�SPI�ӻ�
 *
 * \param[in,out]   p_dev   SPI�ӻ��豸
 *
 * \retval   AW_OK      �ɹ�
 * \retval  -ENXIO      δ�ҵ�ָ����SPI����
 * \retval  -ENOTSUP    ĳЩ���Բ�֧��
 *
 * \par ʾ��
 * \code
 *
 * // ��ʼ���豸�����ṹ
 * awbl_spi_mkdev(p_dev,          // AWBus SPI �豸ʵ��
 *                8��             // �ִ�СΪ8-bit
 *                AW_SPI_MODE_0,  // SPI ģʽ0
 *                500000,         // ֧�ֵ�����ٶ� 500000 Hz
 *                PIO0_3,         // Ƭѡ����Ϊ PIO0_3
 *                NULL);          // ���Զ����Ƭѡ���ƺ���
 *
 * // �����豸
 * awbl_spi_setup(p_dev);
 *
 * \endcode
 */
aw_err_t awbl_spi_setup(struct awbl_spi_device *p_dev);

/**
 * \brief ������Ϣ���첽ģʽ
 *
 * ���ӿ��ṩ�� AWBus SPI ���豸����ʹ��
 *
 * ���첽�ķ�ʽ������Ϣ����Ϣ�Ĵ���״̬�ͽ����ӳ�� p_msg->status��
 * ��Ϣ�������(�ɹ������)ʱ��������� p_msg->pfunc_complete �����ݲ���
 * p_msg->p_arg��
 *
 * \param[in]       p_dev   AWBus SPI �豸ʵ��
 * \param[in,out]   p_msg   Ҫ�������Ϣ
 *
 * �����ķ���ֵ���£�
 * \retval  AW_OK       ��Ϣ�Ŷӳɹ����ȴ�����
 * \retval  -EINVAL     ��������
 *
 * �ɹ�����/���յ����ݸ�����ӳ�� p_msg->actual_length
 *
 * ��Ϣ�Ĵ���״̬�ͽ����ӳ�� p_msg->status ��
 *
 *      \li  -ENOTCONN       ��Ϣ��δ�Ŷ�
 *      \li  -EISCONN        ��Ϣ�����Ŷ�
 *      \li  -EINPROGRESS    ��Ϣ���ڱ�����
 * ����Ϊ��Ϣ������ϵĽ��
 *      \li  AW_OK           ���д���ɹ�����
 *      \li  -ENOTSUP        ��Ϣ��ĳ����������ò�֧��(���磬�ִ�С���ٶȵ�)
 *      \li  -ECANCELED      �����������������������Ϣ��ȡ�������Ժ�����
 *
 * \par ����
 * \code
 *  aw_spi_device_t   spi_dev;
 *  aw_spi_message_t  msg;
 *  aw_spi_transfer_t trans[3];
 *  uint8_t           txbuf[16];
 *  uint8_t           rxbuf[16];
 *
 *  // �����豸
 *  if (aw_spi_setup(&spi_dev) != AW_OK) {
 *      // �����豸ʧ��
 *  }
 *
 *  //  ��һ������,����16���ֽ�
 *  aw_spi_mktrans(&trans[0],       // ���������ṹ 0
 *                 &txbuf[0],       // ���ͻ�����
 *                 NULL,            // ���ջ���
 *                 16,              // ���͸���
 *                 0,               // cs_change �޸ı�
 *                 0,               // bpw ʹ��Ĭ������
 *                 0,               // udelay ����ʱ
 *                 0);              // speed ʹ��Ĭ��ֵ
 *
 *  //  �ڶ�������,����16���ֽ�
 *  aw_spi_mktrans(&trans[1],       // ���������ṹ 1
 *                 NULL,            // ���ͻ�����
 *                 &rxbuf[0],       // ���ջ���
 *                 16,              // ���ո���
 *                 0,               // cs_change �޸ı�
 *                 0,               // bpw ʹ��Ĭ������
 *                 0,               // udelay ����ʱ
 *                 0);              // speed ʹ��Ĭ��ֵ
 *
 *  //  ����������,�����ҽ���16���ֽ�
 *  aw_spi_mktrans(&trans[2],       // ���������ṹ 2
 *                 &txbuf[0],       // ���ͻ�����
 *                 &rxbuf[0],       // ���ջ���
 *                 16,              // ���ո���
 *                 0,               // cs_change �޸ı�
 *                 0,               // bpw ʹ��Ĭ������
 *                 0,               // udelay ����ʱ
 *                 0);              // speed ʹ��Ĭ��ֵ
 *
 *  // �����������Ϣ
 *  aw_spi_msg_init(&msg, my_callback, my_arg); // ��ʼ����Ϣ
 *  aw_spi_trans_add_tail(&msg, &trans[0]);     // ��ӵ�1������
 *  aw_spi_trans_add_tail(&msg, &trans[1]);     // ��ӵ�2������
 *  aw_spi_trans_add_tail(&msg, &trans[2]);     // ��ӵ�3������
 *
 *  // �첽���ʹ���Ϣ�������������أ�������ɺ����ú��� my_callback (my_arg)
 *  awbl_spi_async(p_dev, &msg);
 *
 *  // ͬ�����ʹ���Ϣ��������ɺ����ŷ���
 *  awbl_spi_sync(p_dev, &msg);
 *
 * \endcode
 *
 * \sa aw_spi_sync()
 */
aw_err_t awbl_spi_async(struct awbl_spi_device *p_dev,
                        struct aw_spi_message  *p_msg);

/**
 * \brief ������Ϣ��ͬ��ģʽ
 *
 * ���ӿ��ṩ�� AWBus SPI ���豸����ʹ��
 *
 * ��ͬ���ķ�ʽ������Ϣ����Ϣ�Ĵ���״̬�ͽ����ӳ�� p_msg->status��
 *
 * \param[in]       p_dev   AWBus SPI �豸ʵ��
 * \param[in,out]   p_msg   Ҫ�������Ϣ
 *
 * �����ķ���ֵ���£�
 * \retval AW_OK        ��Ϣ����ɹ�
 * \retval -AW_EINVAL   ��������p_msg ��ĳЩ��Ա������Ч������
 * \retval -ENOTSUP     ��Ϣ��ĳ����������ò�֧��(���磬�ִ�С���ٶȵ�)
 * \retval -ECANCELED   �����������������������Ϣ��ȡ�������Ժ�����
 *
 * �ɹ�����/���յ����ݸ�����ӳ�� p_msg->actual_length
 *
 * ��Ϣ�Ĵ���״̬�ͽ����ӳ�� p_msg->status ��
 *
 *      \li  -ENOTCONN       ��Ϣ��δ�Ŷ�
 *      \li  -EISCONN        ��Ϣ�����Ŷ�
 *      \li  -EINPROGRESS    ��Ϣ���ڱ�����
 * ����Ϊ��Ϣ������ϵĽ��
 *      \li  AW_OK           ���д���ɹ�����
 *      \li  -ENOTSUP        ��Ϣ��ĳ����������ò�֧��(���磬�ִ�С���ٶȵ�)
 *      \li  -ECANCELED      �����������������������Ϣ��ȡ�������Ժ�����
 *
 * \par ����
 * �� aw_spi_async()
 *
 * \sa aw_spi_async()
 */
aw_err_t awbl_spi_sync(struct awbl_spi_device *p_dev,
                       struct aw_spi_message  *p_msg);


/**
 * \brief ��д���
 *
 * ���ӿ��ṩ�� AWBus SPI ���豸����ʹ��
 *
 * �������Ƚ���SPIд�������ٽ��ж�������
 * ��ʵ��Ӧ���У�д����������Ϊ��ַ����������ΪҪ�Ӹõ�ַ��ȡ�����ݡ�
 *
 * \param[in]   p_dev   AWBus SPI �豸ʵ��
 * \param[in]   p_txbuf ���ݷ��ͻ�����
 * \param[in]   n_tx    Ҫ���͵������ֽڸ���
 * \param[out]  p_rxbuf ���ݽ��ջ�����
 * \param[in]   n_rx    Ҫ���յ������ֽڸ���
 *
 * \retval AW_OK        ��Ϣ����ɹ�
 * \retval -AW_EINVAL   ��������p_msg ��ĳЩ��Ա������Ч������
 * \retval -ENOTSUP     ��Ϣ��ĳЩ�������õ����Բ�֧��
 */
aw_err_t awbl_spi_write_then_read(struct awbl_spi_device *p_dev,
                                  const uint8_t          *p_txbuf,
                                  size_t                  n_tx,
                                  uint8_t                *p_rxbuf,
                                  size_t                  n_rx);


/**
 * \brief ִ������д����
 *
 * ���ӿ��ṩ�� AWBus SPI ���豸����ʹ��
 *
 * ����������ִ������д���������η������ݻ�����0�ͻ�����1�е����ݡ�
 * ��ʵ��Ӧ���У�������0����Ϊ��ַ��������1ΪҪд��õ�ַ�����ݡ�
 *
 * \param[in]   p_dev    AWBus SPI �豸ʵ��
 * \param[in]   p_txbuf0 ���ݷ��ͻ�����0
 * \param[in]   n_tx0    ������0���ݸ���
 * \param[out]  p_txbuf1 ���ݷ��ͻ�����1
 * \param[in]   n_tx1    ������1���ݸ���
 *
 * \retval AW_OK        ��Ϣ����ɹ�
 * \retval -AW_EINVAL   ��������p_msg ��ĳЩ��Ա������Ч������
 * \retval -ENOTSUP     ��Ϣ��ĳЩ�������õ����Բ�֧��
 */
aw_err_t awbl_spi_write_then_write(struct awbl_spi_device *p_dev,
                                   const uint8_t          *p_txbuf0,
                                   size_t                  n_tx0,
                                   const uint8_t          *p_txbuf1,
                                   size_t                  n_tx1);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AWBL_SPIBUS_H */

/* end of file */
