#include "header.h"
/* Steps:
1 - Fetch
2 - Tokenize
3 - Fork
4 - Exec
5 - Wait
*/
void quit() {
	printf("Thanks for using the best terminal ever!\n");
	exit(0);
}

void get_command(char *tokens[100], char commands[80]) {
	// Takes a pointer to a space to store a token array and a pointer to the command string ,
	// converts the command into tokens, and adds them into the token array.
	fgets(commands, 100, stdin);
	commands[strlen(commands) - 1] = '\0';
		// Gets input from stdin and removes newline.

	if (strcmp(commands, "exit") == 0) quit();

	int i = 0;	
	tokens[i] = strtok(commands, " "); // Stores first command, ie program name
	while(tokens[i]) { // Fetches arguments
		i++;
		tokens[i] = strtok(NULL, " ");
	}
}


void execute(char *tokens[100]) {
	// Takes an array of argvs and uses them to start a child process
	pid_t pid = fork();
		if (pid == 0) { 	// This program is child process
			if ( execvp(tokens[0], tokens) == -1) {
				printf("Exec failed: %s\n", strerror(errno));
				exit(1);
			}
		}
		else if(pid > 0) { 	// Parent; prompt for new command
			printf("> ");
			wait();
		}
		else {				// Error, quit child process
			printf("Error: %s\n", strerror(errno));
			exit(1);
		}
}

int main() {
	printf("Welcome to the terminal.\n>");

	while(1) {
		char *tokens[100]; // An array storing argvs for the program to be executed
		char command[80]; // Stores the string entered on the 'command line'
			// Note - command must be kept intact due to the way strtok functions!
		get_command(tokens, command);
			// Passes in the addresses of these pointers so their values persist
		execute(tokens);
		
	}

	return 0;
}
