#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
int main(int argc, char * argv[]);
void quit();
void tokenize (char commands[80],  char *tokens[100]);
void execute(char *tokens[100]);
void error(const char *error_message);
void graceful_exit(int sig);
int catch_signal(int sig, void (*handler) (int));
int check_commands(char *tokens[100]);
void get_commands(char commands[100]);
void catch_signals();