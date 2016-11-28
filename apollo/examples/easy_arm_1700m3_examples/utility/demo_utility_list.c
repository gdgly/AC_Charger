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
 * \brief 链表例程
 *
 * - 实验现象：
 *   1. 打印出链表基础操作的过程：排序、删除节点、添加节点以及合并两个链表等
 *   2. 利用链表的基本服务完成约瑟夫环
 * 
 * \par 源代码
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
#include "aw_delay.h"                                              /* 延时服务 */
#include "aw_types.h"

/**
 * \brief 结构体类型和数据定义
 */
typedef uint_t  ElementType;

struct person 
{ 
    ElementType num; 
    ElementType PassWord; 
    struct aw_list_head list;                                               /*  继承通用链表结构            */
};
typedef struct person PERSON;
#define DataLength 8

/**
 * \brief 以下为数据类型定义，因为本平台不支持动态内存分配，所以需要提前静态定义好数据
 */
int Guinum[DataLength] = {1,2,3,4,5,6,7,8};
int GuiPassWord[DataLength] = {2,3,2,3,4,5,4,2};
PERSON Gpeson[DataLength];


/**
 * \brief 函数声明 
 */
void list_task_entry1(void);
void list_task_entry2(void);


/**
 * \brief 链表的基础服务
 */
void list_task_entry1 ()
{
    
    PERSON person_head;                                                /*  定义一个双向链表头结点                 */

    PERSON *temp = NULL;                                               /*   储存暂时信息，遍历使用                */                                                
    struct aw_list_head *pPos  = NULL;
    struct aw_list_head *pNext = NULL;
    PERSON NewNodeAdd = {9,6};                                         /*  链表添加节点使用                       */
    PERSON NewNodeRep = {10,5};                                        /*  链表替换节点使用                       */
    PERSON NewNodeCut ;                                                /*  链表分割时使用                         */
    
    uint_t i = 0;
    AW_INIT_LIST_HEAD(&person_head.list);                              /*  初始化一个头结点                       */     
    AW_INIT_LIST_HEAD(&NewNodeCut.list);

    aw_kprintf("链表基本服务如下： \n");
    
  /*
   *将元素挨个插入链表    
   */
    for(i = 0;i< DataLength;i++){
    
    Gpeson[i].num= Guinum[i];
    Gpeson[i].PassWord= GuiPassWord[i];    
//    aw_list_add(&(Gpeson[i].list),&(person_head.list));                /*  将节点倒序插入链表                      */
    aw_list_add_tail(&(Gpeson[i].list ),&(person_head.list));            /*  将节点正序插入链表                      */
    }
    
    aw_kprintf("正序输出信息如下： \n");        
    aw_list_for_each(pPos,&person_head.list){                            /*  for循环进行遍历并正序输出              */
        /*
         * pPos保存每个结构体的链表指针  
         * 根据pPos指针和偏移量得到指向结构体元素的指针temp            
         */                
        temp = aw_list_entry(pPos,PERSON,list);       
        aw_kprintf(" num= %d PassWord= %d \n", temp->num ,temp->PassWord);    
    }      

    aw_kprintf("倒序输出信息如下： \n");        
    aw_list_for_each_prev(pPos,&person_head.list){                      /*  for循环进行遍历并倒序输出              */    
        temp = aw_list_entry(pPos,PERSON,list);       
        aw_kprintf(" num= %d PassWord= %d \n", temp->num ,temp->PassWord);    
    } 

    /*
     *查找特定元素节点并将此节点删除
     */
    aw_list_for_each_safe(pPos,pNext,&person_head.list){                /*  n为标记指针方便删除后继续遍历           */
        temp = aw_list_entry(pPos,PERSON,list); 
        if(temp->num == 3){
            aw_list_del_init(pPos);                                     /*  将元素删除并将删除后的节点初始化为头结点 */
            break;
        }
    }

    aw_kprintf("删除节点的信息如下： \n");                              /*  被删除的节点信息                       */
    aw_kprintf(" num= %d PassWord= %d \n", temp->num ,temp->PassWord);

    aw_kprintf("链表删除后的输出信息如下： \n");        
    aw_list_for_each(pPos,&person_head.list){                           /*  将删除节点后的链表进行遍历并正序输出    */    
    temp = aw_list_entry(pPos,PERSON,list);       
    aw_kprintf(" num= %d  PassWord= %d \n", temp->num ,temp->PassWord);            
} 

  /*
   *查找特定元素节点，并将一个新节点插入此节点之后
   */ 
    aw_list_for_each(pPos,&person_head.list){                    
        temp = aw_list_entry(pPos,PERSON,list); 
        if(temp->num == 5){
            aw_list_add(&NewNodeAdd.list,pPos);                         /*  将新节点重新加入链表                   */
            break;
        }
    }        
        
    aw_kprintf("新加入的节点的信息如下： \n");                          /*  新加入的节点信息                       */
    aw_kprintf(" num= %d PassWord= %d \n", NewNodeAdd.num ,NewNodeAdd.PassWord);

    aw_kprintf("链表加入新节点后的输出信息如下： \n");        
    aw_list_for_each(pPos,&person_head.list){                          
        temp = aw_list_entry(pPos,PERSON,list);       
        aw_kprintf(" num= %d  PassWord= %d \n", temp->num ,temp->PassWord);            
    }
        
    /*
   *查找特定元素节点，并将一个新节点替代此节点
   */
    aw_list_for_each(pPos,&person_head.list){                    
        temp = aw_list_entry(pPos,PERSON,list); 
        if(temp->num == 2){
            aw_list_replace_init(pPos,&NewNodeRep.list);                /*  将新节点替代原有节点并加入链表          */
            break;
        }
    }        
        
    aw_kprintf("替代的节点的信息如下： \n");                            /*  新加入的节点信息                       */
    aw_kprintf(" num= %d PassWord= %d \n", NewNodeRep.num ,NewNodeRep.PassWord);
    aw_kprintf("被替代的节点的信息如下： \n");                          /*  被替代的节点信息                       */
    aw_kprintf(" num= %d PassWord= %d \n", temp->num ,temp->PassWord);
        
    aw_kprintf("链表加入替代节点后的输出信息如下： \n");        
    aw_list_for_each(pPos,&person_head.list){                          
        temp = aw_list_entry(pPos,PERSON,list);       
        aw_kprintf(" num= %d  PassWord= %d \n", temp->num ,temp->PassWord);            
    }
        
    /*
     *下边操作为两个链表之间的操作
     *将原来链表分割为两个链表，表头分别为person_head 和 NewNodeCut.list
     */
    aw_list_for_each(pPos,&person_head.list){                    
    temp = aw_list_entry(pPos,PERSON,list); 
        if(temp->num == 4){
            aw_list_cut_position(&NewNodeCut.list,&person_head.list,pPos);   /*  将原来链表拆分为两个链表          */
            break;
        }
    }        
        
    aw_kprintf("原来链表输出信息如下： \n");        
    aw_list_for_each(pPos,&person_head.list){                          
        temp = aw_list_entry(pPos,PERSON,list);       
        aw_kprintf(" num= %d  PassWord= %d \n", temp->num ,temp->PassWord);            
    }
    aw_kprintf("拆分得到的新链表输出信息如下： \n");        
    aw_list_for_each(pPos,&NewNodeCut.list){                          
        temp = aw_list_entry(pPos,PERSON,list);       
        aw_kprintf(" num= %d  PassWord= %d \n", temp->num ,temp->PassWord);            
    }
    
    /*
     *节点搬移，将链表中的一个节点删除后添加到一个新的链表
     */
    aw_list_for_each(pPos,&person_head.list){                    
    temp = aw_list_entry(pPos,PERSON,list); 
        if(temp->num == 5){                                             /*  pPos保存要删除的节点                   */                  
            aw_list_for_each(pNext,&NewNodeCut.list){                    
                temp = aw_list_entry(pNext,PERSON,list);                /*  n保存要插入的节点                     */
                if(temp->num == 1){
                    aw_list_move(pPos,pNext);                           /*  将pPos节点插入n节点之后                */
    //                aw_list_move_tail(pPos,n);                        /*  将pPos节点插入n节点之前                */
                    break;
                }
            }        
        break;
        }
    }        
        
    aw_kprintf("节点移动后原来链表输出信息如下： \n");        
    aw_list_for_each(pPos,&person_head.list){                          
        temp = aw_list_entry(pPos,PERSON,list);       
        aw_kprintf(" num= %d  PassWord= %d \n", temp->num ,temp->PassWord);            
    }
    aw_kprintf("节点移动后拆分得到的新链表输出信息如下： \n");        
    aw_list_for_each(pPos,&NewNodeCut.list){                          
        temp = aw_list_entry(pPos,PERSON,list);       
        aw_kprintf(" num= %d  PassWord= %d \n", temp->num ,temp->PassWord);            
    }
    
    /*
     *链表合并，将单独的两个链表合并为一个新的链表
     */    
        
    aw_list_for_each(pPos,&person_head.list){                    
    temp = aw_list_entry(pPos,PERSON,list); 
        if(temp->num == 8){
            aw_list_splice_init(&NewNodeCut.list,pPos);             /*  将两个链表合并为一个链表                 */
            break;
        }
    }    
    
    aw_kprintf("两个链表合并后新的链表输出信息如下： \n");        
    aw_list_for_each(pPos,&person_head.list){                          
        temp = aw_list_entry(pPos,PERSON,list);       
        aw_kprintf(" num= %d  PassWord= %d \n", temp->num ,temp->PassWord);            
    }

    
    aw_mdelay(100);        
}



/**
 * \brief 利用链表的基本服务完成约瑟夫环
 * 函数描述：已知n个人（以编号1，2，3...n分别表示）围坐在一张圆桌周围，每一个人都有一个唯一的密码，
 *                      编号为1的人将自己的密码说出后作为报数密码m，然后开始报数，数到m的那个人出列，
 *           并将自己的密码说出赋值给m然后被杀死；他的下一个人又从1开始报数，数到m的那个人又出列然后被杀死
 *           并以自己密码将m重新赋值，依此规律重复下去，直到圆桌周围的人全部出列并被杀死，求依次出列的顺序
 */
void list_task_entry2 ()
{

    PERSON person_head;                                                 /*  定义一个双向链表头结点                 */
     
    
    PERSON *temp = NULL;                                                                                              
    struct aw_list_head *pPos    = NULL;                                /*   储存遍历过程中被杀死的节点             */ 
    struct aw_list_head *pHead   = NULL;                                /*   储存每次遍历过程中的头结点             */
    struct aw_list_head *pNext   = NULL;                                /*  储存被杀死节点的下一个几点，记录使用    */
    
    uint_t i = 0;
    uint_t FlagNum = GuiPassWord[0];                                    /*  记录每一个节点的密码信息                */
    AW_INIT_LIST_HEAD(&person_head.list);                               /*  初始化一个头结点                        */     

    aw_kprintf("下面为约瑟夫环任务： \n");    
    /*
     *将元素挨个插入链表    
     */
    for(i = 0;i< DataLength;i++){
            
        Gpeson[i].num= Guinum[i];
        Gpeson[i].PassWord= GuiPassWord[i];    
        aw_list_add_tail(&(Gpeson[i].list ),&(person_head.list));       /*  将节点正序插入链表                     */
    }
        

    aw_kprintf("正序输出信息如下： \n");        
    aw_list_for_each(pPos,&person_head.list){                           /*  for循环进行遍历并正序输出              */        
        temp = aw_list_entry(pPos,PERSON,list);       
        aw_kprintf(" num= %d PassWord= %d \n", temp->num ,temp->PassWord);    
    }      



    pHead = &(person_head.list);                                         /*  保存每次遍历的头结点                   */
    i = 1;                                                               /*  保存每次遍历所走的步数                 */
    while(!aw_list_empty(&person_head.list)){                            /*  当所有节点被杀死后链表为空，停止遍历   */
                 
    /*
     *for循环模仿aw_list_for_each_safe(pPos,n,q)，不过去掉了截止条件        
     *实现走相应的步数，找到要杀死的节点
     */    
        for (pPos = pHead->next, pNext = pPos->next;;pPos = pNext, pNext = pPos->next){
            if((i == FlagNum) && (pPos != &person_head.list )){          /*  走了相应的步数后找到被杀死的节点        */
                break;
            } else if(pPos != &person_head.list){                        /*  遍历过的节点不包括头结点（没有数据）    */
                i++;                                                     /*   没有找到继续遍历，同时步数记录         */
            }
        
        }   
    
        FlagNum = (aw_list_entry(pPos,PERSON,list))->PassWord;           /*  将找到的杀死节点的密码作为新的要走的步数 */
        aw_list_del_init(pPos);                                          /*  将找到的节点杀死，重新组成链表           */
        pHead = pNext->prev;                                             /*  重新归置头结点                           */
        i = 1;                                                           /*  步数积累重新赋值为1，进行下次遍历        */
                
        aw_kprintf(" 被杀死的节点编号为 %d \n", aw_list_entry(pPos,PERSON,list)->num);    

    }
    aw_mdelay(100);        
}


/** 
 * \brief 延迟作业入口函数
 */
void demo_utility_list_entry (void)
{
    /* 定义任务实体，分配栈空间大小为512  */
    AW_TASK_DECL_STATIC(task1,512);
    AW_TASK_DECL_STATIC(task2,512);
    
    AW_TASK_INIT( task1,             /* 定义的任务实体   */
                 "task1",            /* 任务名           */
                   6,                /* 任务优先级       */
                  512,               /* 任务栈大小       */
                  list_task_entry1,  /* 任务的入口函数 */
                                        
                   0);               /* 传递给任务的参数 */
    
    AW_TASK_INIT( task2,             /* 定义的任务实体   */
                 "task2",            /* 任务名           */
                   8,                /* 任务优先级       */
                  512,               /* 任务栈大小       */
                  list_task_entry2,  /* 任务的入口函数 */
                                        
                   0);               /* 传递给任务的参数 */
    
    AW_TASK_STARTUP(task1);          /* 启动任务         */
    AW_TASK_STARTUP(task2);          /* 启动任务         */
}
/** [src_utility_list] */

/* end of file */
