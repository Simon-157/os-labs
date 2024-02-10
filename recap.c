#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{

    for (int i = 0; i < 3; i++)
    {
        pid_t pid = fork();

        if (pid == 0)
        {
            printf("Child pid %d = %d \n",i, getpid());
            exit(0);
        }
        else if (pid > 0)
        {
            printf("Parent pid = %d \n", getpid());
        }
    }
}