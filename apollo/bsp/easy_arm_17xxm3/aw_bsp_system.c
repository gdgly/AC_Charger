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

		/* ���OSCƵ�ʳ���18MHz,����Χ����Ϊ15 ~ 25MHz */
		if (freq > 18000000) {
			amhw_syscon_oscrange_set(AMHW_SYSCON_OSCRANGE_15_25MHz);
		}

		amhw_syscon_osc_enable();
		while (amhw_syscon_osc_ready_chk() == FALSE);  /* �ȴ�OSC ready */
	}

	/* ����ʱ�ӷ�Ƶ����������CPUƵ��Ϊ100MHz,��PLL���Ƶ������Ϊ300MHz������Ҫ3��Ƶ */
	amhw_clock_cclk_div_set(AW_CFG_CPU_CLK_DIV);

	if (AW_CFG_PLL0_ENABLE == 1) {
		/*
		 * ��PLL0�����Ƶ�����õ�300MHz,PLL0�����Ƶ�ʣ�275MHz ~ 550MHz��
		 * ѡ��һ��ϣ����CPUƵ�ʵ��������������ڸ��������Сֵ��ѣ���USBʹ��PLL0ʱ��Ƶ��ֻ����288��384��480MHz�е�һ����
		 */
		amhw_pll0_config(AW_CFG_PLL0_CLK_SRC, AW_CFG_PLL0_FCCO_FREQ);
	} else {
#ifdef AW_LPC177X_8X
        /* ѡ������ʱ��Դ  */
        amhw_clock_pll0_insrc_set(AW_CFG_PLL0_CLK_SRC);

        /* ѡ��PLL0����ʱ����ΪCPU CLK */
        amhw_clock_cclk_src_set(AMHW_CLOCK_CCLK_SRC_SYSCLK);

        amhw_clock_pll0_disable();           /* PLL0ʧ��                     */
        amhw_clock_pll0_feed();
#endif
	}

#ifdef AW_LPC177X_8X
    /* ����ʱ�ӷ�Ƶ����  */
    amhw_clock_pclk_div_set(AW_CFG_PCLK_DIV);
#endif

	/*
	 * ����ʱ��Ƶ��ֵ��g_system_clkfreq
	 */
	amhw_clock_freq_update();

	/* ����FLASH����ʱ������ */
	amhw_syscon_flash_cfg(g_system_clkfreq);

}

/* end of file */
