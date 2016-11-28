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
 * \brief ��������
 *
 * - ʵ������
 *   1. ��ӡ��������������Ĺ��̣�����ɾ���ڵ㡢��ӽڵ��Լ��ϲ����������
 *   2. ��������Ļ����������Լɪ��
 * 
 * \par Դ����
 * \snippet demo_utility_list.c src_utility_list 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-08-13  hbt, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_utility_list
 * \copydoc demo_utility_list.c
 */
 
/** [src_utility_list] */
#include "apollo.h"
#include "aw_vdebug.h"
#include "aw_list.h"
#include "aw_delay.h"                                              /* ��ʱ���� */
#include "aw_types.h"

/**
 * \brief �ṹ�����ͺ����ݶ���
 */
typedef uint_t  ElementType;

struct person 
{ 
    ElementType num; 
    ElementType PassWord; 
    struct aw_list_head list;                                               /*  �̳�ͨ������ṹ            */
};
typedef struct person PERSON;
#define DataLength 8

/**
 * \brief ����Ϊ�������Ͷ��壬��Ϊ��ƽ̨��֧�ֶ�̬�ڴ���䣬������Ҫ��ǰ��̬���������
 */
int Guinum[DataLength] = {1,2,3,4,5,6,7,8};
int GuiPassWord[DataLength] = {2,3,2,3,4,5,4,2};
PERSON Gpeson[DataLength];


/**
 * \brief �������� 
 */
void list_task_entry1(void);
void list_task_entry2(void);


/**
 * \brief ����Ļ�������
 */
void list_task_entry1 ()
{
    
    PERSON person_head;                                                /*  ����һ��˫������ͷ���                 */

    PERSON *temp = NULL;                                               /*   ������ʱ��Ϣ������ʹ��                */                                                
    struct aw_list_head *pPos  = NULL;
    struct aw_list_head *pNext = NULL;
    PERSON NewNodeAdd = {9,6};                                         /*  ������ӽڵ�ʹ��                       */
    PERSON NewNodeRep = {10,5};                                        /*  �����滻�ڵ�ʹ��                       */
    PERSON NewNodeCut ;                                                /*  ����ָ�ʱʹ��                         */
    
    uint_t i = 0;
    AW_INIT_LIST_HEAD(&person_head.list);                              /*  ��ʼ��һ��ͷ���                       */     
    AW_INIT_LIST_HEAD(&NewNodeCut.list);

    aw_kprintf("��������������£� \n");
    
  /*
   *��Ԫ�ذ�����������    
   */
    for(i = 0;i< DataLength;i++){
    
    Gpeson[i].num= Guinum[i];
    Gpeson[i].PassWord= GuiPassWord[i];    
//    aw_list_add(&(Gpeson[i].list),&(person_head.list));                /*  ���ڵ㵹���������                      */
    aw_list_add_tail(&(Gpeson[i].list ),&(person_head.list));            /*  ���ڵ������������                      */
    }
    
    aw_kprintf("���������Ϣ���£� \n");        
    aw_list_for_each(pPos,&person_head.list){                            /*  forѭ�����б������������              */
        /*
         * pPos����ÿ���ṹ�������ָ��  
         * ����pPosָ���ƫ�����õ�ָ��ṹ��Ԫ�ص�ָ��temp            
         */                
        temp = aw_list_entry(pPos,PERSON,list);       
        aw_kprintf(" num= %d PassWord= %d \n", temp->num ,temp->PassWord);    
    }      

    aw_kprintf("���������Ϣ���£� \n");        
    aw_list_for_each_prev(pPos,&person_head.list){                      /*  forѭ�����б������������              */    
        temp = aw_list_entry(pPos,PERSON,list);       
        aw_kprintf(" num= %d PassWord= %d \n", temp->num ,temp->PassWord);    
    } 

    /*
     *�����ض�Ԫ�ؽڵ㲢���˽ڵ�ɾ��
     */
    aw_list_for_each_safe(pPos,pNext,&person_head.list){                /*  nΪ���ָ�뷽��ɾ�����������           */
        temp = aw_list_entry(pPos,PERSON,list); 
        if(temp->num == 3){
            aw_list_del_init(pPos);                                     /*  ��Ԫ��ɾ������ɾ����Ľڵ��ʼ��Ϊͷ��� */
            break;
        }
    }

    aw_kprintf("ɾ���ڵ����Ϣ���£� \n");                              /*  ��ɾ���Ľڵ���Ϣ                       */
    aw_kprintf(" num= %d PassWord= %d \n", temp->num ,temp->PassWord);

    aw_kprintf("����ɾ����������Ϣ���£� \n");        
    aw_list_for_each(pPos,&person_head.list){                           /*  ��ɾ���ڵ���������б������������    */    
    temp = aw_list_entry(pPos,PERSON,list);       
    aw_kprintf(" num= %d  PassWord= %d \n", temp->num ,temp->PassWord);            
} 

  /*
   *�����ض�Ԫ�ؽڵ㣬����һ���½ڵ����˽ڵ�֮��
   */ 
    aw_list_for_each(pPos,&person_head.list){                    
        temp = aw_list_entry(pPos,PERSON,list); 
        if(temp->num == 5){
            aw_list_add(&NewNodeAdd.list,pPos);                         /*  ���½ڵ����¼�������                   */
            break;
        }
    }        
        
    aw_kprintf("�¼���Ľڵ����Ϣ���£� \n");                          /*  �¼���Ľڵ���Ϣ                       */
    aw_kprintf(" num= %d PassWord= %d \n", NewNodeAdd.num ,NewNodeAdd.PassWord);

    aw_kprintf("��������½ڵ��������Ϣ���£� \n");        
    aw_list_for_each(pPos,&person_head.list){                          
        temp = aw_list_entry(pPos,PERSON,list);       
        aw_kprintf(" num= %d  PassWord= %d \n", temp->num ,temp->PassWord);            
    }
        
    /*
   *�����ض�Ԫ�ؽڵ㣬����һ���½ڵ�����˽ڵ�
   */
    aw_list_for_each(pPos,&person_head.list){                    
        temp = aw_list_entry(pPos,PERSON,list); 
        if(temp->num == 2){
            aw_list_replace_init(pPos,&NewNodeRep.list);                /*  ���½ڵ����ԭ�нڵ㲢��������          */
            break;
        }
    }        
        
    aw_kprintf("����Ľڵ����Ϣ���£� \n");                            /*  �¼���Ľڵ���Ϣ                       */
    aw_kprintf(" num= %d PassWord= %d \n", NewNodeRep.num ,NewNodeRep.PassWord);
    aw_kprintf("������Ľڵ����Ϣ���£� \n");                          /*  ������Ľڵ���Ϣ                       */
    aw_kprintf(" num= %d PassWord= %d \n", temp->num ,temp->PassWord);
        
    aw_kprintf("�����������ڵ��������Ϣ���£� \n");        
    aw_list_for_each(pPos,&person_head.list){                          
        temp = aw_list_entry(pPos,PERSON,list);       
        aw_kprintf(" num= %d  PassWord= %d \n", temp->num ,temp->PassWord);            
    }
        
    /*
     *�±߲���Ϊ��������֮��Ĳ���
     *��ԭ������ָ�Ϊ����������ͷ�ֱ�Ϊperson_head �� NewNodeCut.list
     */
    aw_list_for_each(pPos,&person_head.list){                    
    temp = aw_list_entry(pPos,PERSON,list); 
        if(temp->num == 4){
            aw_list_cut_position(&NewNodeCut.list,&person_head.list,pPos);   /*  ��ԭ��������Ϊ��������          */
            break;
        }
    }        
        
    aw_kprintf("ԭ�����������Ϣ���£� \n");        
    aw_list_for_each(pPos,&person_head.list){                          
        temp = aw_list_entry(pPos,PERSON,list);       
        aw_kprintf(" num= %d  PassWord= %d \n", temp->num ,temp->PassWord);            
    }
    aw_kprintf("��ֵõ��������������Ϣ���£� \n");        
    aw_list_for_each(pPos,&NewNodeCut.list){                          
        temp = aw_list_entry(pPos,PERSON,list);       
        aw_kprintf(" num= %d  PassWord= %d \n", temp->num ,temp->PassWord);            
    }
    
    /*
     *�ڵ���ƣ��������е�һ���ڵ�ɾ������ӵ�һ���µ�����
     */
    aw_list_for_each(pPos,&person_head.list){                    
    temp = aw_list_entry(pPos,PERSON,list); 
        if(temp->num == 5){                                             /*  pPos����Ҫɾ���Ľڵ�                   */                  
            aw_list_for_each(pNext,&NewNodeCut.list){                    
                temp = aw_list_entry(pNext,PERSON,list);                /*  n����Ҫ����Ľڵ�                     */
                if(temp->num == 1){
                    aw_list_move(pPos,pNext);                           /*  ��pPos�ڵ����n�ڵ�֮��                */
    //                aw_list_move_tail(pPos,n);                        /*  ��pPos�ڵ����n�ڵ�֮ǰ                */
                    break;
                }
            }        
        break;
        }
    }        
        
    aw_kprintf("�ڵ��ƶ���ԭ�����������Ϣ���£� \n");        
    aw_list_for_each(pPos,&person_head.list){                          
        temp = aw_list_entry(pPos,PERSON,list);       
        aw_kprintf(" num= %d  PassWord= %d \n", temp->num ,temp->PassWord);            
    }
    aw_kprintf("�ڵ��ƶ����ֵõ��������������Ϣ���£� \n");        
    aw_list_for_each(pPos,&NewNodeCut.list){                          
        temp = aw_list_entry(pPos,PERSON,list);       
        aw_kprintf(" num= %d  PassWord= %d \n", temp->num ,temp->PassWord);            
    }
    
    /*
     *����ϲ�������������������ϲ�Ϊһ���µ�����
     */    
        
    aw_list_for_each(pPos,&person_head.list){                    
    temp = aw_list_entry(pPos,PERSON,list); 
        if(temp->num == 8){
            aw_list_splice_init(&NewNodeCut.list,pPos);             /*  ����������ϲ�Ϊһ������                 */
            break;
        }
    }    
    
    aw_kprintf("��������ϲ����µ����������Ϣ���£� \n");        
    aw_list_for_each(pPos,&person_head.list){                          
        temp = aw_list_entry(pPos,PERSON,list);       
        aw_kprintf(" num= %d  PassWord= %d \n", temp->num ,temp->PassWord);            
    }

    
    aw_mdelay(100);        
}



/**
 * \brief ��������Ļ����������Լɪ��
 * ������������֪n���ˣ��Ա��1��2��3...n�ֱ��ʾ��Χ����һ��Բ����Χ��ÿһ���˶���һ��Ψһ�����룬
 *                      ���Ϊ1���˽��Լ�������˵������Ϊ��������m��Ȼ��ʼ����������m���Ǹ��˳��У�
 *           �����Լ�������˵����ֵ��mȻ��ɱ����������һ�����ִ�1��ʼ����������m���Ǹ����ֳ���Ȼ��ɱ��
 *           �����Լ����뽫m���¸�ֵ�����˹����ظ���ȥ��ֱ��Բ����Χ����ȫ�����в���ɱ���������γ��е�˳��
 */
void list_task_entry2 ()
{

    PERSON person_head;                                                 /*  ����һ��˫������ͷ���                 */
     
    
    PERSON *temp = NULL;                                                                                              
    struct aw_list_head *pPos    = NULL;                                /*   ������������б�ɱ���Ľڵ�             */ 
    struct aw_list_head *pHead   = NULL;                                /*   ����ÿ�α��������е�ͷ���             */
    struct aw_list_head *pNext   = NULL;                                /*  ���汻ɱ���ڵ����һ�����㣬��¼ʹ��    */
    
    uint_t i = 0;
    uint_t FlagNum = GuiPassWord[0];                                    /*  ��¼ÿһ���ڵ��������Ϣ                */
    AW_INIT_LIST_HEAD(&person_head.list);                               /*  ��ʼ��һ��ͷ���                        */     

    aw_kprintf("����ΪԼɪ������ \n");    
    /*
     *��Ԫ�ذ�����������    
     */
    for(i = 0;i< DataLength;i++){
            
        Gpeson[i].num= Guinum[i];
        Gpeson[i].PassWord= GuiPassWord[i];    
        aw_list_add_tail(&(Gpeson[i].list ),&(person_head.list));       /*  ���ڵ������������                     */
    }
        

    aw_kprintf("���������Ϣ���£� \n");        
    aw_list_for_each(pPos,&person_head.list){                           /*  forѭ�����б������������              */        
        temp = aw_list_entry(pPos,PERSON,list);       
        aw_kprintf(" num= %d PassWord= %d \n", temp->num ,temp->PassWord);    
    }      



    pHead = &(person_head.list);                                         /*  ����ÿ�α�����ͷ���                   */
    i = 1;                                                               /*  ����ÿ�α������ߵĲ���                 */
    while(!aw_list_empty(&person_head.list)){                            /*  �����нڵ㱻ɱ��������Ϊ�գ�ֹͣ����   */
                 
    /*
     *forѭ��ģ��aw_list_for_each_safe(pPos,n,q)������ȥ���˽�ֹ����        
     *ʵ������Ӧ�Ĳ������ҵ�Ҫɱ���Ľڵ�
     */    
        for (pPos = pHead->next, pNext = pPos->next;;pPos = pNext, pNext = pPos->next){
            if((i == FlagNum) && (pPos != &person_head.list )){          /*  ������Ӧ�Ĳ������ҵ���ɱ���Ľڵ�        */
                break;
            } else if(pPos != &person_head.list){                        /*  �������Ľڵ㲻����ͷ��㣨û�����ݣ�    */
                i++;                                                     /*   û���ҵ�����������ͬʱ������¼         */
            }
        
        }   
    
        FlagNum = (aw_list_entry(pPos,PERSON,list))->PassWord;           /*  ���ҵ���ɱ���ڵ��������Ϊ�µ�Ҫ�ߵĲ��� */
        aw_list_del_init(pPos);                                          /*  ���ҵ��Ľڵ�ɱ���������������           */
        pHead = pNext->prev;                                             /*  ���¹���ͷ���                           */
        i = 1;                                                           /*  �����������¸�ֵΪ1�������´α���        */
                
        aw_kprintf(" ��ɱ���Ľڵ���Ϊ %d \n", aw_list_entry(pPos,PERSON,list)->num);    

    }
    aw_mdelay(100);        
}


/** 
 * \brief �ӳ���ҵ��ں���
 */
void demo_utility_list_entry (void)
{
    /* ��������ʵ�壬����ջ�ռ��СΪ512  */
    AW_TASK_DECL_STATIC(task1,512);
    AW_TASK_DECL_STATIC(task2,512);
    
    AW_TASK_INIT( task1,             /* ���������ʵ��   */
                 "task1",            /* ������           */
                   6,                /* �������ȼ�       */
                  512,               /* ����ջ��С       */
                  list_task_entry1,  /* �������ں��� */
                                        
                   0);               /* ���ݸ�����Ĳ��� */
    
    AW_TASK_INIT( task2,             /* ���������ʵ��   */
                 "task2",            /* ������           */
                   8,                /* �������ȼ�       */
                  512,               /* ����ջ��С       */
                  list_task_entry2,  /* �������ں��� */
                                        
                   0);               /* ���ݸ�����Ĳ��� */
    
    AW_TASK_STARTUP(task1);          /* ��������         */
    AW_TASK_STARTUP(task2);          /* ��������         */
}
/** [src_utility_list] */

/* end of file */
