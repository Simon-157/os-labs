#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>

#define MAX_SIZE 1000

int array[MAX_SIZE];
int part = 0;

void* sum_array(void* arg) {
    int thread_part = part++;
    int sum = 0;
    for (int i = thread_part * (MAX_SIZE / 4); i < (thread_part + 1) * (MAX_SIZE / 4); i++)
        sum += array[i];
    return sum;
}

int sum_without_threads(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return sum;
}

int sum_with_threads(int arr[], int n) {
    pthread_t threads[4];
    for (int i = 0; i < 4; i++)
        pthread_create(&threads[i], NULL, sum_array, (void*)NULL);
    int total_sum = 0;
    for (int i = 0; i < 4; i++) {
        int sum;
        pthread_join(threads[i], (void**)&sum);
        total_sum += sum;
    }
    return total_sum;
}

int main(){
    time_t start, end;
    int nums[1000] ;
    for(int i=0;i<1000;i++){
        nums[i] = i;  
    }

    // start = time(NULL);
    // int res = sum_without_threads(nums, 1000);
    // end = time(NULL);
    // printf("sum without threads = %d \n", res);
    // printf("time without threads = %f \n", difftime(end, start));

    start = time(NULL);
    res = sum_with_threads(nums, 1000);
    end = time(NULL);
    printf("sum with threads = %d \n", res);
    printf("time with threads = %f \n", difftime(end, start));
    
    return 0;
}