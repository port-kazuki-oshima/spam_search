#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "insert_spam.h"

int main(int argc,char** argv[]){

    //子プロセス生成
    pid_t pid = fork();
    int a;
    
    while(1){
        
        if(a == 1){
            
        }
        
        
        
        if(pid < 0){
            perror("fork");
            exit(-1);
        }else if(pid == 0){
            insert_spam();
        }
    }
    
}