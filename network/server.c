#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 61440 // 60kb
#define SERVER_DIR "server/"

int handling(int state, const int state_value, const char* message);

int main(int argc, char* argv[])
{
	struct stat file_stat;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;
	
	int fd = 0;
	int len = 0;
	int serv_sock = 0;
	int clnt_sock = 0;
	int state = 0;
	mode_t file_mode = 0;
	off_t file_size = 0;

	char path[1024] = {0,};
	char buffer[BUF_SIZE] = {0,};

	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	handling(serv_sock, -1, "socket() error"); // 소캣 에러 메세지

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	state = bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
	handling(state, -1, "bind() error");
	state = listen(serv_sock, 5);
	handling(state, -1, "listen() error");

	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
	handling(clnt_sock, -1, "accept() error");

	while(1) {
		
        
		len = read(clnt_sock, buffer, BUF_SIZE);
		handling(len, -1, "read() error");
		if (!strlen(buffer)) 
			continue;
		if(!strcmp(buffer, "quit"))
			break;
		
		
		putchar('\n');
		fputs("Requested File Path : ", stdout);
		puts(buffer);
		
		// server라는 파일에 만들기
		strcpy(path, SERVER_DIR);
		strcat(path, buffer);

		
		fd = open(path, O_RDONLY);
		if (fd == -1) {
			fputs("... NOT FOUND : ", stdout);
			puts(path);
			strcpy(buffer, "NOT FOUND");
			write(clnt_sock, buffer, BUF_SIZE);
			puts("File request failed");
			continue;
		}
		strcpy(buffer, "FOUND");
		write(clnt_sock, buffer, BUF_SIZE);

		
		state = fstat(fd, &file_stat); //파일의 상태를 state에 넣기
		handling(state, -1, "fstat() error"); // 파일 상태에대한 handling
		file_size = file_stat.st_size;
		file_mode = file_stat.st_mode
		puts("Success!!");
		printf("File Size : %ld\n", file_size);
		printf("File Mode : %X\n", file_mode);
		write(clnt_sock, &file_size, sizeof(off_t));
		write(clnt_sock, &file_mode, sizeof(mode_t));
		
		
		while((len = read(clnt_sock, buffer, BUF_SIZE))&&!strlen(buffer));
		handling(len, -1, "read() error");
		if (strcmp(buffer, "ok")) {
			close(fd);
			puts("File request failed");
			continue;
		}
		
	
		while ((len = read(fd, buffer, BUF_SIZE)) > 0) {
			write(clnt_sock, buffer, len);
		}
		puts("Finish");

		
		close(fd);
	}

	close(clnt_sock);
	close(serv_sock);
}

int handling(int state, const int state_value, const char* message)
{
	
	if (state != state_value) {
		return state;
	}
	
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
