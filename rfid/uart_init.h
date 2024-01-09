#ifndef _UART_INIT_H_
#define _UART_INIT_H_

#include <termios.h>

//串口号
#if 0
	#define UART_DEV  	"/dev/ttyUSB0"
#else
	#define UART_DEV  	"/dev/ttySAC2"
#endif


//串口
#define UART_PUT_SUCCESS		0x00
#define UART_PUT_FAIL			0x01
#define UART_GET_SUCCESS		0x02
#define UART_GET_FAIL			0x03

//READ等待时间us
#define WAIT_USEC				10000

extern int uart_open(int *fd,char *port);
extern void uart_close(void);  
extern int uart_set(int fd,int speed,int flow_ctrl,int databits,int stopbits,int parity);
extern unsigned char uart_putchar(unsigned char ch);
extern unsigned char uart_getchar(unsigned char *ch, unsigned int wait_usec);
extern void rfid_uart_init(void);


#endif
