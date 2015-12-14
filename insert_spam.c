/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <regex.h>
#include "insert_spam.h"

#define FILE_NAME "sample.txt"

char regex_address(void);
char regex_header(void);
char regex_body(void);

void mail_insert(){
	MYSQL *conn = NULL;
	MYSQL_RES *resp = NULL;
	MYSQL_ROW row;
	char sql_str[256];
	char *sql_serv	=	"localhost";
	char *user		="root";
	char *password	=	"";
	char *db_name 	=	"spam_system";

	//address,header,body部を格納
	char *address = (char*)malloc(sizeof(char)*1024);
	char *header  = (char*)malloc(sizeof(char)*1204);
	char *body   = (char*)malloc(sizeof(char)*1024);

	memset(&sql_str[0],0x00,sizeof(sql_str));

	//mysql接続
	conn = mysql_init(NULL);
	if(!mysql_real_connect(conn,sql_serv,user,password,db_name,0,NULL,0)){
		//error
		exit(-1);
	}

	address = regex_address();
	header 	= regex_header();
	body 	= regex_body();	

	//クエリ発行
	snprintf(&sql_str[0],sizeof(sql_str)-1,"insert into data(address,header,body) values(%s,%s,%s)",address,header,body);
	if(mysql_query(conn,&sql_str[0])){
		mysql_close(conn);
		exit(-1);
	}

	resp = mysql_use_result(conn);
	while((row = mysql_fetch_row(resp)) != NULL){
		printf("%d : %c\n",atoi(row[0]),row[1]);
	}

        free(address);
        free(header);
        free(body);
        
	mysql_free_result(resp);
	mysql_close(conn);
	return 0;
}

char regex_address(){
    const char* re = "";//正規表現パターン
    FILE *fp;           
    char *fname = FILE_NAME;
    char s[1024];
    
    regex_t preg;
    regmatch_t pattern[3];
    
    if(regcomp(&preg,re,REG_EXTENDED|REG_NEWLINE)!=0){
        printf("regex compile failed.\n");
        exit(-1);
    }
    
    if(regexec(&preg)!=0){
        
    }
    
}

char regex_header(){
    
}

char regex_body(){
    
}