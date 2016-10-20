#include "nsminishell.h"
#include <stdio.h>
#include <string.h>

/*void intHandler(int sig)
{
	my_char('\n');
}*/

int main(int argc, char** argv)
{
	int n = 0;
	int pid = 0;
	char* s = (char*)malloc(256*sizeof(char));
   	char cwd[1024];
	char** input;
	int letter;
	int x;
	int y;
	int count = 0;
	int store = 0;
	FILE *file;
	FILE *tempf;
	char buff[255];
	char* cut = (char*)malloc(256*sizeof(char));
	char **cuts = (char**)malloc(256*sizeof(char*));
	int temp = 0;
	int index = 0;
	int cut_dex = 0;
	int paste_dex = 0;
	int c = 0;
	int history_pos = 0;
		

	/*int place;*/


	initscr();	
	refresh();
	clear();		/* Start curses mode 		  */
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();
	move(0, 0);


	while (1)
	{
		/*signal(SIGINT, intHandler);*/
		/*my_int(count);*/
		printw("MINISHELL:");
		refresh();

  		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			printw(cwd);
			refresh();
			store = (my_strlen(cwd) + 14);
		}

		else
		{
			printw("Error in current directory");
			refresh();
			return -1;
		}

		printw(" $: ");
		refresh();

		n = 0;

		while (s[n] != '\0')
		{
			s[n] = '\0';
			n++;
		}

		n = 0;

		while ((letter = getch()) != '\n')
		{
			/*endwin();
			printf("KEY NAME : %s - %d\n", keyname(letter),letter);*/

   			getyx(curscr, y, x);

			if (letter == KEY_LEFT)
			{
				if (x == 0)
				{
					move(y - 1, COLS - 1);
					refresh();
					n--;
				}
				else if(n > 0)
				{
					move(y, x - 1);
					refresh();
					n--;
				}
				else
				{
					move(y, x);
					refresh();
				}
			}

			else if (letter == KEY_RIGHT)
			{
				if (n >= count)
				{
					refresh();
				}
				else
				{
					if (x + 1 >= COLS)
					{
						move(y + 1, 0);
						refresh();
						n++;
					}
					else
					{
						move(y, x + 1);
						refresh();
						n++;
					}
				}
			}

			else if (letter == KEY_UP)
			{
				while (count > 0)
				{
					getyx(curscr, y, x);
					s[count] = '\0';
					count--;
					move(y, x - 1);
					delch();
					refresh();
				}

				count = 0;
				n = 0;
				move(y, store);
				temp = history_pos;
				file = fopen(".nsmshistory", "r");

				while (((c = getc(file)) != EOF))
				{
					if (c == '\n')
					{
						if (history_pos == 0)
							break;
						else
							history_pos--;
					}

					if (history_pos == 0)
					{
						if (c != '\n')
							addch(c);
						s[n] = c;
						n++;
						count++;
					}
				}

				history_pos = temp + 1;
				temp = 0;
				fclose(file);
			}

			else if (letter == KEY_DOWN)
			{
				while (count > 0)
				{
					getyx(curscr, y, x);
					s[count] = '\0';
					count--;
					move(y, x - 1);
					delch();
					refresh();
				}

				count = 0;
				n = 0;
				move(y, store);
				temp = history_pos;
				file = fopen(".nsmshistory", "r");

				while (((c = getc(file)) != EOF))
				{
					if (c == '\n')
					{
						if (history_pos == 0)
							break;
						else
							history_pos--;
					}

					if (history_pos == 0)
					{
						if (c != '\n')
							addch(c);
						s[n] = c;
						n++;
						count++;
					}
				}

				history_pos = temp - 1;
				temp = 0;
				fclose(file);
			}


			else if (letter == KEY_BACKSPACE)
			{
				index = 0;

				if (x == 0)
				{
					index = n;

					while (s[index + 1] != '\0')
					{
						s[index] = s[index + 1];
						index++;
					}

					s[index] = '\0';
					move(y - 1, COLS - 1);
					count--;
					delch();
					refresh();
					n--;
					index = 0;
				}

				else if (n > 0)
				{
					index = n;

					while (s[index + 1] != '\0')
					{
						s[index] = s[index + 1];
						index++;
					}

					s[index] = '\0';
					move(y, x - 1);
					count--;
					delch();
					refresh();
					n--;
				}

				else
				{
					move(y, x);
					refresh();
				}
			}

			/*else if (letter == ' ')
			{
				place = n;
				while(n < count)
				{
					n++;
				}
				while(n != place)
				{
					s[n++] = s[n];
					n--;
					move(y, place + 1);
					refresh();
				}
			}*/

			else if (strcmp(keyname(letter), "^L") == 0)
			{
				clear();
				refresh();
				printw("MINISHELL:");
				printw(cwd);
				printw(" $: ");
				printw(s);
				count = my_strlen(s);
				n = count;
			}

			else if (strcmp(keyname(letter), "^A") == 0)
			{
				move(y, store);
				refresh();

				n = 0;
			}

			else if (strcmp(keyname(letter), "^E") == 0)
			{
				/* DOES NOT WORK FOR OVER 2 LINES*/
				if (count < COLS - store)
					move(y, store + count - 1);

				else
					move((count + store) / COLS, count - (COLS - store) - 1);
					/*move(y + 1 + (count - (COLS - 1 - store)) / COLS, (count - (COLS * (count - (COLS -1 - store) / COLS))));*/

				refresh();

				n = count;
			}

			else if (strcmp(keyname(letter), "^W") == 0)
			{
				/*DOES NOT WORK*/
				if (n > 0)
				{
					temp = n;
					index = 0;

					while (s[temp] != ' ')
					{
						temp--;
					}

					while(temp + 1 < n)
					{
						cut[index] = s[temp];
						temp++;
						index++;
					}

					cut[index] = '\0';
					cuts[cut_dex] = (char*) malloc((my_strlen(cut) + 1) * sizeof(char));
					my_strcpy(cuts[cut_dex], cut);
					cut_dex++;
				}
			}

			else if (strcmp(keyname(letter), "^U") == 0)
			{
				/*DOES NOT WORK*/
				cuts[cut_dex] = (char*) malloc((my_strlen(s) + 1) * sizeof(char));
				my_strcpy(cuts[cut_dex], s);
				cut_dex++;

				while (count >= 0)
				{
					s[count] = '\0';
					count--;
				}

				n = 0;

			}

			else if (strcmp(keyname(letter), "^Y") == 0)
			{
				/*DOES NOT WORK*/
				index = 0;
				paste_dex = 0;

				if (cut_dex > 0)
				{
					while (cuts[index] != NULL)
					{
						while (cuts[index][paste_dex] != '\0')
						{
							addch(cuts[index][paste_dex]);
							count++;
							s[n] = cuts[index][paste_dex];
							n++;
							paste_dex++;
						}

						paste_dex = 0;
						index++;
					}
				}

				cut_dex = 0;
			}

			else
			{
				addch(letter);
				count++;
				s[n] = letter;
				n++;
				/*my_int(n);*/
				refresh();
			}
		}

		addch('\n');
		n = my_strlen(s);
		s[n] = '\0';

		file = fopen(".nsmshistory", "r");
		tempf = fopen(".temp", "w+");
		fclose(tempf);
		tempf = fopen(".temp", "a");

		if ((file != NULL) && (tempf != NULL))
		{
			while (((c = getc(file)) != EOF))
				fputc(c, tempf);
			fclose(file);
			fclose(tempf);
		}

		file = fopen(".nsmshistory", "w+");
		fclose(file);
		file = fopen(".nsmshistory", "a");
		tempf = fopen(".temp", "r");

		if ((file != NULL) && (tempf != NULL))
		{
			fputs(s, file);
			fputc('\n', file);
			while (((c = getc(tempf)) != EOF))
				fputc(c, file);
			fclose(file);
			fclose(tempf);
		}

		if (n >= 1)
		{
			input = my_str2vect(s);
			if ((my_strlen(input[0]) == 2) && (my_strcmp(input[0], "cd") == 0))
			{
				/*CHANGE DIRECTORY*/
				if (input[1] != '\0')
				{
					if (chdir(input[1]) == -1)
					{
						printw("MINISHELL: Error in path. Make sure the directory exists.\n");
						refresh();
					}
				}

				else
				{
					printw("MINISHELL: Error. No directory specified.\n");
					refresh();
				}
			}

			else if ((my_strlen(input[0]) == 4) && (my_strcmp(input[0], "help") == 0))
			{
				/*HELP*/
				printw("\nMINISHELL COMMANDS:\n\ncd *directory\nChanges the current working directory to *directory\n\nexit\nExits the minishell\n\nhelp\nPrints a help message listing the built in commands\n\n");
				refresh();
			}

			else if ((my_strlen(input[0]) == 4) && (my_strcmp(input[0], "exit") == 0))
			{
				/*EXIT*/
				printw("Thank you for using MINISHELL\n");
				endwin();
				fclose(file);
				exit(0);
			}

			else if ((my_strlen(input[0]) == 7) && (my_strcmp(input[0], "history") == 0))
			{
				/*HISTORY*/
				file = fopen(".nsmshistory", "r");
				printw("Your command history: \n");
				while (fgets(buff, 255, file) != NULL)
					printw(buff);
				fclose(file);
			}

			else if (input[0] != NULL)
			{
				/*EXECUTE AN EXTERNAL PROGRAM*/
				if ((pid = fork()) == -1)
				{
					printw("MINISHELL: Error forking\n");
					refresh();
				}

				else if (pid > 0)
				{
					wait(NULL);
				}

				else
				{
					index = 0;

					while (input[0][index] != '\0')
					{
						if (input[0][index] == '$')
							printw("dollar sign\n");
						/*DO THINGS*/
						index++;
					}

					if (execvp(input[0], input) == -1)
					{
						printw("MINISHELL: Error. Program does not exist in current directory.\n");
						refresh();
						exit(0);
					}
				}
			}

			else
			{
				printw("MINISHELL: Error reading command. Type help to see available commands.");
				refresh();
			}
		}
	}
	free(s);
	return 0;
}
