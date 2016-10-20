#include "myselect.h"

int WINDOW_CHANGED = 1;

void size_handler(int sig)
{
	signal(SIGWINCH, SIG_IGN);

	endwin();
	initscr();
	refresh();
	clear();
	WINDOW_CHANGED = 1;
}


int main(int argc, char** argv)
{
	char** files = &argv[1];
	int* selected; 
	int * max_sizes;
	int c = 1;
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int x = 0;
	int y = 0;
	int max_size = 0;
	int num_files;
	int ch;
	int resize_me = 0;


	if (argc < 1)
	{
		my_int(y);
	}

	if (argc < 2)
	{
		my_str("usage: ./myselect files . . .\n");
		return -1;
	}

	initscr();			/* Start curses mode 		  */
	raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();
	move(0, 0);
	

	while (files[i] != NULL)
	{
		/*printw(files[i]);
		printw("\n");*/
		i++;
	}

	num_files = i - 1;
	selected = (int *) malloc(num_files * sizeof(int));
	i = 0;
	mvchgat(0, 0, my_strlen(files[i]), A_UNDERLINE, 1, NULL);

	while (1)
	{
		/*Screen Adjust Code*/
		signal(SIGWINCH, size_handler);

		if (WINDOW_CHANGED)
		{
			while (selected[i] != '\0')
			{
				selected[i] = 0;
				i++;
			}

			resize_me = 0;
			i = 0;
			k = 0;
			l = 0;
			j = 0;

			while (files[i] != NULL)
			{
				if (l >= LINES)
				{
					k += 1;
					k += max_size;
					j++;
					if (k >= COLS)
					{
						clear();
						move(0,0);
						printw("Please Make Terminal Bigger");
						resize_me = 1;
						break;
					}
					l = 0;
					c ++;
					max_size = 0;
				}

				if (my_strlen(files[i]) > max_size)
					max_size = my_strlen(files[i]);
				i++;
				l++;
			}

			if (k + max_size >= COLS)
			{
				clear();
				move(0,0);
				printw("Please Make Terminal Bigger");
				resize_me = 1;
			}

			max_sizes = (int *) malloc(c * sizeof(int));
			i = 0;
			k = 0;
			l = 0;
			j = 0;
			c = 1;
			max_size = 0;

			if (!resize_me)
			{
				while (files[i] != NULL)
				{
					if (l >= LINES)
					{
						k += 1;
						k += max_size;
						move(0, k);
						l = 0;
						max_sizes[c - 1] = max_size;
						c++;
						max_size = 0;
					}

					if (my_strlen(files[i]) > max_size)
						max_size = my_strlen(files[i]);
				
					move(l, k);
					printw(files[i]);
					printw("\n");
					i++;
					l++;
				}

				i = 0;
				k = 0;
			}
			
			WINDOW_CHANGED = 0;
		}	

		if (!resize_me)
		{
			ch = getch();
			if (ch == KEY_DOWN)
			{
   				getyx(curscr, y, x);
				
				if ((i + LINES * j >= num_files) && (j > 0))
				{
					if (selected[LINES * j] == 0)
						mvchgat(0, x, my_strlen(files[LINES * j]), A_UNDERLINE, 1, NULL);

					i = num_files - LINES * j;

					if (selected[num_files] == 0)
						mvchgat(i, x, my_strlen(files[num_files]), A_NORMAL, 1, NULL);	

					i = 0;
				}

				else if ((i == LINES - 1) && (c > 1))
				{
					if (selected[LINES * j] == 0)
						mvchgat(0, x, my_strlen(files[LINES * j]), A_UNDERLINE, 1, NULL);


					if (selected[i + LINES * j] == 0)
						mvchgat(i, x, my_strlen(files[i + LINES * j]), A_NORMAL, 1, NULL);	
					i = 0;
				}

				else if ((i + LINES * j < num_files) && (j > 0))
				{
					i++;

					if (selected[i + LINES * j] == 0)
						mvchgat(i, x, my_strlen(files[i + LINES * j]), A_UNDERLINE, 1, NULL);

					if ((i > 0) && (selected[i - 1 + LINES * j] == 0))
						mvchgat(i - 1, x, my_strlen(files[i - 1 + LINES * j]), A_NORMAL, 1, NULL);			
				}

				else if ((i < num_files) && (c == 1))
				{
					i++;

					if (selected[i] == 0)
						mvchgat(i, x, my_strlen(files[i]), A_UNDERLINE, 1, NULL);

					if ((i > 0) && (selected[i - 1] == 0))
						mvchgat(i - 1, x, my_strlen(files[i - 1]), A_NORMAL, 1, NULL);			
				}


				else if ((i < LINES - 1) && (c > 1))
				{
					i++;

					if (selected[i] == 0)
						mvchgat(i, x, my_strlen(files[i]), A_UNDERLINE, 1, NULL);

					if ((i > 0) && (selected[i - 1] == 0))
						mvchgat(i - 1, x, my_strlen(files[i - 1]), A_NORMAL, 1, NULL);			

				}

				else if ((i == num_files) && (c == 1))
				{

					if (selected[0] == 0)
						mvchgat(0, x, my_strlen(files[0]), A_UNDERLINE, 1, NULL);


					if (selected[i] == 0)
						mvchgat(i, x, my_strlen(files[i]), A_NORMAL, 1, NULL);	
					i = 0;
				}
			}

			else if (ch == KEY_UP)
			{
   				getyx(curscr, y, x);
				
				if (i > 0)
				{
					i--;

					if (selected[i + LINES * j] == 0)
						mvchgat(i, x, my_strlen(files[i + LINES * j]), A_UNDERLINE, 1, NULL);


					if ((i < num_files) && (selected[i + LINES * j + 1] == 0))
						mvchgat(i + 1, x, my_strlen(files[i + LINES * j + 1]), A_NORMAL, 1, NULL);
				}

				else if (i == 0)
				{
					if (c == 1)
						i = num_files;
					else if (j > 0)
						i = num_files - LINES * j;
					else
						i = LINES - 1;

					if (selected[i + LINES * j] == 0)
						mvchgat(i, x, my_strlen(files[i + LINES * j]), A_UNDERLINE, 1, NULL);


					if (selected[LINES * j] == 0)
						mvchgat(0, x, my_strlen(files[LINES * j]), A_NORMAL, 1, NULL);	
				}
			}

			else if (ch == KEY_RIGHT)
			{
				if ((i + LINES * (j + 1) > num_files) && (j < c - 1))
				{
   					getyx(curscr, y, x);

					if (!selected[i + LINES * j])
						mvchgat(i, x, my_strlen(files[i + LINES * j]), A_NORMAL, 1, NULL);

					i = num_files - LINES * (j + 1);

					if (!selected[num_files])
						mvchgat(i, max_sizes[j] + x + 1, my_strlen(files[num_files]), A_UNDERLINE, 1, NULL);
					else
					{
						mvchgat(i, max_sizes[j] + x + 1, my_strlen(files[num_files]), A_STANDOUT, 1, NULL);
					}

					j++;

				}

				else if (j < c - 1)
				{
   					getyx(curscr, y, x);

					if (!selected[i + LINES * j])
						mvchgat(i, x, my_strlen(files[i + LINES * j]), A_NORMAL, 1, NULL);

					if (!selected[i + LINES * (j + 1)])
						mvchgat(i, max_sizes[j] + x + 1, my_strlen(files[i + LINES * (j + 1)]), A_UNDERLINE, 1, NULL);

					else
					{
						mvchgat(i, max_sizes[j] + x + 1, my_strlen(files[i + LINES * (j + 1)]), A_STANDOUT, 1, NULL);
					}

					j++;
				}

				else
				{
   					getyx(curscr, y, x);
					if (!selected[num_files])
						mvchgat(num_files - LINES * j, x, my_strlen(files[num_files]), A_UNDERLINE, 1, NULL);
					/*else
					{
						mvchgat(i, x, my_strlen(files[i + LINES * j]), A_STANDOUT, 1, NULL);
					}*/

					if ((!selected[i + LINES * j]) && ((i + LINES * j) != num_files))
						mvchgat(i, x, my_strlen(files[i + LINES * j]), A_NORMAL, 1, NULL);
					i = num_files - LINES * j;
				}
			}

			else if (ch == KEY_LEFT)
			{
				if (j > 0)
				{
   					getyx(curscr, y, x);

					if (!selected[i + LINES * j])
						mvchgat(i, x, my_strlen(files[i + LINES * j]), A_NORMAL, 1, NULL);

					j--;

					if (!selected[i + LINES * j])
						mvchgat(i, x - 1 - max_sizes[j], my_strlen(files[i + LINES * j]), A_UNDERLINE, 1, NULL);

					else
					{
						mvchgat(i, x - 1 - max_sizes[j], my_strlen(files[i + LINES * j]), A_STANDOUT, 1, NULL);
					}
				}
			}

			else if (ch == ' ')
			{
   				getyx(curscr, y, x);

				if (((selected[i] == 0) && (j == 0)) || ((j > 0) && (selected[i + LINES * j] == 0)))
				{
					mvchgat(i, x, my_strlen(files[i + LINES * j]), A_STANDOUT, 1, NULL);
					if (j > 0)
						selected[i + LINES * j] = 1;
					else
						selected[i] = 1;

					if ((i < num_files) && (c == 1))
					{
						i++;
					}


					else if ((i < LINES - 1) && (j == 0) && (c > 1))
					{
						i++;
					}

					else if (i == LINES - 1)
					{
						i = 0;
					}

					else if (i == num_files - LINES * j)
					{
						i = 0;
					}

					else if ((i + LINES * j < num_files) && (j > 0) && (j == c))
					{
						i++;
					}

					else
					{
						i++;
					}
				}

				else
				{
					mvchgat(i, x, my_strlen(files[i + LINES * j]), A_NORMAL, 1, NULL);
					selected[i + LINES * j] = 0;
				}
			}

			else if (ch == 10)
			{
				endwin();			
				break;
			}

			else if (ch == 27)
			{
				endwin();
				return 0;
			}
		}
	}		

						/* Print it on to the real screen */
	i = 0;

	while (i < num_files + 1)
	{
		if (!selected[i])
			i++;
		else
		{
			my_str(files[i]);
			my_str(" ");		
			i++;
		}	
	}

	return 0;

}

