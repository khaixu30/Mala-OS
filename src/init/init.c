#include <unistd.h>

int main(void) {
    write(1, "Hello, World! I'm Mala-OS, and this is my root process, PID 1.\n", 63);
    while (1)
    {
        pause();
    }

    return 0;
}