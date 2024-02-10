#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[MAX_BUFFER_SIZE];

    // Create client socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("failed to create a socket for the client");
        exit(EXIT_FAILURE);
    }

    // Setting up server address structure for the client which is same for the server
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8888);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("client connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    while (1) {
        // Get number input from the client
        printf("Enter a number (type 'exit' to quit): ");
        fgets(buffer, MAX_BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline

        // Sending number to the server
        send(client_socket, buffer, strlen(buffer), 0);

        // Check for exiting condition
        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // Receiving and display the updated accumulator response from the server
        recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
        printf("Server response: %s\n", buffer);
    }

    // Close the client socket
    close(client_socket);

    return 0;
}
