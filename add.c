#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>

void* func1(void* p){

    int *ptr = (int*)p;
    int sum = 0;
    for(int i=0;i<1000;i++){
        sum += ptr[i];
    }
    pthread_exit(&sum);
}

int main(){
    time_t start, end;
    time(&start);
    int nums[1000] ;
    for(int i=0;i<1000;i++){
        nums[i] = i;  
    }
    pthread_t t1;
    pthread_create(&t1, NULL, func1, nums);
    int *ptr1;
    pthread_join(t1, (void**)(&ptr1));
    int res = *ptr1;
    printf("sum = %d \n", res);
    time(&end);
    printf("time = %f \n", difftime(end, start));
    return 0;
}