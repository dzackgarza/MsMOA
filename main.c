#include "header.h"
/* Steps:
1 - Fetch
2 - Tokenize
3 - Fork
4 - Exec
5 - Wait
*/

////	The important stuff!	////

int main(int argc, char *argv[]) 
{
	FILE *input = stdin;
		// Used to keep track of which buffer should be read in (added for scripting purposes)
	char *tokens[100]; 
		// An array storing argvs for the program to be executed
	char commands[80]; // Stores the string entered on the 'command line'
		// Note - command must be kept intact due to the way strtok functions!
	int times_run = 0;

	printf("Welcome to the terminal.\n");
	catch_signals();


	do
	{

		if (times_run >= 1) 
		{
			commands[strlen(commands) - 1] = '\0';
			tokenize(commands, tokens);
			check_commands(tokens);
		}
		pid_t pid = fork();
		if(pid > 0) 
		{ 	// Parent; prompt for new command
			printf(">");
			if (argc > 1 && times_run == 0) 
			{
				FILE *script = fopen(argv[1], "r");
				input = script;
				times_run++;
				continue;
			}
			
			
			int status;
			wait(&status);
			times_run++;
		}

		else if (pid == 0 && times_run >=1) 
		{ 	// This program is child process
			if (execvp(tokens[0], tokens) == -1) 
			{
				error("Unable to run command, please try again.");
			}
		}	

		else //if (pid < 0)
		{				// Error, quit child process
			exit(1);
		}

	} while (fgets(commands, 100, input) != NULL);

	return 0;
}

void get_commands(char commands[80])
	// Call this function to read in commands
{
	
}

int check_commands(char *tokens[100])
	// Accepts a token array and checks to see if the command entered matches a built-in command.
	// Returns a 1 (true) if the command is built in, otherwise returns 0 (false)
{
	if (strcmp(tokens[0], "exit") == 0) 
		{ quit(); return 1; }
	else if (strcmp(tokens[0], "cd") == 0) 
		{ chdir(tokens[1]); printf(">"); return 1; }
	else return 0;

}

void tokenize(char commands[80], char *tokens[100])
	// Takes a pointer to a space to store a token array and a pointer to the command string ,
	// converts the command into tokens, and adds them into the token array.
{
	int i = 0;	
	tokens[i] = strtok(commands, " "); 
			// Stores first command, ie program name
	while(tokens[i]) 
	{		// Fetches arguments
		i++;
		tokens[i] = strtok(NULL, " ");
	}
}

/* void execute(char *tokens[100], int *argc, int *called_with_script) 
	// Takes an array of argvs and uses them to start a child process
{
	pid_t pid = fork();
	if (pid == 0) 
		{ 	// This program is child process
			if (execvp(tokens[0], tokens) == -1) 
			{
				error("Unable to run command, please try again.");
			}
		}

		else if(pid > 0) 
		{ 	// Parent; prompt for new command
			if (argc > 1) {
				called_with_script = 1;
			}
			printf(">");
			int status;
			wait(&status);
		}

		else 
		{				// Error, quit child process
			error("Unable to fork process.");
		}
}
*/


////	Error handling and signal processing	////

void error(const char *error_message) 
	// Pass this function an error message to gracefully exit
{	
	fprintf(stderr, "%s: %s\n", error_message, strerror(errno));
	exit(1);
}

void catch_signals() 
{
	if (catch_signal(SIGINT, graceful_exit) == -1) 

	{
		puts("Error: Unable to map handler");
		exit(2);
	}
}

int catch_signal(int sig, void (*handler) (int)) 
{
	struct sigaction action;
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	return sigaction (sig, &action, NULL);
}

void graceful_exit(int sig)
{
	puts("\nIgnored!");
}

void quit()
	// Function to display "goodbye" message
	// #TODO: Can this be combined with other exit handlers?
{
	printf("Thanks for using the best terminal ever!\n");
	exit(0);
}
