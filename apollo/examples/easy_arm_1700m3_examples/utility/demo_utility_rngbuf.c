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
 * \brief ���λ���������
 *
 * - ʵ������
 *   1. ��ӡ���λ���������Ϣ���������ֽ�����ʣ����ֽ���
 *   2. ��ӡ���λ�����������
 * 
 * \par Դ����
 * \snippet demo_utility_rngbuf.c src_utility_rngbuf 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-08-13  hbt, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_utility_rngbuf
 * \copydoc demo_utility_rngbuf.c
 */
 
/** [src_utility_rngbuf] */
#include "apollo.h"
#include "aw_vdebug.h"
#include "aw_rngbuf.h"
#include "aw_delay.h"
#include "aw_types.h"
#include "string.h"


///**
// * \brief ��������
// */
//void rngbuf_task_entry(void *p_arg);



/**
 * \brief ���λ������ĵĻ���������
 */
static void rngbuf_task_entry (void *p_arg)
{
    char data;
    char *str1 = " you are using aworks platform";
    char strtemp[64];
    
    AW_RNGBUF_DEFINE(char_buf, char, 64);                                 /* 64��char�ռ�Ļ��λ�����char data;     */
    aw_rngbuf_putchar(&char_buf, 'd');                                    /* ���1���ַ���������                    */
    aw_rngbuf_getchar(&char_buf, &data);                                  /* �ӻ�������ȡ1����                      */
    aw_kprintf("list_task_entry1 \n");        
    aw_kprintf("ȡ�����ַ�= %c \n" ,data);        
    
    aw_rngbuf_flush (&char_buf);                                          /*  ��ջ�����                            */
    aw_rngbuf_put (&char_buf, str1, strlen(str1));
    aw_kprintf("�������������ֽ���= %d \n" ,aw_rngbuf_nbytes (&char_buf));        
    aw_kprintf("������ʣ�µ��ֽ���= %d \n" , aw_rngbuf_freebytes(&char_buf));    
    
    aw_rngbuf_get (&char_buf, strtemp, strlen(str1));
    aw_kprintf("�������������ֽ���= %d \n" ,aw_rngbuf_nbytes (&char_buf));        
    aw_kprintf("������ʣ�µ��ֽ���= %d \n" , aw_rngbuf_freebytes(&char_buf));    
     aw_kprintf("ȡ�����ַ���= %s \n" ,strtemp);
    

    aw_rngbuf_flush (&char_buf);
    memset(strtemp,0,64);
    if(aw_rngbuf_isempty(&char_buf)){                                       /* �жϻ������Ƿ�Ϊ��                    */
            aw_rngbuf_putchar(&char_buf, 'a');                              /* д������'a'                          */
            aw_rngbuf_put_ahead(&char_buf, 'b', 0);                         /* д������'b'�������'b'������          */
            aw_rngbuf_put_ahead(&char_buf, 'c', 1);                         /* д������'c'�����'c'Ҳ������          */
            aw_rngbuf_move_ahead(&char_buf, 2);                             /* ��ǰ�ƶ�����ָ��2���ֽ�               */
            aw_rngbuf_get(&char_buf, strtemp, 3);                           /* ��ʱ���԰�"abc"��������               */
    }
    aw_kprintf("ȡ�����ַ���= %s \n" ,strtemp);        


      aw_mdelay(100);        
}

/** 
 * \brief ����ringbuf����
 */
void demo_utility_rngbuf_entry (void)
{
    /* ��������ʵ�壬����ջ�ռ��СΪ512  */
    AW_TASK_DECL_STATIC(task0,512);

    AW_TASK_INIT( task0,             /* ���������ʵ��   */
                 "task0",            /* ������           */
                   8,                /* �������ȼ�       */
                  512,               /* ����ջ��С       */
                  rngbuf_task_entry, /* �������ں���   */
                   0);               /* ���ݸ�����Ĳ��� */
    
    AW_TASK_STARTUP(task0);          /* ��������         */
}

/** [src_utility_rngbuf] */

/* end of file */
