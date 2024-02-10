#include <stdio.h>
#include<unistd.h>
#include <sys/types.h>


int main(){
    printf("--beginning \n");
    int counter = 0;
    pid_t pid = fork();

    if(pid == 0){
        int i = 0;
        for(;i<6;i++){
            printf("child process: counter = %d \n", ++counter);
        }
    }

    else if(pid > 0){
        int i = 0;
        for(;i<6;i++){
            printf("parent process: counter = %d \n", ++counter);
        }
  
    }

    else{
       printf("process creation failed ");
       return 1;
    }

    return 0;
    
}