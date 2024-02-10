/*
 * Author: Simon Junior Boateng
 * Assignment: Lab 1
 * Question 2
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void createProcessChain(int depth, int current);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_processes>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int numProcesses = atoi(argv[1]);

    if (numProcesses <= 0) {
        fprintf(stderr, "Number of processes should be greater than 0\n");
        exit(EXIT_FAILURE);
    }

    createProcessChain(numProcesses, 1);

    return 0;
}


void createProcessChain(int depth, int current) {
    pid_t pid;

    if (current <= depth) {
        pid = fork();

        if (pid == -1) {
            perror("error creating child processess");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            if (current < depth) {
                createProcessChain(depth, current + 1); // Recursive call for the next level of the chain
            }
            printf("Hello Child with PID %d from parent with PID %d\n", getpid(), getppid());
            exit(EXIT_SUCCESS);
        } else { 
            wait(NULL); // Parent process waits for the child process to finish
        }
    }
}