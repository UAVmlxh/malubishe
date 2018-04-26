#ifndef __shujuku_h
#define __shujuku_h
#include <stdio.h>

void chage(const unsigned char *card_num, unsigned char *card_string,int len);
int findsql(unsigned char *num, char *cishu);
int input_sql(unsigned char *num,unsigned char xuanze);
int update_sql(unsigned char *num,unsigned char count);


#endif
