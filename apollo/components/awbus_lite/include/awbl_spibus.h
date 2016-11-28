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
 * \brief AWBus SPI总线接口头文件
 *
 * 使用本模块需要包含以下头文件：
 * \code
 * #include "awbl_spibus.h"
 * \endcode
 * 本模块为 SPI 总线的精简版实现
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
#include "aw_spi.h"         /* 通用SPI接口文件 */
#include "aw_sem.h"

/**
 * \name SPI 控制器功能限制标志
 * @{
  */
#define AWBL_SPI_MASTER_HALF_DUPLEX AW_BIT(0)  /**< /brief 不支持全双工 */
#define AWBL_SPI_MASTER_NO_RX       AW_BIT(1)  /**< /brief 不支持缓冲区读 */
#define AWBL_SPI_MASTER_NO_TX       AW_BIT(2)  /**< /brief 不支持缓冲区写 */
/** @} */

/** \biref 得到SPI从机设备的父控制器 */
#define AWBL_SPI_PARENT_GET(p_dev) \
    ((struct awbl_spi_master *) \
        (((struct awbl_dev *)(p_dev))->p_parentbus->p_ctlr))

/** \biref 得到SPI从机设备的父控制器编号 */
#define AWBL_SPI_PARENT_BUSID_GET(p_dev) \
        (((struct awbl_spi_master_devinfo *) \
            AWBL_DEVINFO_GET( \
                ((struct awbl_dev *)(p_dev))->p_parentbus->p_ctlr))->bus_index)

struct awbl_spi_master;

/** \biref AWBus SPI 总线控制器 (SPI 主机) 设备信息 (平台配置部分) */
struct awbl_spi_master_devinfo {

    /** \brief 控制器所对应的总线编号 */
    uint8_t     bus_index;
};

/** \biref AWBus SPI 总线控制器 (SPI 主机) 设备信息 (驱动配置部分) */
struct awbl_spi_master_devinfo2 {

    /** \brief 控制器的特性(支持的“SPI模式标帧本,见 aw_spi.h)  */
    uint16_t    features;

    /** \brief 控制器的限制(见“SPI 控制器功能限制标志”) */
    uint16_t    flags;

    /** DMA 缓冲区对齐要求, 如果控制器支持DMA传输的话 */
    uint16_t    dma_alignment;

    /**
     * \brief 设置控制器模式、时钟等参数 ( SPI 驱动可能多次调用)
     * \attention 该函数可能在传输活动时被调用，不要直接更新那些公共的寄存器，
     *            否则会破环当前传输。
     */
    aw_err_t (*pfunc_setup)(struct awbl_spi_master *p_master,
                            aw_spi_device_t        *p_dev);

   /**
     * \brief 启动传输
     *
     * 该函数的主要角色是添加消息到队列中。当前没有从队列中移除的操作，或者任何
     * 其它请求管理。对于 aw_spi_device 来说，该队列是纯粹的FIFO。
     *
     * 控制器的角色就是处理它的消息队列，选择片选然后发送数据。如果有多个 SPI
     * 从设备，I/O队列的仲裁算法是未指定的 (例如，循环、FIFO、优先级、保留、
     * 抢占等等)。
     *
     * 片选在整个消息的传输过程中保持有效 (除非 aw_spi_transfer.cs_change != 0
     * 影响了片选)。
     *
     * 消息传输使用先前为此设备调用 setup() 所设置的时钟和SPI模式。
     */
    aw_err_t (*pfunc_xfer_startup)(struct awbl_spi_master *p_master);
};

/* \biref SPI bus 从机设备驱动注册信息结构体 */
typedef struct awbl_spi_drvinfo {
    struct awbl_drvinfo super;  /**< \brief 继承自 AWBus 设备驱动信息 */
} awbl_spi_drvinfo_t;

/** \brief AWBus SPI 总线设备 (SPI从机) 实例 */
struct awbl_spi_device {
    struct awbl_dev super;          /**< \brief 继承自 AWBus 设备 */
    struct aw_spi_device spi_dev;   /**< \brief SPI 设备 */
};

/** \brief AWBus SPI 总线控制器 (SPI主机) 实例 */
struct awbl_spi_master {
    struct awbl_busctlr super;      /**< \brief 继承自 AWBus 总线控制器 */
    struct awbl_spi_master *p_next; /**< \brief 指向下一个 SPI 控制器 */


    /** \brief SPI 控制器相关信息 (驱动配置部分) */
    const struct awbl_spi_master_devinfo2 *p_devinfo2;

    /** \brief 控制器锁 */
    aw_spinlock_isr_t dev_lock;

    /** \brief 控制器互斥量 */
    AW_MUTEX_DECL(dev_mutex);

    /** \brief 总线锁定标志, 1-总线被锁定 0-总线未被锁定 */
    bool_t        bus_lock_flag;

    /** \brief SPI 控制器消息队列 */
    struct aw_list_head msg_list;

    /** \brief 消息内存分配, aw_spi_write_then_read() 使用此内存 */
    struct aw_spi_message msg;

    /** \brief 传输内存分配, aw_spi_write_then_read() 使用此内存  */
    struct aw_spi_transfer trans[2];
};

/** \brief 锁定控制器 */
#define AWBL_SPI_MASTER_LOCK(p_master) \
    aw_spinlock_isr_take(&((struct awbl_spi_master *)p_master)->dev_lock)

/** \brief 解除控制器锁定 */
#define AWBL_SPI_MASTER_UNLOCK(p_master) \
    aw_spinlock_isr_give(&((struct awbl_spi_master *)p_master)->dev_lock)

/**
 * \brief 添加一条 message 到控制器传输列表末尾
 * \attention 调用此函数必须锁定控制器
 */
aw_local aw_inline void awbl_spi_msg_in (struct awbl_spi_master *p_master,
                                         struct aw_spi_message  *p_msg)
{
    aw_list_add_tail((struct aw_list_head *)(&p_msg->ctlrdata),
                     &p_master->msg_list);
}

/**
 * \brief 从控制器传输列表表头取出一条 message
 * \attention 调用此函数必须锁定控制器
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
 * \brief 取消指定的 message (从队列中移除此 message)
 *
 * 只有消息尚未被处理时才可以被取消
 *
 * \retval  AW_OK       成功
 * \retval  AW_ERROR    失败，message正在被处理
 * \attention 调用此函数必须锁定控制器
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
 * \brief 检查控制器传输列表是否为空
 * \attention 调用此函数必须锁定控制器
 */
aw_local aw_inline int awbl_spi_msg_empty (struct awbl_spi_master *p_master)
{
    return aw_list_empty_careful(&p_master->msg_list);
}

/**
 * \brief AWBus SPI 总线模块初始化函数
 *
 * \attention 本函数应当在 awbus_lite_init() 之后、awbl_dev_init1() 之前调用
 */
void awbl_spibus_init(void);

/**
 * \brief 创建 AWBus SPI 总线实例以及枚举总线上的设备
 *
 * 本接口提供给 AWBus SPI 总线控制器(主机设备)驱动使用
 *
 */
aw_err_t awbl_spibus_create(struct awbl_spi_master *p_master);

/**
 * \brief 设置SPI设备结构体参数
 * \param p_dev         AWBus SPI从机设备实例
 * \param bits_per_word 字大小，为0时使用默认的“8-bit字大小”
 * \param mode          设备模式标志，见“SPI模式标志”
 * \param max_speed_hz  设备支持的最大速度
 * \param cs_pin        片选引脚编号(pfunc_cs 为NULL时，本参数有效)
 * \param pfunc_cs      片选控制函数(本参数不为 NULL 时， cs_pin 参数无效)
 *
 * \par 范例
 * 见 awbl_spi_setup()
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
 * \brief 设置SPI从机设备
 *
 * 本接口提供给 AWBus SPI 从设备驱动使用
 *
 * \attention 在SPI从机设备被使用前，必须先调用本函数进行设置，且如本函数返回
 *            错误，则一定不能再使用此SPI从机
 *
 * \param[in,out]   p_dev   SPI从机设备
 *
 * \retval   AW_OK      成功
 * \retval  -ENXIO      未找到指定的SPI总线
 * \retval  -ENOTSUP    某些特性不支持
 *
 * \par 示例
 * \code
 *
 * // 初始化设备描述结构
 * awbl_spi_mkdev(p_dev,          // AWBus SPI 设备实例
 *                8，             // 字大小为8-bit
 *                AW_SPI_MODE_0,  // SPI 模式0
 *                500000,         // 支持的最大速度 500000 Hz
 *                PIO0_3,         // 片选引脚为 PIO0_3
 *                NULL);          // 无自定义的片选控制函数
 *
 * // 设置设备
 * awbl_spi_setup(p_dev);
 *
 * \endcode
 */
aw_err_t awbl_spi_setup(struct awbl_spi_device *p_dev);

/**
 * \brief 处理消息、异步模式
 *
 * 本接口提供给 AWBus SPI 从设备驱动使用
 *
 * 以异步的方式处理消息，消息的处理状态和结果反映在 p_msg->status。
 * 消息处理结束(成功或出错)时，将会调用 p_msg->pfunc_complete 并传递参数
 * p_msg->p_arg。
 *
 * \param[in]       p_dev   AWBus SPI 设备实例
 * \param[in,out]   p_msg   要处理的消息
 *
 * 函数的返回值如下：
 * \retval  AW_OK       消息排队成功，等待处理
 * \retval  -EINVAL     参数错误
 *
 * 成功发送/接收的数据个数反映在 p_msg->actual_length
 *
 * 消息的处理状态和结果反映在 p_msg->status ：
 *
 *      \li  -ENOTCONN       消息尚未排队
 *      \li  -EISCONN        消息正在排队
 *      \li  -EINPROGRESS    消息正在被处理
 * 下面为消息处理完毕的结果
 *      \li  AW_OK           所有传输成功处理
 *      \li  -ENOTSUP        消息中某个传输的配置不支持(例如，字大小、速度等)
 *      \li  -ECANCELED      因控制器出错或处理队列满，消息被取消，可稍后再试
 *
 * \par 范例
 * \code
 *  aw_spi_device_t   spi_dev;
 *  aw_spi_message_t  msg;
 *  aw_spi_transfer_t trans[3];
 *  uint8_t           txbuf[16];
 *  uint8_t           rxbuf[16];
 *
 *  // 设置设备
 *  if (aw_spi_setup(&spi_dev) != AW_OK) {
 *      // 配置设备失败
 *  }
 *
 *  //  第一个传输,发送16个字节
 *  aw_spi_mktrans(&trans[0],       // 传输描述结构 0
 *                 &txbuf[0],       // 发送缓冲区
 *                 NULL,            // 接收缓冲
 *                 16,              // 发送个数
 *                 0,               // cs_change 无改变
 *                 0,               // bpw 使用默认配置
 *                 0,               // udelay 无延时
 *                 0);              // speed 使用默认值
 *
 *  //  第二个传输,接收16个字节
 *  aw_spi_mktrans(&trans[1],       // 传输描述结构 1
 *                 NULL,            // 发送缓冲区
 *                 &rxbuf[0],       // 接收缓冲
 *                 16,              // 接收个数
 *                 0,               // cs_change 无改变
 *                 0,               // bpw 使用默认配置
 *                 0,               // udelay 无延时
 *                 0);              // speed 使用默认值
 *
 *  //  第三个传输,发送且接收16个字节
 *  aw_spi_mktrans(&trans[2],       // 传输描述结构 2
 *                 &txbuf[0],       // 发送缓冲区
 *                 &rxbuf[0],       // 接收缓冲
 *                 16,              // 接收个数
 *                 0,               // cs_change 无改变
 *                 0,               // bpw 使用默认配置
 *                 0,               // udelay 无延时
 *                 0);              // speed 使用默认值
 *
 *  // 将传输组成消息
 *  aw_spi_msg_init(&msg, my_callback, my_arg); // 初始化消息
 *  aw_spi_trans_add_tail(&msg, &trans[0]);     // 添加第1个传输
 *  aw_spi_trans_add_tail(&msg, &trans[1]);     // 添加第2个传输
 *  aw_spi_trans_add_tail(&msg, &trans[2]);     // 添加第3个传输
 *
 *  // 异步发送此消息，函数立即返回，发送完成后会调用函数 my_callback (my_arg)
 *  awbl_spi_async(p_dev, &msg);
 *
 *  // 同步发送此消息，发送完成后函数才返回
 *  awbl_spi_sync(p_dev, &msg);
 *
 * \endcode
 *
 * \sa aw_spi_sync()
 */
aw_err_t awbl_spi_async(struct awbl_spi_device *p_dev,
                        struct aw_spi_message  *p_msg);

/**
 * \brief 处理消息、同步模式
 *
 * 本接口提供给 AWBus SPI 从设备驱动使用
 *
 * 以同步的方式处理消息，消息的处理状态和结果反映在 p_msg->status。
 *
 * \param[in]       p_dev   AWBus SPI 设备实例
 * \param[in,out]   p_msg   要处理的消息
 *
 * 函数的返回值如下：
 * \retval AW_OK        消息处理成功
 * \retval -AW_EINVAL   参数错误，p_msg 中某些成员参数无效，请检查
 * \retval -ENOTSUP     消息中某个传输的配置不支持(例如，字大小、速度等)
 * \retval -ECANCELED   因控制器出错或处理队列满，消息被取消，可稍后再试
 *
 * 成功发送/接收的数据个数反映在 p_msg->actual_length
 *
 * 消息的处理状态和结果反映在 p_msg->status ：
 *
 *      \li  -ENOTCONN       消息尚未排队
 *      \li  -EISCONN        消息正在排队
 *      \li  -EINPROGRESS    消息正在被处理
 * 下面为消息处理完毕的结果
 *      \li  AW_OK           所有传输成功处理
 *      \li  -ENOTSUP        消息中某个传输的配置不支持(例如，字大小、速度等)
 *      \li  -ECANCELED      因控制器出错或处理队列满，消息被取消，可稍后再试
 *
 * \par 范例
 * 见 aw_spi_async()
 *
 * \sa aw_spi_async()
 */
aw_err_t awbl_spi_sync(struct awbl_spi_device *p_dev,
                       struct aw_spi_message  *p_msg);


/**
 * \brief 先写后读
 *
 * 本接口提供给 AWBus SPI 从设备驱动使用
 *
 * 本函数先进行SPI写操作，再进行读操作。
 * 在实际应用中，写缓冲区可以为地址，读缓冲区为要从该地址读取的数据。
 *
 * \param[in]   p_dev   AWBus SPI 设备实例
 * \param[in]   p_txbuf 数据发送缓冲区
 * \param[in]   n_tx    要发送的数据字节个数
 * \param[out]  p_rxbuf 数据接收缓冲区
 * \param[in]   n_rx    要接收的数据字节个数
 *
 * \retval AW_OK        消息处理成功
 * \retval -AW_EINVAL   参数错误，p_msg 中某些成员参数无效，请检查
 * \retval -ENOTSUP     消息中某些传输设置的特性不支持
 */
aw_err_t awbl_spi_write_then_read(struct awbl_spi_device *p_dev,
                                  const uint8_t          *p_txbuf,
                                  size_t                  n_tx,
                                  uint8_t                *p_rxbuf,
                                  size_t                  n_rx);


/**
 * \brief 执行两次写操作
 *
 * 本接口提供给 AWBus SPI 从设备驱动使用
 *
 * 本函数连续执行两次写操作，依次发送数据缓冲区0和缓冲区1中的数据。
 * 在实际应用中，缓冲区0可以为地址，缓冲区1为要写入该地址的数据。
 *
 * \param[in]   p_dev    AWBus SPI 设备实例
 * \param[in]   p_txbuf0 数据发送缓冲区0
 * \param[in]   n_tx0    缓冲区0数据个数
 * \param[out]  p_txbuf1 数据发送缓冲区1
 * \param[in]   n_tx1    缓冲区1数据个数
 *
 * \retval AW_OK        消息处理成功
 * \retval -AW_EINVAL   参数错误，p_msg 中某些成员参数无效，请检查
 * \retval -ENOTSUP     消息中某些传输设置的特性不支持
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
