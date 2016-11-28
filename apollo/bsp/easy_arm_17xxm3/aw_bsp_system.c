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
 * \brief System initialization configure
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */
#include "apollo.h"
#include "ametal.h"
#include "aw_prj_params.h"
#include "aw_bsp_config.h"

/** 
 * \brief System initialization
 * The function should be called in aw_bsp_early_init()
 */
void aw_bsp_system_init (void)
{
    uint32_t freq;

#if AW_CFG_PLL0_CLK_SRC == AMHW_CLOCK_PLL0_INSRC_OSC
    amhw_clock_freq_osc_set(AW_CFG_CLOCK_OSC_FREQ);
#endif

	if (AW_CFG_PLL0_CLK_SRC == AMHW_CLOCK_PLL0_INSRC_OSC) {
		freq = amhw_clock_freq_osc_get();

		/* 如果OSC频率超过18MHz,将范围设置为15 ~ 25MHz */
		if (freq > 18000000) {
			amhw_syscon_oscrange_set(AMHW_SYSCON_OSCRANGE_15_25MHz);
		}

		amhw_syscon_osc_enable();
		while (amhw_syscon_osc_ready_chk() == FALSE);  /* 等待OSC ready */
	}

	/* 设置时钟分频，如期望的CPU频率为100MHz,将PLL输出频率设置为300MHz，则需要3分频 */
	amhw_clock_cclk_div_set(AW_CFG_CPU_CLK_DIV);

	if (AW_CFG_PLL0_ENABLE == 1) {
		/*
		 * 将PLL0的输出频率设置到300MHz,PLL0的输出频率（275MHz ~ 550MHz）
		 * 选择一个希望的CPU频率的整数倍，以落在该区域的最小值最佳，当USB使用PLL0时，频率只能是288、384、480MHz中的一个。
		 */
		amhw_pll0_config(AW_CFG_PLL0_CLK_SRC, AW_CFG_PLL0_FCCO_FREQ);
	} else {
#ifdef AW_LPC177X_8X
        /* 选择输入时钟源  */
        amhw_clock_pll0_insrc_set(AW_CFG_PLL0_CLK_SRC);

        /* 选择PLL0输入时钟作为CPU CLK */
        amhw_clock_cclk_src_set(AMHW_CLOCK_CCLK_SRC_SYSCLK);

        amhw_clock_pll0_disable();           /* PLL0失能                     */
        amhw_clock_pll0_feed();
#endif
	}

#ifdef AW_LPC177X_8X
    /* 外设时钟分频设置  */
    amhw_clock_pclk_div_set(AW_CFG_PCLK_DIV);
#endif

	/*
	 * 更新时钟频率值：g_system_clkfreq
	 */
	amhw_clock_freq_update();

	/* 设置FLASH访问时钟设置 */
	amhw_syscon_flash_cfg(g_system_clkfreq);

}

/* end of file */
