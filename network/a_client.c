#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>

#include <sys/socket.h>

#include <dirent.h> 
#include <fcntl.h>
 

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

	
	while(1) {
//	fgets(message,BUFSIZ,stdin);
	str_len = read(sock, message, sizeof(message)-1);

	if(str_len == -1)

		error_handling("read() error");

//	printf("message = %s\n\n\n",message);	
	if(strcmp(message,"ls")==0) {
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
		
	}

	char cd_name[30]; // filename size 30
	if(message[0] == 'c' && message[1] == 'd')
	{
		int index = 3;
		while(message[index] != NULL)
		{
			strcat(cd_name, message[index]);
			index++;
		
		}
		chdir(cd_name);
		
		printf("success");
		//message = NULL;
	
		
		
	}
	if(message[0] =='g'&& message[1]=='e'&& message[2] == 't')
	{
		char file_name[30], file_name2[30] = {0,};
		int len = strlen(message);
		printf("len = %d\n",len);
		printf("message = %s", message);
		int index =4;
		FILE *fp;
		char buffer[100];
		memcpy(file_name,message,strlen(message)+1);
		printf("file_name is =%s\n",file_name);	
		for(int i = index; i<len+1;i++)
		{
			sprintf(file_name, "%c", message[i]);
			
			strcat(file_name2, file_name);
		}
		//printf("%s", message);		
			
		printf("file name=%s\n", file_name2);
		fp = open(file_name2, O_WRONLY);
		if(fp == -1)
		{
			error_handling("open() error!");
		}
		if(read(fp, buffer, sizeof(buffer)) == -1)
		{

			error_handling("read() error!");
		}
		
		printf("text is = %s", buffer);
		
	}
	
	//return 0;	
	
}
}
 

void error_handling(char *message)

{

	fputs(message, stderr);

	fputc('\n', stderr);

	exit(1);

}
