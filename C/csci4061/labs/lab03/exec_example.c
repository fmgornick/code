#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    pid_t pid1;
    pid_t pid2;
    pid_t pid3;
    pid_t pid4;
    pid_t pid5;

    pid1 = fork();
    if (pid1 == 0) {
        execl("/bin/echo", "/bin/echo", "hello", "execl", NULL);
        printf("Error executing execl()\n");
        exit(0);
    }

    pid2 = fork();
    if (pid2 == 0) {
        execlp("echo", "echo", "hello", "execlp", NULL);
        printf("Error executing execlp()\n");
        exit(0);
    }

    pid3 = fork();
    if (pid3 == 0) {
        char *args[] = {"/bin/echo", "hello", "execv", NULL};
        execv(*args, args);
        printf("Error executing execv()\n");
        exit(0);
    }

    pid4 = fork();
    if (pid4 == 0) {
        char *args[] = {"echo", "hello", "execvp", NULL};
        execvp(*args, args);
        printf("Error executing execvp()\n");
        exit(0);
    }

    printf("Parent process (pid: %d) spawned 4 child processes.\n", getpid());

    pid_t terminated_pid;
    while((terminated_pid = wait(NULL)) > 0) {
        printf("Terminated a child process (pid: %d)\n", terminated_pid);
    }

    return 0;
}
