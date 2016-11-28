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
 * \brief IO访问定义，仅供驱动使用
 *
 * \internal
 * \par modification history:
 * - 1.01 12-11-29  orz, add io{read/write}XX and io{read/write}XX_rep
 * - 1.00 12-09-04  orz, first implementation
 * \endinternal
 */

#ifndef __AW_IO_H
#define __AW_IO_H

/* todo: include arch io define file here */

#include "aw_types.h"
#include "aw_compiler.h"

#ifndef __iomem
#define __iomem
#endif

#ifndef __force
#define __force
#endif

/**
 * \name aw_io
 * \brief IO访问定义
 * @{
 * \par
 * readX/writeX()用于访问内存被映射的设备。不同体系结构中IO访问方式不尽相同。
 * 在一些简单的体系结构中，如没有MMU的ARM7，cortex-m3等，可以直接访问IO空间。
 * 而在其它体系结构中，如x86、开启了MMU的ARM9等，则不能直接访问IO空间，必须使用
 * 对应体系结构提供的方法进行访问，如进行物理地址转换等
 * \par
 * 可移植的驱动应该使用IO操作接口进行寄存器的读写，而不是直接对IO地址进行操作
 *
 * \note 如果你的体系架构不能直接对IO进行操作，则需要在定义__raw_readX()和
 * __raw_writeX()来覆盖本文件的定义
 */

#ifndef __raw_readb
static aw_inline uint8_t __raw_readb(const volatile void __iomem *addr)
{
	return *(const volatile uint8_t __force *) addr;
}
#endif

#ifndef __raw_readw
static aw_inline uint16_t __raw_readw(const volatile void __iomem *addr)
{
	return *(const volatile uint16_t __force *) addr;
}
#endif

#ifndef __raw_readl
static aw_inline uint32_t __raw_readl(const volatile void __iomem *addr)
{
	return *(const volatile uint32_t __force *) addr;
}
#endif

/******************************************************************************/

#ifndef __raw_read8_rep
static aw_inline void __raw_read8_rep (const void *addr, uint8_t *data, int len)
{
    while (len-- > 0) {
        *data++ = __raw_readb(addr);
    }
}
#endif

#ifndef __raw_read16_rep
static aw_inline void __raw_read16_rep (const void *addr,
                                        uint16_t   *data,
                                        int         len)
{
    while (len-- > 0) {
        *data++ = __raw_readw(addr);
    }
}
#endif

#ifndef __raw_read32_rep
static aw_inline void __raw_read32_rep (const void *addr,
                                        uint32_t   *data,
                                        int         len)
{
    while (len-- > 0) {
        *data++ = __raw_readl(addr);
    }
}
#endif

/******************************************************************************/

#define readb(addr)     __raw_readb(addr)
#define readw(addr)     __raw_readw(addr)
#define readl(addr)     __raw_readl(addr)

#define ioread8(addr)   __raw_readb(addr)
#define ioread16(addr)  __raw_readw(addr)
#define ioread32(addr)  __raw_readl(addr)

#define ioread8_rep(addr, data, n)      __raw_read8_rep (addr, data, n)
#define ioread16_rep(addr, data, n)     __raw_read16_rep(addr, data, n)
#define ioread32_rep(addr, data, n)     __raw_read32_rep(addr, data, n)

/******************************************************************************/

#ifndef __raw_writeb
static aw_inline void __raw_writeb(uint8_t b, volatile void __iomem *addr)
{
	*(volatile uint8_t __force *) addr = b;
}
#endif

#ifndef __raw_writew
static aw_inline void __raw_writew(uint16_t b, volatile void __iomem *addr)
{
	*(volatile uint16_t __force *) addr = b;
}
#endif

#ifndef __raw_writel
static aw_inline void __raw_writel(uint32_t b, volatile void __iomem *addr)
{
	*(volatile uint32_t __force *) addr = b;
}
#endif

#ifndef __raw_write8_rep
static aw_inline void __raw_write8_rep (void          *addr,
                                        const uint8_t *data,
                                        int            len)
{
    while (len-- > 0) {
        __raw_writeb(*data++, addr);
    }
}
#endif

#ifndef __raw_write16_rep
static aw_inline void __raw_write16_rep (void           *addr,
                                         const uint16_t *data,
                                         int             len)
{
    while (len-- > 0) {
        __raw_writew(*data++, addr);
    }
}
#endif

#ifndef __raw_write32_rep
static aw_inline void __raw_write32_rep (void           *addr,
                                         const uint32_t *data,
                                         int             len)
{
    while (len-- > 0) {
        __raw_writel(*data++, addr);
    }
}
#endif

/******************************************************************************/

#define writeb(b, addr)     __raw_writeb(b, addr)
#define writew(b, addr)     __raw_writew(b, addr)
#define writel(b, addr)     __raw_writel(b, addr)

#define iowrite8(b, addr)   __raw_writeb(b, addr)
#define iowrite16(b, addr)  __raw_writew(b, addr)
#define iowrite32(b, addr)  __raw_writel(b, addr)

#define iowrite8_rep(addr, data, n)     __raw_write8_rep (addr, data, n)
#define iowrite16_rep(addr, data, n)    __raw_write16_rep(addr, data, n)
#define iowrite32_rep(addr, data, n)    __raw_write32_rep(addr, data, n)

/* @} */

#endif /* __AW_IO_H */

/* end of file */
