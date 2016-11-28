#include "apollo.h"
#include "aw_task.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "acp1000_din.h"
#include "acp1000_dout.h"
#include "aw_time.h"
#include "aw_rtc.h"
#include "pile.h"
#include "string.h"
#include "aw_adc.h"
#include "aw_sem.h"
#include "aw_gpio.h"
#include "event_node.h"
#include "ac_charge_prj_cfg.h"

#define TEMP_MAX      75        /* ���Ĺ����¶� */
#define TEMP_MIN     -30        /* ��С�Ĺ����¶� */

#define N_SAMPLES    10       //�����������Ϊ10��
#define CHANNEL      0         //ת��ͨ��Ϊͨ��2

struct adc_state {
    AW_SEMB_DECL(convert_sem);   /**< ת����� �ź���  */
    int num;                     /**< ת����ɵĲ��� */
};

static struct adc_state     g_adc_sta;

static void adc_callback (void *p_arg, int state)
{
     int num = (int)p_arg;

     if (state != AW_OK ) {
         //��������ת��ʧ�ܣ��������л��Զ�ȡ���������ٴ�ת��������������
         //���������жϼ��ص�������ʱ��Ӧ�þ����̣ܶ��ٴ˿���ʹ���ź�������Ϣ����
         //����ת��ʧ�ܵĹ��������������
         g_adc_sta.num = 2;
         AW_SEMB_GIVE(g_adc_sta.convert_sem);
     } else {
         //����ת���ɹ�����������������
         //���������жϼ��ص�������ʱ��Ӧ�þ����̣ܶ��ٴ˿���ʹ���ź�������Ϣ����
         //�������ݵĹ��������������
         g_adc_sta.num = num;
         AW_SEMB_GIVE(g_adc_sta.convert_sem);
     }
}

/**
 * ��ȡƽ��ֵ
 */
static inline uint16_t aver_get(uint16_t *p_buf, uint32_t len)
{
    uint32_t m  = 0;
    uint32_t sum = 0;

    if (0 == len) {
        return 0;
    }

    for (m = 0; m < len; m++) {
        sum += p_buf[m];
    }
    sum /= len;

    return sum;
}

/*******************************************************************************
 *  ȫ�ֱ�������
********************************************************************************/
/**
 * \brief �б��ж�Ӧ���¶�ֵ������-40~85�棬����1�档
 */
static const uint32_t g_temp_res_val[] = {
    /* -40~-31�� */
    248277, 233136, 219036, 205897, 193648, 182221, 171556, 161596, 152290, 143590,
    /* -30~-21�� */
    135452, 127837, 120707, 114028, 107768, 101898, 96391, 91222, 86369, 81809,
    /* -20~-11�� */
    77523, 73492, 69701, 66132, 62771, 59606, 56623, 53810, 51157, 48654,
    /* -10~-1�� */
    46290, 44058, 41950, 39957, 38072, 36290, 34603, 33006, 31494, 30062,
    /* 0~9�� */
    28704, 27417, 26197, 25039, 23940, 22897, 21906, 20964, 20070, 19219,
    /* 10~19�� */
    18410, 17641, 16909, 16212, 15548, 14916, 14313, 13739, 13192, 12669,
    /* 20~29�� */
    12171, 11696, 11242, 10809, 10395, 10000, 9622, 9261, 8916, 8585,
    /* 30~39�� */
    8269, 7967, 7678, 7400, 7135, 6881, 6637, 6403, 6179, 5965,
    /* 40~49�� */
    5759, 5561, 5372, 5189, 5015, 4847, 4686, 4531, 4382, 4239,
    /* 50~59�� */
    4101, 3969, 3842, 3719, 3601, 3488, 3379, 3274, 3172, 3075,
    /* 60~69�� */
    2981, 2890, 2803, 2719, 2638, 2559, 2484, 2411, 2341, 2273,
    /* 70~79�� */
    2207, 2144, 2083, 2024, 1967, 1912, 1858, 1807, 1757, 1709,
    /* 80~85�� */
    1662, 1617, 1574, 1532, 1491, 1451
};

static const int g_res_val_num = sizeof(g_temp_res_val) / sizeof(g_temp_res_val[0]);
static const int g_temp_start  =  -40;    /* �������ʼ�¶�Ϊ-20�� */


/**
 * \brief ����������ֵ���㹫ʽ
 * Rv = (Vref - Vadc) *Rm / Vadc
 * ����յ�·ͼ��֪Vref = 3300, Vadc = AD = vol�ɼ��ĵ�ѹ����λmv
 * Rm = 10000��
 * \param[in] adc_handle : ADC��׼������
 * \return ����ֵ�������������ֵ��
 */
static inline uint32_t ntc_res_get(uint32_t vol )
{
    return (3300 - vol) * 10000 / vol;
}

/**
 * \brief �¶������1��֮��ͨ���㷨ȡ�����ֵ
 *
 * \param[in] t1 : ��߽��¶�
 * \param[in] t1 : �ұ߽��¶�
 *
 * \return temp : �¶�ֵ
 */
static inline int16_t __ntc_temp_get_from_range (int t1,int t2, uint32_t res)
{
    int r1 = g_temp_res_val[t1 - g_temp_start];  /* �õ��¶�1��Ӧ����ֵ */
    int r2 = g_temp_res_val[t2 - g_temp_start];  /* �õ��¶�2��Ӧ����ֵ */

    int r  = res;
    int temp;

    /* Ϊ����С������������256��������8λ�� */
    temp =  (((t2 - t1) * (r - r1)) << 8) / (r2 - r1) + (t1 << 8);

    return temp;
}

/**
 * \brief ���ַ����������Ӧ���¶�ֵ
 * \param[in]  res : ������ֵ
 *
 * \return temp: �¶�ֵ
 */
static int16_t ntc_res_to_temp (uint32_t res)
{
    int16_t   temp;
    int low, high, mid;     /* ���ַ����������±�     */
    int t1,t2;              /* ����������¶�ֵ t1 ~ t2 */

    low  = 0;               /* ��ʼ���ϱ߽�Ϊ��һ��     */
    high = g_res_val_num - 1; /* ��ʼ���±߽�Ϊ���һ��   */

    while(1) {

        /* ����һλ����Ч�� (low + high)/2 */
        mid = (low + high) >> 1;

        /* ���ǡ����� */
        if (res == g_temp_res_val[mid]) {
            /* �����¶�ֵ������256�� */
            temp = (mid + g_temp_start) << 8;
            break;
        }

        /* ��ֵ�����м�ֵ����������ΧΪǰ�벿�֣�����highֵ */
        if (res > g_temp_res_val[mid]) {
            high = mid;
        } else {
            /* ��ֵС���м�ֵ����������ΧΪ��벿�֣�����lowֵ */
            low = mid;
        }

        /* ������Χȷ����1���ڣ��ҵ��¶�������Χ */
        if (high - low == 1) {

            /* �ұ߽��¶�ֵ */
            t2 = high + g_temp_start;
            /* ��߽��¶�ֵ */
            t1 = low - 1 + g_temp_start;
            /* ��������¶�ֵ */
            temp = __ntc_temp_get_from_range(t1, t2, res);

            break;
        }
    }

    return temp;
}


/* ========================================================================= */
#define TEMP_TASK_PRIO       5
#define TEMP_TACK_SIZE       1024
#define TEMP_DETECT_PERIOD   15
AW_TASK_DECL_STATIC(temp_task, TEMP_TACK_SIZE);

/**
 * �¶ȼ���������
 */
static void temp_task_entry(void *p_arg)
{
    pile_t *p_this = (pile_t *)p_arg;
    uint16_t  aver = 0;

    uint16_t  adc_val[N_SAMPLES]; // �ٶ�����λ��Ϊ12λ������������Ϊuint16_t
    uint32_t  ref_mv;
    uint32_t  sample_mv;
    uint32_t  bits;
    uint32_t  res;     /* NTC��ֵ */
    int16_t   temp;    /* ��ǰ�¶� */
    aw_err_t  ret;

    if (NULL == p_this) {
        return ;
    }

    aw_gpio_pin_cfg(PIO0_23, PIO0_23_AD0_0 | AW_GPIO_FLOAT | PIO0_23_ADMODE_ANALOG);
    aw_gpio_pin_cfg(PIO0_24, PIO0_24_AD0_1 | AW_GPIO_FLOAT | PIO0_24_ADMODE_ANALOG);

    ref_mv = aw_adc_vref_get(CHANNEL);
    bits   = aw_adc_bits_get(CHANNEL);
    bits = (1 << bits) - 1;

    while (1) {
           //ͬ����ȡ��ת�������󷵻�
           ret = aw_adc_sync_read(CHANNEL, adc_val, N_SAMPLES, FALSE);
           aver = aver_get(adc_val, N_SAMPLES);
           sample_mv = aver * ref_mv / bits;
//           AW_INFOF(("sample_mv : %d mv\r\n", sample_mv));
           res  = ntc_res_get(sample_mv);    /* �����ȡ����ֵ         */
//           AW_INFOF(("res : %d m\r\n", res));
           temp = ntc_res_to_temp(res);      /* ������ת�����¶Ȳ���   */
           temp /= 256;
//           AW_INFOF(("the temperature is %d ��\r\n", temp));
           event_node_tell_all(&p_this->evt_node,
                               PILE_TEMP,
                               temp);
#if ACP1000_TEMP_ERR_DETECT
           if (temp > TEMP_MAX) {
               event_node_tell_all(&p_this->evt_node,
                                   ERR_TEMP,
                                   1);
           } else if (temp < TEMP_MIN) {
               event_node_tell_all(&p_this->evt_node,
                                   ERR_TEMP,
                                   2);
           } else {
               event_node_tell_all(&p_this->evt_node,
                                   ERR_TEMP,
                                   0);
           }
#endif
           aw_mdelay(2000);
    }
}

void pile_temp_task_startup (pile_t *p_this)
{
    AW_TASK_INIT(temp_task,           /* ����ʵ�� */
                 "temp_task",         /* �������� */
                 TEMP_DETECT_PERIOD,  /* �������ȼ� */
                 TEMP_TACK_SIZE,      /* �����ջ��С */
                 temp_task_entry,     /* ������ں��� */
                 (void *)p_this);     /* ������ڲ��� */
    /* �������� */
    AW_TASK_STARTUP(temp_task);
}
