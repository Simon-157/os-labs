#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>



#define MAX_CLIENTS 5
#define MAX_BUF_SIZE 1024
int GLOBAL_ACCUMULATOR = 0;

pthread_mutex_t mutex;
sem_t sem;

typedef struct {
    int client_socket;
    struct sockaddr_in client_addr;
} client_info;


void* handleclient(void* arg);
void sendmessage(int client_socket, char* message);
void receivemessage(int client_socket, char* buffer);


int main(){
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    pthread_t tid[MAX_CLIENTS];
    int i = 0;

    // initialize mutex and semaphore
    pthread_mutex_init(&mutex, NULL);
    sem_init(&sem, 0, 5);
  

    // create socket server
    if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Server failed to create socket");
        exit(EXIT_FAILURE);
    }

    // set up server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = INADDR_ANY;


    // binding the server socket to the specified address
    if(bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
        perror("Server failed to bind");
        exit(EXIT_FAILURE);
    }

    // listen for incoming connections
    if(listen(server_socket, MAX_CLIENTS) == -1){
        perror("Server failed to listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port 8888...\n");

    while(1){
         // Accept a new client connection
        if ((client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len)) == -1) {
            perror("Accept failed");
            continue;
        }
        // Create a thread to handle the client
        if (pthread_create(&tid[i], NULL, handleclient, (void*)&client_socket) != 0) {
            perror("Thread creation failed");
            close(client_socket);
        }

        // Increment the thread index
        i = (i + 1) % MAX_CLIENTS;
    }

    // close server socket and destroy mutex and semaphore
    close(server_socket);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem);

    return 0;
}


void sendmessage(int client_socket, char* message){

    if(send(client_socket, message, strlen(message), 0) == -1){
        perror("Server failed to send message");
        exit(EXIT_FAILURE);
    }

}


void receivemessage(int client_socket, char* buffer){
   if(recv(client_socket, buffer, MAX_BUF_SIZE, 0) == -1){
        perror("Server failed to receive message");
   }
}


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void *handleclient(void* arg){
    int client_socket = *((int*)arg);
    char buffer[MAX_BUF_SIZE];
    
    // get client address
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    getpeername(client_socket, (struct sockaddr*)&client_addr, &client_addr_len);
    printf("connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    while(1){
        // receive number message from client
        receivemessage(client_socket, buffer);
        printf("Received from %s:%d:%s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);

        // processing the message to update the GLOBAL_ACCUMULATOR
        int num = atoi(buffer);
        pthread_mutex_lock(&lock);
        GLOBAL_ACCUMULATOR += num;
        pthread_mutex_unlock(&lock);
        printf("GLOBAL_ACCUMULATOR = %d\n", GLOBAL_ACCUMULATOR);
        
        // converting GLOBAL_ACCUMULATOR to string
        char acc_str[MAX_BUF_SIZE];
        sprintf(acc_str, "%d", GLOBAL_ACCUMULATOR);

        // sending sum response to client
        sendmessage(client_socket, acc_str);
        printf("Sent to %s:%d:%s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), acc_str);
        sleep(1);
    }

    close(client_socket);
    free(arg);
    pthread_exit(NULL);
}