#include <stdio.h>
#include <unistd.h>

int main()
{
    int pipefds1[2], pipefds2[2];
    int returnstatus1, returnstatus2;
    int pid;
    returnstatus1 = pipe(pipefds1);

    if (returnstatus1 == -1)
    {
        printf("Unable to create pipe 1 \n");
        return 1;
    }
    returnstatus2 = pipe(pipefds2);

    if (returnstatus2 == -1)
    {
        printf("Unable to create pipe 2 \n");
        return 1;
    }
    pid = fork();
    if (pid != 0) // Parent process
    {
        close(pipefds1[0]); // Close the unwanted pipe1 read side
        close(pipefds2[1]); // Close the unwanted pipe2 write side
        int pipe1writemessage = {2, 3, 4, 5};
        int sum;
        printf("In Parent: Writing to pipe 1 – Message is %s\n", pipe1writemessage);
        write(pipefds1[1], pipe1writemessage, sizeof(pipe1writemessage)); // Write the array to pipe1

        read(pipefds2[0], &sum, sizeof(sum)); // Read the sum from pipe2
        printf("In Parent: Reading from pipe 2 – Message is %d\n", sum);
        close(pipefds1[1]); // Close the pipe1 write side
        close(pipefds2[0]); // Close the pipe2 read side
    }
    else // Child process
    {
        close(pipefds1[1]); // Close the unwanted pipe1 write side
        close(pipefds2[0]); // Close the unwanted pipe2 read side
        int readmessage1[4];
        read(pipefds1[0], readmessage1, sizeof(readmessage1)); // Read the array from pipe1
        int sum = 0;
        for (int i = 0; i < 4; i++)
        {
            sum += readmessage1[i]; // Sum the array
        }

        printf("In Child: Writing to pipe 2 – Message is %d\n", sum);
        write(pipefds2[1], sum, sizeof(sum)); // Write the sum to pipe2
    }
    return 0;
}