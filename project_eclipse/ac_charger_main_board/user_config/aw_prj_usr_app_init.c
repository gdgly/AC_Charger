/*******************************************************************************
*                                 AnyWhere
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.embedcontrol.com/
* e-mail:      anywhere.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief AnyWhere user application initialzation entry file.
 *
 * \internal
 * \par History
 * - 1.00 13-01-10  yangtao, first implementation.
 * \endinternal
 */

/*******************************************************************************
  headers
*******************************************************************************/

#include "apollo.h"
#include "aw_int.h"

/*******************************************************************************
  defines
*******************************************************************************/

/*******************************************************************************
  implementation
*******************************************************************************/
extern int  aw_main(void);

/* The function be called after start up,at first of main() */
void target_init(void)
{
    return;
}

/**
 * \brief user application initialization entry
 */
int aw_prj_usr_app_init (void)
{
    /* add user application initialization code here */   
    return aw_main();
}

/* end of file */
