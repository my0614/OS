/* "[소스 1] signal 예제 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void call(int sig)
{
	/* SIGINT 값을 출력 */
	printf("I got signal %d\n", sig);	
	
	/* 시그널 설정 : 발생 시 시그널을 무시함 */
	(void)signal(SIGINT, SIG_DFL);
}

int main()
{
	/* 시그널 설정 : 발생 시 call 함수를 호출 함 */
	(void)signal(SIGINT, call);	
	
	while(1)
	{
		printf("Hello World\n");
		sleep(1);
	}
}
