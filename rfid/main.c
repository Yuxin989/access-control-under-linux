/*
	功能：针对于ISO/IEC14443 TypeB类卡的RFID操作
	读写器型号兼容：MFRC522,MFRC523,FM17522,FM17550等
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "rfid_lib.h"
#include "uart_init.h"

void my_udp_send(int sockfd, unsigned char *card);

int main(void)
{
	unsigned char type[2], ret, card_id[4];
	int i;
	rfid_reset();
	rfid_carda_init();

	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		perror("socket");
		return -1;
	}

	while (1)
	{
		ret = rfid_carda_request(PICC_REQALL, type);
		if (ret == OK)
		{
			printf("type = 0x%02x%02x\n", type[0], type[1]);
			// WaitCardOff();
		}
		else
			continue;
		ret = rfid_anticoll(card_id);
		if (ret == OK)
		{
			printf("card ID:");
			for (i = 0; i < 4; i++)
				printf("0x%02x ", card_id[i]);
			puts("");
			WaitCardOff();
		}
		else
			continue;
		my_udp_send(sockfd, card_id);
	}
	close(sockfd);
	return 0;
}

void my_udp_send(int sockfd, unsigned char *card)
{
	struct sockaddr_in toaddr;
	toaddr.sin_family = AF_INET;
	toaddr.sin_port = htons(8000);
	toaddr.sin_addr.s_addr = inet_addr("10.9.42.212");

	// sendto(sockfd, card, 4, 0, (struct sockaddr *)&toaddr, sizeof(toaddr));

	char hex_card[32];
	sprintf(hex_card, "%d%d%d%d", card[0], card[1], card[2], card[3]);
	printf("拼接后: %s\n", hex_card);

	sendto(sockfd, hex_card, strlen(hex_card), 0, (struct sockaddr *)&toaddr, sizeof(toaddr));
}
