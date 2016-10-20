#include "pipes.h"

int main(int argc, char** argv)
{
	int pipe1[2];
	int pipe2[2];
	pid_t pid;
	char* str;
        char readbuffer[100];
	int n;


	if (argc < 2)
	{
		my_str("usage: ./pipes arg1 [arg2] [arg3]... [arg_n]\n");
		return -1;
	}

	else
	{
		if (pipe(pipe1) == -1)
			exit(-1);

		if ((pid = fork()) == -1)
		{
			exit(-1);
		}

		else if (pid > 0)
		{
			if (close(pipe1[0]))
				return -1;

			str = my_vect2str(&argv[1]);
			my_str(">Parent: ");
			my_str(str);
			my_char('\n');

               		if (write(pipe1[1], str, (my_strlen(str) + 1)) < 0)
				return -1;

			wait(NULL);
			exit(0);
		}

		else if (pid == 0)
		{
			if (close(pipe1[1]))
				return -1;

			if (pipe(pipe2))
				return -1;
			
			if ((pid = fork()) == -1)
			{
				exit(-1);
			}

			else if (pid > 0)
			{
				if (close(pipe2[0]))
					return -1;

				str = my_vect2str(&argv[1]);
               			n = read(pipe1[0], readbuffer, sizeof(readbuffer));

				if (n < 0)
					return -1;

				my_str(">Child: ");
				my_str(readbuffer);
				my_char('\n');

                		if (write(pipe2[1], readbuffer, (my_strlen(readbuffer) + 1)) < 0)
					return -1;

				wait(NULL);
				exit(0);
			}

			else if (pid == 0)
			{
				if (close(pipe2[1]))
					return -1;

				str = my_vect2str(&argv[1]);

               			n = read(pipe2[0], readbuffer, sizeof(readbuffer));

				if (n < 0)
					return -1;

				my_str(">Grandchild: ");
				my_str(readbuffer);
				my_char('\n');

				exit(0);
			}

		}

	}

	return 0;
}
