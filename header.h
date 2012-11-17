#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int main();
void quit();
void get_command(char *tokens[100], char commands[80]);
void execute(char *tokens[100]);
