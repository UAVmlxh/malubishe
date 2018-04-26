#ifndef __client_h
#define __client_h
#include<stdio.h>


int tcp_init();
void chages_b_s(const unsigned char *bNum,unsigned char *sNum,int len);
unsigned char  tcp_getMessage(unsigned char *getnum,int sock_fd);
int  tcp_sendMessage( unsigned char *Mes_num,int sock_fd);



#endif
