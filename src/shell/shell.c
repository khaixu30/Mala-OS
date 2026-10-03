#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINES 1024
#define MAX_ARGS 64

int tokenize(char *line, char **argv) {
    int argc = 0;
    char *tok = strtok(line, " \t\n");
    while(tok != NULL && argc < MAX_ARGS - 1){
        argv[argc++] = tok;
        tok = strtok(NULL, " \t\n");
    }
    argv[argc] = NULL;
    return argc;
}

int try_builtin(char **argv, int argc, int *should_exit) {
    if(argc == 0) return 1;

    if(strcmp(argv[0], "exit") == 0){
        *should_exit = 1;
        return 1;
    }

    if(strcmp(argv[0], "cd") == 0){
        const char *target  = (argc > 1) ? argv[1] : getenv("HOME");
        if(target == NULL) target = "/";
        if(chdir(target) != 0) {
            perror("cd");
        }
        return 1;
    }

    return 0;
}

void run_external(char **argv) {
    pid_t pid = fork();
    if(pid == 0) {
        execvp(argv[0], argv);
        fprintf(stderr, "MALAOS: %s: not a command\n", argv[0]);
        _exit(127);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    } else {
        perror("fork");
    }
}

int main(void) {
    char line[MAX_LINES];
    char *argv[MAX_ARGS];
    int should_exit = 0;

    while(!should_exit){
        printf("MALAOS@linux $  ");
        fflush(stdout);

        if(fgets(line, sizeof(line), stdin) == NULL){
            printf("\n");
            break;
        }
        int argc = tokenize(line, argv);
        if(argc == 0) continue;

        if(!try_builtin(argv, argc, &should_exit)) {
            run_external(argv);
        }

    }

    return 0;
}

