#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>

#include <sys/socket.h>

#include <dirent.h> 

 

void error_handling(char *message);



int main(int argc, char * argv[])

{

	int sock;

	struct sockaddr_in serv_addr;

	char message[30];

	int str_len;
	
	char * cwd = (char *)malloc(sizeof(char) * 1024); 
	DIR *dir = NULL; //directory
	struct dirent *entry= NULL;
	
	getcwd(cwd, 1024);

	if(argc!=3)  

	{

		printf("Usage : %s <IP> <port> \n", argv[0]);

		exit(1);

	}

	sock = socket(PF_INET, SOCK_STREAM, 0) ;

	if(sock == -1)

		error_handling("socket() error");

		

	memset(&serv_addr, 0 ,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;

	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

	serv_addr.sin_port = htons(atoi(argv[2]));

	

	if(connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)

		error_handling("connect() error");

	

	str_len = read(sock, message, sizeof(message)-1);

	if(str_len == -1)

		error_handling("read() error");

	
	if(!strcmp(message,"ls")) {
	printf("Message from server : %s\n", message);
	
       		
		if((dir = opendir(cwd)) == NULL)
		{
			printf("directory error\n");
			exit(1);
		}
	
		while((entry = readdir(dir)) != NULL)
		{
			printf("%s\n", entry->d_name);
		}
		free(cwd);
		closedir(dir);
		close(sock);
	}
	return 0;	

}

 

void error_handling(char *message)

{

	fputs(message, stderr);

	fputc('\n', stderr);

	exit(1);

}
