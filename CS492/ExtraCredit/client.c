#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

int main(int argc, char **argv)
{
	int sockfd, portnum;
	struct sockaddr_in serv_addr;
	struct hostent *host_name;
	char msg[1024];
	char *username = (char*)malloc(256*sizeof(char));
	char *message = (char*)malloc(256*sizeof(char));

	if (argc<3)
	{
		printf("Usage: ./client <host_name> <port_number>\n");
		exit(0);
	}
	
	if ((host_name = gethostbyname(argv[1]))==NULL)
	{
		printf("Invalid hostname\n");
		exit(0);
	}
	
	portnum = str_to_num(argv[2]);
	
	if (portnum < 1024)
	{
		perror("Ports below 1024 are reserved for root access.\n");
	}

	if (portnum<1 || portnum>65535)
	{
		printf("Port must be between 1 and 65535\n");
		exit(0);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero((char*)&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;

	serv_addr.sin_port = htons(portnum);

	bcopy((char*)host_name->h_addr_list[0], (char*)&serv_addr.sin_addr.s_addr, host_name->h_length);

	/*serv_addr.sin_addr.s_addr = (struct in_addr*)host_name->h_addr_list[0];*/
	if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))<0)
	{
		perror("connect");
		exit(0);
	}

	printf("Connected to server... sending message now.\n");
	printf("username: ");
	fgets(msg, sizeof(msg), stdin);
	printf("\n");

	if (printfncmp("/exit", msg, 5) == 0)
	{
		printf("Exiting sockettalk client\n");
		exit(0);
	}

	else
	{
		printfncpy(username, msg, printflen(msg) - 1);
		printf("setting nickname to: ");
		printf(username);
		printf("\n");
		write(sockfd, msg, printflen(msg + 1));
	}

	while (1)
	{
		printf("message: ");
		fgets(msg, sizeof(msg), stdin);
		printf("\n");

		if (printfncmp("/exit", msg, 5) == 0)
			exit(0);

		else if (printfncmp(msg, "/me", 3) == 0)
		{
			message = printfconcat(username, &msg[3]);
			write(sockfd, message, printflen(message + 1));
			printf("message sent\n\n");
		}

		else if (printfncmp(msg, "/nick", 5) == 0)
		{
			message = printfconcat("Changing nickname of ", username);
			printf("Changing nickname of ");
			printf(username);
			printfncpy(username, &msg[6], printflen(&msg[6]) - 1);
			printf(" to ");
			printf(username);
			message = printfconcat(message, " to ");
			message = printfconcat(message, username);
			write(sockfd, message, printflen(message));
			printf("\n");
		}

		else
		{
			message = printfconcat(username, ": ");
			message = printfconcat(message, msg);
			write(sockfd, message, printflen(message + 1));
			printf("message sent\n\n");
		}
	}

	write(sockfd, "\0", 1);

	close(sockfd);

	/*printf("Message sent; exiting.\n");*/
	sleep(5000);

	return 0;
}
