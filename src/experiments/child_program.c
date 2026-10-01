#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("I'm the real child program launched by my init with PID %d\n", getpid());

    for(int i = 0; i < 10; i++) {
        printf("...still alive, tick [%d]", i);
        sleep(1);
    }
    printf("Child exited normally.\n");
    return 0;
}