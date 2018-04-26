#include <stdio.h>  
#include <stdlib.h>  
#include <sqlite3.h> 
#include <string.h>
#include <unistd.h>
#include "shujuku.h"


//#define _debug_

//查找卡号
int findsql(unsigned char *num,char *cishu){
	unsigned char card[9] ;
	char sql[300];
	sqlite3 *db=NULL;  
	int rc; 
	char **azResult=NULL; //二维数组存放结果  
	int nrow=0;  
    int ncolumn = 0; 
    char buf[2];

	chage(num, card, 4);
	char *str = (char *)card;
	//打开指定的数据库文件,如果不存在将创建一个同名的数据库文件  
	rc = sqlite3_open("/home/pi/malu/test.db", &db);  
	if( rc )  
	{  
		fprintf(stderr, "Can't open database: %s/n", sqlite3_errmsg(db));  
		sqlite3_close(db);  
		return 1;  
	}
	
	sprintf(sql,"%s%s%s","select sid from rfid where card ='",str,"';");
	sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn ,NULL );
	

#ifdef _debug_
	int i;
    printf( "row:%d column=%d\n " , nrow , ncolumn );  
    for( i=0 ; i<( nrow + 1 ) * ncolumn ; i++ )  
    {  
        printf( "azResult[%d] = %s\n", i , azResult[i] );  
    } 
#endif

	sqlite3_free_table(azResult);
	
	if((nrow==0)&&(ncolumn==0)){
		return 0;
	}
	else{
		  stpcpy(buf,azResult[1]);
		  if(buf[0]>=0x30)
				cishu[0]=buf[0]-0x30;
	}
	
	sqlite3_close(db);
	return 1;
}



//解锁 （在数据库中，添加卡号信息）
//用户卡 还是 来宾卡
// unsigned char *num   4个字节的卡号
// unsigned char xuanze    1 为住户卡  2为来宾卡
int input_sql(unsigned char *num,unsigned char xuanze){
	unsigned char card[9] ;
    char sql[300];
    sqlite3 *db=NULL;  
    int rc;

    chage(num, card, 4);
    char *str = (char *)card;

    //打开指定的数据库文件,如果不存在将创建一个同名的数据库文件  
    rc = sqlite3_open("/home/pi/malu/test.db", &db);  
    if( rc )  
    {  
        fprintf(stderr, "Can't open database: %s/n", sqlite3_errmsg(db));  
        sqlite3_close(db);  
        return 1;  
    }  
    //插入最后的数据
    memset(sql, '\0', 300);
	//住户卡
	if(xuanze==1){
		sprintf(sql, "%s%s%s","insert into rfid(sid,card)values(6,'",str,"');");
    }
	//来宾卡
	if(xuanze==2){
		sprintf(sql, "%s%s%s","insert into rfid(sid,card)values(4,'",str,"');");
	}
	sqlite3_exec(db, sql, NULL, NULL, NULL); 

    //关闭数据库     
    sqlite3_close(db);  
	return 0;
}


//更新次数 -1
int update_sql(unsigned char *num,unsigned char count){
	unsigned char card[9] ;
    char sql[300];
    sqlite3 *db=NULL;  
    int rc;

    chage(num, card, 4);
    char *str = (char *)card;

    //打开指定的数据库文件,如果不存在将创建一个同名的数据库文件  
    rc = sqlite3_open("/home/pi/malu/test.db", &db);  
    if( rc )  
    {  
        fprintf(stderr, "Can't open database: %s/n", sqlite3_errmsg(db));  
        sqlite3_close(db);  
        return 1;  
    }  
    //插入最后的数据
    memset(sql, '\0', 300);
	//住户卡
	if(count>1){	
	sprintf(sql, "%s%d%s%s%s", "update rfid set sid =", count-1," where card = '",str,"';");
	}
	else{
	sprintf(sql, "%s", "delete from rfid where sid = 1;");	
	}
	
	sqlite3_exec(db, sql, NULL, NULL, NULL); 

    //关闭数据库     
    sqlite3_close(db);  
	return 0;
	
	
}


//数组装换成字符串
void chage(const unsigned char *card_num, unsigned char *card_string,int len)
{
	int i;
    char S_num[3];
	for (i = 0; i < len; ++i) {
		sprintf(S_num,"%02x", card_num[i]);
		memcpy(&card_string[i * 2], S_num, 3);
	}
}
