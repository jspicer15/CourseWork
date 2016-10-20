#include "../../include/my.h"

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
		my_str("Usage: ./client <host_name> <port_number>\n");
		exit(0);
	}
	
	if ((host_name = gethostbyname(argv[1]))==NULL)
	{
		my_str("Invalid hostname\n");
		exit(0);
	}
	
	portnum = str_to_num(argv[2]);
	
	if (portnum < 1024)
	{
		perror("Ports below 1024 are reserved for root access.\n");
	}

	if (portnum<1 || portnum>65535)
	{
		my_str("Port must be between 1 and 65535\n");
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

	my_str("Connected to server... sending message now.\n");
	my_str("username: ");
	fgets(msg, sizeof(msg), stdin);
	my_str("\n");

	if (my_strncmp("/exit", msg, 5) == 0)
	{
		my_str("Exiting sockettalk client\n");
		exit(0);
	}

	else
	{
		my_strncpy(username, msg, my_strlen(msg) - 1);
		my_str("setting nickname to: ");
		my_str(username);
		my_str("\n");
		write(sockfd, msg, my_strlen(msg + 1));
	}

	while (1)
	{
		my_str("message: ");
		fgets(msg, sizeof(msg), stdin);
		my_str("\n");

		if (my_strncmp("/exit", msg, 5) == 0)
			exit(0);

		else if (my_strncmp(msg, "/me", 3) == 0)
		{
			message = my_strconcat(username, &msg[3]);
			write(sockfd, message, my_strlen(message + 1));
			my_str("message sent\n\n");
		}

		else if (my_strncmp(msg, "/nick", 5) == 0)
		{
			message = my_strconcat("Changing nickname of ", username);
			my_str("Changing nickname of ");
			my_str(username);
			my_strncpy(username, &msg[6], my_strlen(&msg[6]) - 1);
			my_str(" to ");
			my_str(username);
			message = my_strconcat(message, " to ");
			message = my_strconcat(message, username);
			write(sockfd, message, my_strlen(message));
			my_str("\n");
		}

		else
		{
			message = my_strconcat(username, ": ");
			message = my_strconcat(message, msg);
			write(sockfd, message, my_strlen(message + 1));
			my_str("message sent\n\n");
		}
	}

	write(sockfd, "\0", 1);

	close(sockfd);

	/*my_str("Message sent; exiting.\n");*/
	sleep(5000);

	return 0;
}
