#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <string.h>

static volatile sig_atomic_t child_exited = 0;

void handle_sigchild(int sig) {
    (void)sig;
    child_exited = 1;   // Just set a flag, never do real work inside handler!!
}

int main(void) {
    write(1, "My INIT: starting up PID: 1\n", 29);

    // Mount the kernel-provided virtual filesystems
    if(mount("proc", "/proc", "proc", 0, NULL) != 0) {
       perror("mount /proc failed.");
    } else if(mount("sysfs", "/sys", "sysfs", 0, NULL) != 0) {
        perror("mount /sys failed.");
    } else {
        write(1, "MY INIT: /proc and /sysfs mounted.\n", 35);
    }


    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_sigchild;
    sigaction(SIGCHLD, &sa, NULL);

    pid_t pid = fork();
    if(pid == 0) {
        execl("/bin/child_program", "child_program", NULL);
        _exit(1);
    } else if (pid > 0) {
        write(1, "MY INIT: launched child_program\n", 32);
    } else {
        write(2, "MY INIT: fork failed\n", 21);
    }

    while(1) {
        pause();
        if(child_exited) {
            child_exited = 0;

            int status;

            pid_t reaped;
            while((reaped = waitpid(-1, &status, WNOHANG)) > 0) {
                char msg[64];
                int len = snprintf(msg, sizeof(msg), "MY INIT: reaped %d\n", reaped);
                write(1, msg, len);
            }
        }
    }

    return 0;
}