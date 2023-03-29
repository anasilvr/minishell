#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
// #include <readline/readline.h>
// #include <readline/history.h>
# include "../include/readline/readline.h"
# include "../include/readline/history.h" 
volatile sig_atomic_t g_sigint_received = 0;

void sigint_handler(int signum)
{
    (void) signum;
    g_sigint_received = 1;
}

int main(void)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sigint_handler;
    sigaction(SIGINT, &sa, NULL);

    char *line;
    while (!g_sigint_received && (line = readline("prompt> ")) != NULL) {
        // Process the line...
        add_history(line);
        free(line);
    }

    if (g_sigint_received) {
        printf("Received SIGINT, exiting...\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}