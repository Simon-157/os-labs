#include<stdio.h>
#include<pthread.h>
#include<unistd.h>


int num1 = 3;
int num2 = 4;

void *myfunc1(void* param1){
    pthread_exit(&num1);
}


void *myfunc2(void* param2){
    pthread_exit(&num2);
}


int main(){
    pthread_t t1, t2;
    int j1=3, j2=4;
    int *ptr1, *ptr2;
    pthread_create(&t1, NULL, myfunc1, j1);
    pthread_create(&t2, NULL, myfunc2, j2);
    pthread_join(t1, (void**)(&ptr1));
    pthread_join(t2, (void**)(&ptr2));

    printf("num1 = %d \n", *ptr1);
    printf("num2 = %d \n", *ptr2);
    return 0;
}