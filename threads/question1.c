/*
 * Author: Simon Junior Boateng
 * Assignment: Lab 1
 * Question 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <number_of_processes>\n", argv[0]);
        return 1;
    }

    int num_processes = atoi(argv[1]);
    if (num_processes <= 0)
    {
        fprintf(stderr, "Number of processes should be a positive integer.\n");
        return 1;
    }

    pid_t pid;
    for (int i = 0; i < num_processes; i++)
    {
        pid = fork(); // Create a new process
        if (pid == 0)
        {
            printf("Hello Child %d with pid = %d from [parent pid = %d]\n", i + 1, getpid(), getppid());
            exit(0);
        }
        
        else if (pid > 0)
        {
            wait(NULL); // Parent process waits for the child process to finish
        }
        else
        {
            perror("Error creating child processes");
            return 1;
        }
    }

    return 0;
}
