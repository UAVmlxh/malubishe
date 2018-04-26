#include <stdio.h>
#include "RFID.h"
#include <bcm2835.h>
#include "shujuku.h"
#include <unistd.h>
#include "client.h"
#include <string.h>
#include <sched.h>
#include <string.h>
#include <stdlib.h>

//#define __test_

unsigned char cishu;

int kacaozuo(unsigned char *test_card){
	
	char card_typa[2];
     cishu=0;

	
	//首先找卡
	//小区没有这个卡
	if(findsql(test_card,card_typa)==0){
		printf("NO card!\n");
		return 9;
	}
	
	cishu=card_typa[0];
	if(cishu==6){
		printf("zhuhu card!\n"); //住户卡
		return 6;
	}
	if(cishu==7){             
		printf("card yi suosi!\n"); //suosika 
		return  7;  
	}
	
	update_sql(test_card,cishu);	
	printf("laibin card!\n");
	cishu=cishu-1;
	printf("shenyu %d\n",cishu);//来宾卡
	return cishu;
}



int test1(const int pri)
{
  struct sched_param sched ;

  memset (&sched, 0, sizeof(sched)) ;

  if (pri > sched_get_priority_max (SCHED_RR))
    sched.sched_priority = sched_get_priority_max (SCHED_RR) ;
  else
    sched.sched_priority = pri ;

  return sched_setscheduler (0, SCHED_RR, &sched) ;
}

void playmusic(int sunxu)
{
	switch(sunxu)
	{
		case 1:system("play /home/pi/malu/xixi/1.mp3");break;
		case 2:system("play /home/pi/malu/xixi/2.mp3");break;
		case 3:system("play /home/pi/malu/xixi/3.mp3");break;
		case 4:system("play /home/pi/malu/xixi/4.mp3");break;
		case 5:system("play /home/pi/malu/xixi/5.mp3");break;
		default:break;
	}
}



int main()
{	
	unsigned char card_num[4];
	unsigned char s;//读出2个字节数据TagType--卡片类型代码
	char status;
	unsigned char onum[16];
	unsigned char get_data[4];      //从qt中得到的数据
	unsigned char test_num[4];   
	unsigned char tcp_flag;         //得到的TCP的应答
	int tcp_socket=1;
	int i;
	unsigned char a_buff[8];
	unsigned char key[6]={0xff,0xff,0xff,0xff,0xff,0xff};
	int card_flag=0;
	int bobaoyuying=0;
	
	
	if(!bcm2835_init()) 
		return -1;
	
	MFRC522_Initializtion();
	bcm2835_gpio_fsel(35, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(35, HIGH);
	test1(99);
	int card_count=0;
	
	while(1)
	{	

		//服务器初始化失败
		    if(tcp_socket==1){	
				for(i=0;i<10;i++){
						sleep(2);
						tcp_socket=tcp_init();
						if(tcp_socket != 1)
							break;
					}
					if(i==10){
						sleep(10);
						tcp_socket=tcp_init();
					}		
			}
			//初始化成功
			else{
					memset(&get_data[0],0,4*sizeof(unsigned char));
					memset(&a_buff[0],0,8*sizeof(unsigned char));
					memset(&test_num[0],0,4*sizeof(unsigned char));
						
					tcp_flag=tcp_getMessage(get_data,tcp_socket);
					if(tcp_flag==2)//无法接受到服务器数据，则认为服务器死掉
					{
						tcp_socket=1;
					}
					else
					{
						bobaoyuying=0;
					   //用户界面所有操作
					      if(get_data[0]==0x12){
										memset(&card_num[0],0,4*sizeof(unsigned char));
										memset(&onum[0],0,16*sizeof(unsigned char));
										bobaoyuying=0;
									 while(1){
										status=PcdRequest(0x52,&s);    //搜索卡片类型
										if(status==MI_OK)status=PcdAnticoll(card_num);  //读卡号
										if(status==MI_OK)status=PcdSelect(card_num);    //选卡				
										if(status==MI_OK){
												card_flag=kacaozuo(card_num);
												//住户卡
												if(card_flag==6){
												//输入密码（通过QT发送的字符串得到）
												//操作成功后返回相应的成功标识
												status=PcdAuthState(PICC_AUTHENT1A,1,key,card_num);	
												status=PcdRead(1,onum);
												if(status == MI_OK){
													//比对
													if(memcmp(&get_data[1],&onum[0],3*sizeof(unsigned char))==0){
														     test_num[0]=0x12;
															 test_num[1]=0x01;
															 card_count=0;
															 bobaoyuying=2;
															 break;
													}
													else{
															 test_num[0]=0x12;
															 test_num[1]=0x02;
															 card_count++;
															 bobaoyuying=3;	
													}
													if(card_count==3){
														update_sql(card_num,8);
														card_count=0;
														bobaoyuying=4;
													}
													//如果失败 SID值7是锁死状态
													break;
													}
												}
												//住户卡锁死
											else if(card_flag==7){
													test_num[0]=0x12;
													test_num[1]=0x07;
													bobaoyuying=4;
													break;//直接跳出
												}
												//非本小区卡
										    else if(card_flag==9){
													test_num[0]=0x12;
													test_num[1]=0x09;
													bobaoyuying=1;
													break;//直接跳出
												}
											
											else{
													
													break;//直接跳出
												}
											}
										}	
											chages_b_s(test_num,a_buff,4);
											tcp_sendMessage(a_buff,tcp_socket);	
											playmusic(bobaoyuying);
									    }
					   
					   //来宾卡(非用户卡)
				     else if(get_data[0]==0X13){
						   memset(&card_num[0],0,4*sizeof(unsigned char));
										memset(&onum[0],0,16*sizeof(unsigned char));
										
									 while(1){
										status=PcdRequest(0x52,&s);    //搜索卡片类型
										if(status==MI_OK)status=PcdAnticoll(card_num);  //读卡号
										if(status==MI_OK)status=PcdSelect(card_num);    //选卡				
										if(status==MI_OK){
												card_flag=kacaozuo(card_num);
												if((card_flag <=4)&&(card_flag>=0)){
													test_num[0]=0x12;
													test_num[1]=0x08;
													test_num[2]=cishu;
													break;
												}
												else{
													test_num[0]=0x13;
													break;
												
												}
											}
										}
										chages_b_s(test_num,a_buff,4);
										tcp_sendMessage(a_buff,tcp_socket);	
										playmusic(bobaoyuying);
					   }
					   //保安界面所有操作
					   //解锁
			         else if(get_data[0]==0x22){
									memset(&card_num[0],0,4*sizeof(unsigned char));
								while(1){	
									status=PcdRequest(0x52,&s);    //搜索卡片类型
										if(status==MI_OK)status=PcdAnticoll(card_num);  //读卡号
										if(status==MI_OK)status=PcdSelect(card_num);    //选卡				
										if(status==MI_OK){
											 card_flag=kacaozuo(card_num);
											 //卡片已经解锁
											 if(card_flag==7){
												 update_sql(card_num,7);
												 printf("card yijing jiesuo!\n");
												 test_num[0]=0x22;
												 test_num[1]=0x01;
												 break;
											 }
											 //异常
											 else{
												 printf("card yichan\n");
												 test_num[0]=0x22;
												 test_num[1]=0x02;
												 break;
											 }
										}
									}
											chages_b_s(test_num,a_buff,4);
											tcp_sendMessage(a_buff,tcp_socket);	
											playmusic(bobaoyuying);
						 }	
					   //查看密码
					 else if(get_data[0]==0x33){
						   memset(&card_num[0],0,4*sizeof(unsigned char));
						   test_num[0]=0x34;
						   while(1){	
									status=PcdRequest(0x52,&s);    //搜索卡片类型
										if(status==MI_OK)status=PcdAnticoll(card_num);  //读卡号
										if(status==MI_OK)status=PcdSelect(card_num);    //选卡				
										if(status==MI_OK){
											 card_flag=kacaozuo(card_num);				
											 if(card_flag==6){
												status=PcdAuthState(PICC_AUTHENT1A,1,key,card_num);	
												status=PcdRead(1,onum);
												 if(status==MI_OK){
													 test_num[0]=0x33;
													 test_num[1]=onum[0];
													 test_num[2]=onum[1];
													 test_num[3]=onum[2];
													 printf("wuyu:  %x %x %x\n",test_num[1],test_num[2],test_num[3]);
													 break;
												 }
									            else{
													
													break;
												}  
											 }
											 //异常
											 else{
												 printf("see mima error !\n");
												 break;
											 }
										}
									}
							chages_b_s(test_num,a_buff,4);
							tcp_sendMessage(a_buff,tcp_socket);	
							playmusic(bobaoyuying);		
					   }
					    //设置新的密码
					 else if(get_data[0]==0x44){
						   memset(&card_num[0],0,4*sizeof(unsigned char));
						   test_num[0]=0x45;
						   while(1){	
									status=PcdRequest(0x52,&s);    //搜索卡片类型
										if(status==MI_OK)status=PcdAnticoll(card_num);  //读卡号
										if(status==MI_OK)status=PcdSelect(card_num);    //选卡				
										if(status==MI_OK){
											 card_flag=kacaozuo(card_num);				
											 if(card_flag==6){
												status=PcdAuthState(PICC_AUTHENT1A,1,key,card_num);	
												onum[0]=get_data[1];
												onum[1]=get_data[2];
												onum[2]=get_data[3];
												printf("%x %x %x\n",onum[0],onum[1],onum[2]);
												status=PcdWrite(1,onum); 
												 if(status==MI_OK){
													 test_num[0]=0x44;
													 test_num[1]=0x01;
													 printf("genggai mima chenggou!\n");
													 break;
												 }
									            else{
													break;
												}  
											 }
											 //异常
											 else{
												 printf("genggai mima error !\n");
												 break;
											 }
										}
									}
							chages_b_s(test_num,a_buff,4);
							tcp_sendMessage(a_buff,tcp_socket);	
							playmusic(bobaoyuying);		
					   }
					    //添加来宾卡
					 else if(get_data[0]==0x55){
						   memset(&card_num[0],0,4*sizeof(unsigned char));
						  
						   while(1){	
									status=PcdRequest(0x52,&s);    //搜索卡片类型
										if(status==MI_OK)status=PcdAnticoll(card_num);  //读卡号
										if(status==MI_OK)status=PcdSelect(card_num);    //选卡				
										if(status==MI_OK){
											if(kacaozuo(card_num)==9){	
												input_sql(card_num,2);  //添加来宾卡
												 test_num[0]=0x55;
												 printf("add laibin success!\n");
												break;
											}
											else{
												//小区已经存在该卡片
												test_num[0]=0x56;
												printf("add laibin error!\n");
												break;
											}
										}
											 
									}
								chages_b_s(test_num,a_buff,4);
								tcp_sendMessage(a_buff,tcp_socket);	
								playmusic(bobaoyuying);		
							}
						//添加住户卡
				     else if(get_data[0]==0x66){
						   memset(&card_num[0],0,4*sizeof(unsigned char));
						   
						   while(1){	
									status=PcdRequest(0x52,&s);    //搜索卡片类型
										if(status==MI_OK)status=PcdAnticoll(card_num);  //读卡号
										if(status==MI_OK)status=PcdSelect(card_num);    //选卡				
										if(status==MI_OK){
											 if(kacaozuo(card_num)==9){	
												input_sql(card_num,1);   //添加住户卡
												test_num[0]=0x66;
												 printf("add zhuhu  success!\n");
												break;
											}
											else{
												//小区已经存在该卡片
												test_num[0]=0x67;
												 printf("add zhuhu error!\n");
												break;
											}
										} 
									}
								chages_b_s(test_num,a_buff,4);
								tcp_sendMessage(a_buff,tcp_socket);	
								playmusic(bobaoyuying);		
							}
										
					 else{
						
					      }
					}
				}
	} 
	
	bcm2835_aux_spi_end();
	bcm2835_close();
	return 0;
}