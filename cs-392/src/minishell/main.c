#include "minishell.h"


void intHandler(int sig)
{
	my_char('\n');
}

int main(int argc, char **argv)
{
	int n;
	int pid = 0;
	char* s = (char*)malloc(256*sizeof(char));
   	char cwd[1024];
	char** input;
	/*int cancelled = 0;*/

	while (1)
	{
		signal(SIGINT, intHandler);
		/*if (cancelled)
			my_str("MINISHELL: Error. Program does not exist in current directory.\n");
		my_str("Loop Starts\n");
		cancelled = 0;*/

		my_str("MINISHELL:");

  		if (getcwd(cwd, sizeof(cwd)) != NULL)
			my_str(cwd);

		else
		{
			my_str("Error in current directory");
			return -1;
		}

		my_str(" $: ");
		n = read(0, s, 256);
		s[n] = '\0';

		if (n > 1)
		{
			input = my_str2vect(s);
			if ((my_strlen(input[0]) == 2) && (my_strcmp(input[0], "cd") == 0))
			{
				/*CHANGE DIRECTORY*/
				if (input[1] != '\0')
				{
					if (chdir(input[1]) < 0)
						my_str("MINISHELL: Error in path. Make sure the directory exists.\n");
				}

				else
					my_str("MINISHELL: Error. No directory specified.\n");
			}

			else if ((my_strlen(input[0]) == 4) && (my_strcmp(input[0], "help") == 0))
			{
				/*HELP*/
				my_str("\nMINISHELL COMMANDS:\n\ncd *directory\nChanges the current working directory to *directory\n\nexit\nExits the minishell\n\nhelp\nPrints a help message listing the built in commands\n\n");
			}

			else if ((my_strlen(input[0]) == 4) && (my_strcmp(input[0], "exit") == 0))
			{
				/*EXIT*/
				my_str("Thank you for using MINISHELL\n");
				exit(0);
			}

			else if (input[0] != NULL)
			{
				/*EXECUTE AN EXTERNAL PROGRAM*/
				if ((pid = fork()) < 0)
					my_str("MINISHELL: Error forking\n");

				else if (pid > 0)
				{
					wait(NULL);
				}

				else
				{
					if (execvp(input[0], input) < 0)
					{
						my_str("MINISHELL: Error. Program does not exist in current directory.\n");
						exit(0);
					}
				}
			}

			else
			{
				my_str("MINISHELL: Error reading command. Type help to see available commands.");
			}
		}
	}

	return 0;
}
