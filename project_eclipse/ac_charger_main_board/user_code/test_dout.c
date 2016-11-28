#include "apollo.h"
#include "acp1000/acp1000_dout.h"
#include "aw_task.h"

/* ========================================================================= */
#define SWITCH_TASK_PRIO       5
#define SWITCH_TACK_SIZE       1024
AW_TASK_DECL_STATIC(switch_task, SWITCH_TACK_SIZE);

/**
 * 桩异常检测任务
 */
static void switch_task_entry (void *p_arg)
{

    while (1) {
        aw_mdelay(1000);
        acp1000_gun_unlock();
        aw_mdelay(1000);
        acp1000_gun_lock();

        aw_mdelay(1000);
        aw_gpio_set(ACP1000_DOUT_LED1, 1);
        aw_mdelay(1000);
        aw_gpio_set(ACP1000_DOUT_LED1, 0);

        aw_mdelay(1000);
        aw_gpio_set(ACP1000_DOUT_LED2, 1);
        aw_mdelay(1000);
        aw_gpio_set(ACP1000_DOUT_LED2, 0);

        aw_mdelay(1000);
        aw_gpio_set(ACP1000_DOUT_LED3, 1);
        aw_mdelay(1000);
        aw_gpio_set(ACP1000_DOUT_LED3, 0);

        aw_mdelay(1000);
        aw_gpio_set(ACP1000_DOUT_LEDS, 1);
        aw_mdelay(1000);
        aw_gpio_set(ACP1000_DOUT_LEDS, 0);

        aw_mdelay(1000);
        aw_gpio_set(ACP1000_DOUT_AC, 1);
        aw_mdelay(1000);
        aw_gpio_set(ACP1000_DOUT_AC, 0);
    }
}

void test_switch_startup (void)
{
    AW_TASK_INIT(switch_task,           /* 任务实体 */
                 "switch_task",         /* 任务名字 */
                 SWITCH_TASK_PRIO,      /* 任务优先级 */
                 SWITCH_TACK_SIZE,      /* 任务堆栈大小 */
                 switch_task_entry,     /* 任务入口函数 */
                 (void *)NULL);     /* 任务入口参数 */
    /* 启动任务 */
    AW_TASK_STARTUP(switch_task);
}
