#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char **argv) {

    pid_t pid = fork();
    pid_t terminated_pid;
    if (pid > 0) {
        printf("I am a parent process (pid: %d)\n", getpid());
        printf("My child process's process ID is %d\n", pid);

        // wait option A
        terminated_pid = wait(NULL);
        printf("A child process (pid: %d) has been terminated.\n", terminated_pid);

//        // wait option B
//        terminated_pid = waitpid(pid, NULL, 0);
//        printf("A child process (pid: %d) has been terminated.\n", terminated_pid);

    } else if (pid == 0) {
        printf("I am a child process (pid: %d)\n", getpid());
        printf("My parent's process ID is %d\n", getppid());

    } else {
        printf("Failure creating child process (error number: %d)\n", errno);
    }

    return 0;
}