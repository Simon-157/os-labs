#include<stdio.h>
#include<signal.h>
#include <unistd.h>
 
int main()
{
 
 int pid = getpid();
 printf("%d", pid);
    
    printf("Program to sleep for 10 second in Linux.\n");
 
    sleep(100000);
   
    printf("This line will be executed after 10 second.");
 
    return 0;
}