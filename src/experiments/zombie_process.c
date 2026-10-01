/***
 * This is the demo/experiment to demonstrate zombie process.
 * Zombie process: Process that has been exited but it's parent hasn't called wait on it yet.
 * Just compile this following code and then run 'ps' command in another terminal to actually see the zombie process.
 * Zombie process has <defunct> at the end. It represents that the process has become a zombie.
 */

#include <stdio.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();
    if(pid == 0){
        _exit(0);
    }

    printf("Parent PID %d, child PID %d has exited but i haven't wait()ed yet.\n", getpid(), pid);
    printf("Check 'ps' in another terminal now - look for a <defunct> entry.\n");
    sleep(15);
    return 0;
}