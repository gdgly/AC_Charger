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
 * \brief 通用环形缓冲区
 *
 * 使用本服务需要包含头文件 aw_rngbuf.h
 *
 * \par 简单示例
 * \code
 * #include "apollo.h"
 * #include "aw_rngbuf.h"
 *
 * AW_RNGBUF_DEFINE(char_buf, char, 64);    // 64个char空间的环形缓冲区
 * char data;
 *
 * aw_rngbuf_putchar(&char_buf, 'a');       // 存放1个字符到缓冲区
 * aw_rngbuf_getchar(&char_buf, &data);     // 从缓冲区读取1个字符
 *
 * \endcode
 *
 * // 跟多内容待添加。。。
 *
 * \internal
 * \par modification history
 * - 1.02 12-12-08  orz, change type of size and nbytes to size_t.
 * - 1.01 12-10-22  orz, add prefix "aw_" to everything
 * - 1.00 12-10-15  orz, add implementation from VxWroks
 * @endinternal
 */

#ifndef __AW_RNGBUF_H
#define __AW_RNGBUF_H

/**
 * \addtogroup grp_aw_if_rngbuf
 * \copydoc aw_rngbuf.h
 * @{
 */
#include "aw_common.h"

/*lint ++flb */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief 定义静态的环形缓冲区存储空间
 *
 * 这个宏会定义的存储空间会比所需的空间多一个字节
 *
 * \param rb            需要定义缓冲空间的环形缓冲区
 * \param element_type  环形缓冲区存储的数据元素类型, 如char、 int或结构体等
 * \param num_elements  数据元素个数
 *
 * \note 环形缓冲区存储空间大小为：sizeof(element_type) * num_elements
 *
 * \par 示例
 * \code
 * typedef struct my_struct {
 *     char a;
 *     int  b;
 * } my_struct;
 *
 * AW_RNGBUF_SPACE_DEFINE(char_buf, char, 64);      // 64个char缓冲空间
 * AW_RNGBUF_SPACE_DEFINE(int_buf, int, 64);        // 64个int缓冲空间
 * AW_RNGBUF_SPACE_DEFINE(my_buf, my_struct, 16);   // 16个my_struct缓冲空间
 * \endcode
 * \hideinitializer
 */
#define AW_RNGBUF_SPACE_DEFINE(rb, element_type, num_elements) \
    struct __rngbuf_space_##rb { \
        element_type space[num_elements]; \
        char         resv[1]; \
    }; \
    static struct __rngbuf_space_##rb __rngbuf_space_##rb##_data

/**
 * \brief 获取使用宏AW_RNGBUF_SPACE_DEFINE()定义的缓冲空间大小
 *
 * \param rb 环形缓冲区
 *
 * \return 使用宏AW_RNGBUF_SPACE_DEFINE()定义的缓冲空间大小
 * \hideinitializer
 */
#define AW_RNGBUF_SPACE_SIZE(rb) \
        (sizeof(__rngbuf_space_##rb##_data.space) + 1)

/**
 * \brief 获取使用宏AW_RNGBUF_SPACE_DEFINE()定义的缓冲空间指针
 *
 * \param rb 环形缓冲区
 *
 * \return 使用宏AW_RNGBUF_SPACE_DEFINE()定义的缓冲空间指针
 * \hideinitializer
 */
#define AW_RNGBUF_SPACE_GET(rb) \
        (__rngbuf_space_##rb##_data.space)

/**
 * \brief 初始化一个使用宏AW_RNGBUF_SPACE_DEFINE()定义了存储空间的环形缓冲区
 *
 * \param rb 环形缓冲区
 *
 * \note 必须先使用宏AW_RNGBUF_SPACE_DEFINE()定义好存储空间，然后才能使用本宏
 * \hideinitializer
 */
#define AW_RNGBUF_INIT(rb) \
    aw_rngbuf_init(&rb, \
                   (char *)AW_RNGBUF_SPACE_GET(rb), \
                   AW_RNGBUF_SPACE_SIZE(rb))

/**
 * \brief 定义一个已经初始化过的环形缓冲区
 *
 * 使用这个宏定义的环形缓冲区可以立即使用，而无需再调用rngbuf_init()进行初始化
 *
 * \param rb            要定义的环形缓冲区
 * \param element_type  环形缓冲区存储的数据元素类型, 如char、 int或结构体等
 * \param num_elements  数据元素个数
 *
 * \note - 环形缓冲区存储空间大小为：sizeof(element_type) * num_elements
 *       - 不要再次使用rngbuf_init()对环形缓冲区进行初始化
 *
 * \par 示例
 * \code
 * typedef struct my_struct {
 *     char a;
 * } my_struct;
 *
 * int              data    = 1;
 * struct my_struct my_data = {0};
 *
 * AW_RNGBUF_DEFINE(char_buf, char, 64);    // 64个char空间的环形缓冲区
 * AW_RNGBUF_DEFINE(int_buf, int, 64);      // 64个int空间的环形缓冲区
 * AW_RNGBUF_DEFINE(my_buf, my_struct, 16); // 16个my_struct类型的环形缓冲区
 *
 * aw_rngbuf_putchar(&char_buf, 'a');
 * aw_rngbuf_put(&int_buf, (char *)&data, sizeof(data));
 * aw_rngbuf_put(&my_buf, (char *)&my_data, sizeof(my_data));
 * \endcode
 * \hideinitializer
 */
#define AW_RNGBUF_DEFINE(rb, element_type, num_elements) \
    AW_RNGBUF_SPACE_DEFINE(rb, element_type, num_elements); \
    struct aw_rngbuf rb = { \
        0, \
        0, \
        AW_RNGBUF_SPACE_SIZE(rb), \
        (char *)AW_RNGBUF_SPACE_GET(rb) \
    }

/**
 * \brief 环形缓冲区管理结构
 * \note 不要直接操作本结构的成员
 */
struct aw_rngbuf {
    int     in;     /**< \brief 缓冲区数据写入位置 */
    int     out;    /**< \brief 缓冲区数据读出位置 */
    int     size;   /**< \brief 缓冲区大小 */
    char   *buf;    /**< \brief 缓冲区 */
};

/** \brief 环形缓冲区类型 */
typedef struct aw_rngbuf *aw_rngbuf_t;

/**
 * \brief 初始化环形缓冲
 *
 * \param p_rb    要初始化的环形缓冲区
 * \param p_buf   缓冲区
 * \param size  缓冲区大小，系统保留一个字节，实际可用大小为 size - 1
 */
void aw_rngbuf_init (struct aw_rngbuf *p_rb, char *p_buf, size_t size);

/**
 * \brief 存放一个字节到环形缓冲区
 *
 * \param rb    要操作的环形缓冲
 * \param data  要存放到缓冲区的数据字节
 *
 * \retval 0 数据存放失败，缓冲区满
 * \retval 1 数据成功存放
 */
int aw_rngbuf_putchar (aw_rngbuf_t rb, const char data);

/**
 * \brief 从环形缓冲区取出一个字节数据
 *
 * \param rb     要操作的环形缓冲
 * \param p_data 存放数据字节的指针
 *
 * \retval 0 数据取出失败，缓冲区空
 * \retval 1 数据成功取出
 */
int aw_rngbuf_getchar (aw_rngbuf_t rb, char *p_data);

/**
 * \brief 存放若干字节到环形缓冲区
 *
 * \param rb     要操作的环形缓冲
 * \param p_buf  要存放到环形缓冲区的数据缓冲
 * \param nbytes 要存放到环形缓冲区的数据个数
 *
 * \return 成功存放的数据个数
 */
size_t aw_rngbuf_put (aw_rngbuf_t rb, const char *p_buf, size_t nbytes);

/**
 * \brief 从环形缓冲区获取数据
 *
 * \param rb     要操作的环形缓冲
 * \param p_buf  存放获取数据的缓冲
 * \param nbytes 要获取的数据个数
 *
 * \return 成功获取的数据个数
 */
size_t aw_rngbuf_get (aw_rngbuf_t rb, char *p_buf, size_t nbytes);

/**
 * \brief 清空环形缓冲区
 *
 * 这个函数清空环形缓冲区，所有之前留在缓冲区的数据会丢失
 *
 * \param rb 要操作的环形缓冲
 */
void aw_rngbuf_flush (aw_rngbuf_t rb);

/**
 * \brief 测试环形缓冲区是否为空
 *
 * \param rb 要测试的环形缓冲区
 *
 * \return 环形缓冲区空返回TRUE, 否则返回FALSE
 */
bool_t aw_rngbuf_isempty (aw_rngbuf_t rb);

/**
 * \brief 测试环形缓冲区是否添满
 *
 * \param rb 要测试的环形缓冲区
 *
 * \return 环形缓冲区满返回TRUE, 否则返回FALSE
 */
bool_t aw_rngbuf_isfull  (aw_rngbuf_t rb);

/**
 * \brief 获取环形缓冲区空闲空间大小
 *
 * \param rb 要判断的环形缓冲区
 *
 * \return 环形缓冲区空闲空间大小
 */
size_t aw_rngbuf_freebytes (aw_rngbuf_t rb);

/**
 * \brief 获取环形缓冲区中已填充的数据字节个数
 *
 * \param rb 要判断的环形缓冲区
 *
 * \return 环形缓冲区已填充字节个数
 */
size_t aw_rngbuf_nbytes (aw_rngbuf_t rb);

/**
 * \brief 向环形缓冲区中填入一个字节，但不移动写入数据指针
 *
 * 这个函数向环形缓冲区中写入一个字节，但不移动写入数据指针。因此这个字节不能被
 * 函数aw_rngbuf_get()读取。这个字节的写入位置为环形缓冲区中的当前写入位置偏移
 *  offset 个字节。因此偏移 offset 为0即为向当前写入位置填一个字节，就像调用了
 * 函数aw_rngbuf_putchar()一样，只不过输入指针没有往前移动。
 *
 * 只要正确移动一下输入数据指针，用这个函数写到环形缓冲区的所有数据就可以被读出
 * 来，移动输入数据指针通过函数aw_rngbuf_move_ahead()完成。
 *
 * \note 在调用aw_rngbuf_put_ahead()之前，要确保环形缓冲区中有 offset + 1 个
 *       字节空闲空间
 *
 * \param rb     要操作的环形缓冲区
 * \param byte   要放入环形缓冲区的字节数据
 * \param offset 要写入的数据相对环中当前写入位置的偏移位置，不能为负数
 *
 * \par 示例
 * \code
 * aw_rngbuf_putchar(&rb, 'a');        // 写入数据'a'
 *
 * aw_rngbuf_put_ahead(&rb, 'b', 0);   // 写入数据'b'，但这个'b'读不到
 * aw_rngbuf_put_ahead(&rb, 'c', 1);   // 写入数据'c'，这个'c'也读不到
 * aw_rngbuf_move_ahead(&rb, 2);       // 往前移动数据指针2个字节
 *
 * aw_rngbuf_get(&rb, buf, 3);         // 此时可以把"abc"都读出来
 * \endcode
 */
void aw_rngbuf_put_ahead  (aw_rngbuf_t rb, char byte, size_t offset);

/**
 * \brief 把环形缓冲区的当前写入指针往前移动 nbytes 个字节
 *
 * 这个函数把环形缓冲区的当前写入指针往前移动 nbytes 个字节。在使用
 * aw_rngbuf_put_ahead()写入了若干字节后，使用这个函数可使写入的这些字节能被读出
 *
 * \param rb     要移动输入指针的环形缓冲区
 * \param nbytes 输入指针往前移动的字节个数
 */
void aw_rngbuf_move_ahead (aw_rngbuf_t rb, size_t nbytes);

/** @}  grp_aw_if_rngbuf */

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* __AW_RNGBUF_H */

/* end of file */
