#include <stdio.h>
#include <string.h>

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

int main(void) {
    char line[MAX_LINES];
    char *argv[MAX_ARGS];

    while(1){
        printf("MALAOS@linux $  ");
        fflush(stdout);

        if(fgets(line, sizeof(line), stdin) == NULL){
            printf("\n");
            break;
        }
        int argc = tokenize(line, argv);
        if(argc == 0) continue;

        printf("You typed: \n");
        for(int i = 0; i < argc; i++){
            printf(" [%d] '%s'\n", i, argv[i]);
        }

    }

    return 0;
}

