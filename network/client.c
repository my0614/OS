#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/socket.h>

#define BUF_SIZE 61440 // 60kb
#define CLIENT_DIR "client/"

int handling(int err_chk, const int err_num, const char* message);

int main(int argc, char* argv[])
{
	int fd = 0;
	int len = 0;
	int sock = 0;
	int err_chk = 0;
	mode_t file_mode = 0;
	off_t file_size = 0;
	unsigned long bytes_count = 0;

	struct timeval start;
	struct timeval end;
	double work_time = 0;

	struct sockaddr_in serv_addr;

	char path[1024] = {0,};
	char buffer[BUF_SIZE] = {0,};
	
	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0); 
	handling(sock, -1, "socket() error"); // 소캣에러 메시지 

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	err_chk = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); // client에서 connect한후 결과
	handling(err_chk, -1, "connect() error"); // 결과 비교해서 에러메시지
	
	while(1) {
	
		
		scanf("%s", buffer);
		if (!strcmp(buffer, "quit"))
			break;

		write(sock, buffer, BUF_SIZE);
		
		
	
		strcpy(path, CLIENT_DIR);
		strcat(path, buffer); // 앞에 client 파일 붙이기
		
		
		len = read(sock, buffer, BUF_SIZE); // 파일 읽기
		handling(len, -1, "read() error"); // 소캣연결하고 에러 메세지
	
		
		len = read(sock, &file_size, sizeof(off_t));
		handling(len, -1, "read() error"); 
		len = read(sock, &file_mode, sizeof(mode_t));
		handling(len, -1, "read() error"); 

		printf("... File Size : %ld\n", file_size);
		printf("... File Mode : %X\n", file_mode);
		fd = creat(path, file_mode);

	
		if (fd == -1) {
			fputs("Failed to create file : ", stdout);
			puts(path);
			strcpy(buffer, "no");
			write(sock, buffer, BUF_SIZE);
			continue;
		}
	
		fputs("File created : ", stdout);
		puts(path);
		strcpy(buffer, "ok");
		write(sock, buffer, BUF_SIZE);
		
	
	
		gettimeofday(&start, NULL); //gettimeofday함수 사용하여 파일시간 읽기
		while ((len = read(sock, buffer, BUF_SIZE)) > 0) {
			write(fd, buffer, len);
		
			bytes_count += len;
			if (bytes_count >= file_size)
            {
                puts("file size small");
            }; // 파일 사이즈보다 크면 
		}
		gettimeofday(&end, NULL); 

	
		work_time = (double)(end.tv_sec)
			+ (double)(end.tv_usec)/1000000.0
			- (double)(start.tv_sec)
			- (double)(start.tv_usec)/1000000.0;
	
		printf("File Size : %ld\n", bytes_count);
		printf(" Time Spent : %.3lf\n", work_time);
		printf(" %.3lf b/s\n", (double)bytes_count/work_time);
		printf(" %.3lf kb/s\n", (double)(bytes_count/1024.0f)/work_time);
		printf(" %.3lf mb/s\n", (double)(bytes_count/1024.0f/1024.0f)/work_time);
		puts("Download complete");

	
		close(fd);
		len = 0;
		bytes_count = 0;
	}
	
	strcpy(buffer, "quit");
	write(sock, buffer, BUF_SIZE);
	close(sock);
	return 0;
}

int handling(int err_chk, const int err_num, const char* message)
{
	
	if (err_chk != err_num) {
		return err_chk;
	}

	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);

}
