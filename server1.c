#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/un.h>
#include <string.h>

#define MAX 	1024

void write_str(char B[])
{
	char ch;
	int len=0;
	
	do
	{
		ch = B[len];
		len++;
	}
	while(ch!='\n');

	write(1, B, (len+1));
}

void read_str(char B[])
{
	char ch;
	 int len1;

	do{
		ch = fgetc(stdin);
		len1++;
	}

	while(ch != '\n');

	read(0, B, (len1+1));
}


int main()
{
	char B[MAX];
	int len1;
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;

	unlink("server_socket");
	server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	server_address.sun_family = AF_UNIX;
	strcpy(server_address.sun_path, "server_socket");

	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

	listen(server_sockfd, 5);

	while(1)
	{
		//char ch;

		printf("servr waiting\n");

		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);

		len1 = read(client_sockfd, B, MAX);

	//	write_str(B);
		B[++len1] = '\0';

		printf("the string received is:: %s\n",B);

		char *C = "Yahoooo!!\n";
		int i =0;
		scanf("%d",&i);
		printf("%d\n",i);		
		len1 = strlen(C);

		write(client_sockfd, C, len1);
		close(client_sockfd);
	}
}
