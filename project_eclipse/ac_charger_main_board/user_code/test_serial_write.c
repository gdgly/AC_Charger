#include "apollo.h"
#include "aw_task.h"
#include "string.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "aw_serial.h"
#include "aw_ioctl.h"

#define UART1_TASK_PRIO       4
#define UART1_TACK_SIZE       2048
#define UART1_DETECT_PERIOD   1000
AW_TASK_DECL_STATIC(uart1_task, UART1_TACK_SIZE);

static uint8_t g_test_wbuf[200] = {0};
/**
 * ��̽������
 */
static void uart1_task_entry (void *p_arg)
{
    int com = COM1;

    aw_serial_ioctl(com, SIO_BAUD_SET, (void *)2400);
    /* ����Ϊ8������λ  */
    aw_serial_ioctl(com,
                   SIO_HW_OPTS_SET,
                   (void *)( CLOCAL | CREAD | CS8 ));

    /* ���ö�ȡ��ʱʱ��Ϊ20ms */
    aw_serial_ioctl(com, AW_TIOCRDTIMEOUT, (void *)20);


    /* �����Ƿ�ʹ��RS485 */
     aw_serial_ioctl(com, AM_UART_RS485_ENABLE_SET, 1);

    while (1) {
        aw_serial_write(com, g_test_wbuf, sizeof(g_test_wbuf));
        aw_mdelay(UART1_DETECT_PERIOD);
    }
}




static void uart1_task_startup (void)
{
    AW_TASK_INIT(uart1_task,           /* ����ʵ�� */
                 "uart1_task",            /* �������� */
                 UART1_TASK_PRIO,      /* �������ȼ� */
                 UART1_TACK_SIZE,      /* �����ջ��С */
                 uart1_task_entry,     /* ������ں��� */
                 NULL);        /* ������ڲ��� */
    /* �������� */
    AW_TASK_STARTUP(uart1_task);
}


#define UART4_TASK_PRIO       4
#define UART4_TACK_SIZE       2048
#define UART4_DETECT_PERIOD   1000
AW_TASK_DECL_STATIC(uart4_task, UART4_TACK_SIZE);

static uint8_t g_test_rbuf[10] = {0};
/**
 * ��̽������
 */
static void uart4_task_entry (void *p_arg)
{

    int len = 0;
    int com = COM4;

    aw_serial_ioctl(com, SIO_BAUD_SET, (void *)19200);
    /* ����Ϊ8������λ  */
    aw_serial_ioctl(com,
                   SIO_HW_OPTS_SET,
                   (void *)( CLOCAL | CREAD | CS8 ));

    /* ���ö�ȡ��ʱʱ��Ϊ20ms */
    aw_serial_ioctl(com, AW_TIOCRDTIMEOUT, (void *)20);


    /* �����Ƿ�ʹ��RS485 */
     aw_serial_ioctl(com, AM_UART_RS485_ENABLE_SET, 1);

    while (1) {
        len = aw_serial_read (com, g_test_rbuf, sizeof(g_test_rbuf));

        if (len <= 0) {
               continue;
         } else {
               for (len = 0; len < sizeof(g_test_rbuf); len++) {
                   if (g_test_rbuf[len] != (len + '0')) {
                       AW_INFOF(("COM%d Rx test failed!\r\n", com));
                   }
               }
               if (len == sizeof(g_test_rbuf)) {
                   AW_INFOF(("COM%d Rx test suscessfully!\r\n", com));
               }
          }
    }
}




static void uart4_task_startup (void)
{
    AW_TASK_INIT(uart4_task,           /* ����ʵ�� */
                 "uart4_task",            /* �������� */
                 UART4_TASK_PRIO,      /* �������ȼ� */
                 UART4_TACK_SIZE,      /* �����ջ��С */
                 uart4_task_entry,     /* ������ں��� */
                 NULL);        /* ������ڲ��� */
    /* �������� */
    AW_TASK_STARTUP(uart4_task);
}

void test_serial_write (void)
{
    uart1_task_startup();
    uart4_task_startup();
}
