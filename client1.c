#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX 	1024


void read_str(char A[])
{
	char ch;
	static int L;

	do{
		ch = fgetc(stdin);
		L++;
	}
	while(ch!='\n');
	
	read(0, A, (L+1));
}

void write_str(char A[])
{
	char ch;
	static int len1=0;

	do{
		ch = A[len1];
		len1++;
	}
	while(ch!='\n');

	write(1, A, (len1+1));
	
}

int main()
{
        int sockfd;
        int len;
	int len1=0;
	char B[MAX];
	char A[MAX];
	char ch;
        struct sockaddr_un address;
        int result;

        //char *A = "Here I am!!\n";
//	scanf("%d",&ch);
//	printf("Hello there!!\n");
	while((ch=getchar())!='\n')
	{
		B[len1] = ch;
		printf("%c",ch);
		len1++;
	}

	printf("WTF!!\n");
	//len1 = strlen(A) ;
	
//	printf("%d\n",ch);
	
/*	int i =0;

	while(i<len1)
	{
		printf("%c",B[i]);
		i++;
	}*/

        sockfd = socket (AF_UNIX, SOCK_STREAM, 0);                              /*Creating a socket for client*/

        address.sun_family = AF_UNIX;
        strcpy (address.sun_path, "server_socket");
        len = sizeof(address);

        result = connect(sockfd, (struct sockaddr *)&address, len);

        if(result == -1)
        {
                perror("client!!\n");
                exit(1);
        }

//	read_str(A);

        write(sockfd, B, len1);
       len1 =  read(sockfd, A, MAX);

	A[++len1] = '\0';

	printf("The string is %s",A);

//        write_str(A);
        close(sockfd);
        exit(0);
}
