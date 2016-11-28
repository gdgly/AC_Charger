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
 * \brief IO���ʶ��壬��������ʹ��
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
 * \brief IO���ʶ���
 * @{
 * \par
 * readX/writeX()���ڷ����ڴ汻ӳ����豸����ͬ��ϵ�ṹ��IO���ʷ�ʽ������ͬ��
 * ��һЩ�򵥵���ϵ�ṹ�У���û��MMU��ARM7��cortex-m3�ȣ�����ֱ�ӷ���IO�ռ䡣
 * ����������ϵ�ṹ�У���x86��������MMU��ARM9�ȣ�����ֱ�ӷ���IO�ռ䣬����ʹ��
 * ��Ӧ��ϵ�ṹ�ṩ�ķ������з��ʣ�����������ַת����
 * \par
 * ����ֲ������Ӧ��ʹ��IO�����ӿڽ��мĴ����Ķ�д��������ֱ�Ӷ�IO��ַ���в���
 *
 * \note ��������ϵ�ܹ�����ֱ�Ӷ�IO���в���������Ҫ�ڶ���__raw_readX()��
 * __raw_writeX()�����Ǳ��ļ��Ķ���
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
