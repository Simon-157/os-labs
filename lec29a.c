#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void sigusr_handler(int signum) {
    printf("Received SIGUSR signal\n");

}

int main() {
    pid_t pid = getpid();
    printf("Process ID: %d\n", pid);
    signal(SIGUSR1, sigusr_handler);
    printf("Waiting for SIGUSR signal...\n");

    while (1) {
        sleep(1);
    }

    return 0;
}
