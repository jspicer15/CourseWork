#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void interrupt();

void interrupt()
{
	printf("Server exiting.\n");
	exit(0);
}

int str_to_num(char* str)      
{
        int i = 0;
        int numDigits = 0;
        int ret = 0;

        while (str[numDigits] != '\0')
        {
                numDigits++;
        }

        while (i < numDigits)
        {
                int digit = str[i];

                if (digit < 48 && digit > 57)
                        return -1;

                digit -= 48;

                ret += digit * my_pow(10, numDigits - i - 1);
                i++;
        }
 
        return ret;
}

char* add_null_term(char* str)
{
	int i = 0;

	while (str[i] != '\0')
		i++;

	str[i] = '\0';

	return str;
}
int main(int argc, char **argv)
{
	int sockfd, newsockfd, portnum;
	int len;
	char buffer[256];
	/*char *username = (char*)malloc(256*sizeof(char));*/
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
  
	/*check args*/
	if (argc < 2)
	{
		printf("Usage: ./server <port_number>\n");
		exit(0);
	}
  
	portnum = str_to_num(argv[1]);
	
	if (portnum < 1024)
	{
		perror("Ports below 1024 are reserved for root access.\n");
		exit(0);
	}
	
	if (portnum < 1 || portnum > 65535)
	{
		printf("Port must be between 1 and 65535\n");
		exit(0);
	}

	signal(SIGINT, interrupt);
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero((char*)&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;

	serv_addr.sin_port = htons(portnum);

	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))<0)
	{
		perror("bind");
		exit(0);
	}
	
	listen(sockfd, 5);
	
	clilen = sizeof(cli_addr);

	while(1)
	{
		if ((newsockfd=accept(sockfd, (struct sockaddr*)&cli_addr, &clilen)) < 0)
		{
			perror("accept");
			exit(0);
		}
		
		usleep(2000);
		
		printf("Client connection started: ");
		
		while ((len = read(newsockfd, &buffer, 256)) > 0)
		{
			buffer[printflen(buffer)] = '\0';

			if (printfcmp(buffer, "/") == 0)
			{
				printf("Error: command ");
				printf(buffer);
				printf("not found.\n");
				bzero((char*)&buffer, sizeof(buffer));
			}

			else
			{
				printf(buffer);
				bzero((char*)&buffer, sizeof(buffer));
				printf(buffer);
				printf("\n");
			}
		}

		printf("\nServer: Message end. Waiting for next connection.\n");
	}

	return 0;
}
