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
 * \brief ���ߺ�����
 *
 * - ʵ������
 *   1. ��ӡ�����ӻ�������Ϣ����ͨ������Ϣ�Լ�������Ϣ
 *   
 * 
 * \par Դ����
 * \snippet demo_utility_others.c src_utility_others
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-08-13  hbt, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_utility_others
 * \copydoc demo_utility_others.c
 */
 
/** [src_utility_others] */
#define AW_VDEBUG_DEBUG
#include "aw_vdebug.h" 

#include "apollo.h"
#include "aw_delay.h"
#include "aw_types.h"
#include "string.h"
#include "aw_errno.h"
#include "aw_common.h" 


/**
 * \brief ���ߺ���Ժ���
 * �������������ù��ߺ꣬ʵ�ִ�������Լ����ӻ����ԡ�
 */

static void utility_others_task_entry (void *p_arg)
{
    struct my_struct{
        int  m1;   
        char m2;
    };
    
    struct my_struct  my_st = {10,'w'};
    char             *p_m2  = &my_st.m2;
    int offset_m2           = AW_OFFSET( struct my_struct, m2); /*  �ṹ��Ԫ��ƫ����                */
    struct my_struct *p_st  = AW_CONTAINER_OF(p_m2, struct my_struct, m2);  /*  ��Ԫ�ص�ַ�õ��ṹ���ַ        */
    int a[3];
    
    aw_kprintf((const char *)p_st);
    aw_kprintf("ƫ���ֽ���= %d \n" , offset_m2);
    aw_kprintf("�ṹ���Ա= %d,%c \n" , p_st->m1,p_st->m2);
    aw_kprintf("�ṹ���Ա��С= %d,%d \n" ,AW_MEMBER_SIZE(struct my_struct, m1),AW_MEMBER_SIZE(struct my_struct, m2) );
    aw_kprintf("����Ԫ�ظ���= %d \n" , AW_NELEMENTS(a));
    
    aw_kprintf("��������= %d \n",AW_ROUND_UP(15, 4));
    aw_kprintf("��������= %d \n",AW_ROUND_DOWN(15, 4));
    aw_kprintf("������������= %d \n",AW_DIV_ROUND_UP(15, 8));
        
    if(AW_ALIGNED(0x789d, 4)){
        aw_kprintf("���ֽڶ���\n");
    } else {
        aw_kprintf("���ֽ�û�ж��룬����ȼ�Ϊ %d \n",EFAULT);
    }
        
    aw_kprintf("���ֽ�����ַ���Ϊ %s\n ",AW_XSTR(a)AW_XSTR(p)AW_XSTR(o)AW_XSTR(l)AW_XSTR(l)AW_XSTR(o));
        
   /*
    * ���ӻ�����
    */        
    AW_LOGF(("������Ϣ��ӡ��\n "));
    AW_INFOF(("This is a normal information\n"));                   /* ��ӡ��ͨ��Ϣ��ûʹ�ܣ�������� */
    AW_DBGF(("Value of register is %x\n"));                         /* ��ӡ������Ϣ                   */
    AW_WARNF(("Warning: invalid argument: %d\n"));                  /* ��ӡ������Ϣ                   */

    aw_mdelay(100);        
}

/** 
 * \brief �ӳ���ҵ��ں���
 */
void demo_utility_others_entry (void)
{
    /* ��������ʵ�壬����ջ�ռ��СΪ512  */
    AW_TASK_DECL_STATIC(task0,512);

    AW_TASK_INIT( task0,             /* ���������ʵ��   */
                 "task0",            /* ������           */
                   8,                /* �������ȼ�       */
                  512,               /* ����ջ��С       */
                  utility_others_task_entry, /* �������ں���   */
                   0);               /* ���ݸ�����Ĳ��� */
    
    AW_TASK_STARTUP(task0);          /* ��������         */
}

/** [src_utility_others] */

/* end of file */
