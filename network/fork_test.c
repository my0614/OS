/* "[소스 2] fork 예제" */  

#include <unistd.h>
#include <stdio.h>
 
int main(void) 
{          
     int pid;		// Process ID
     int count;	// 공통 변수
     
     count = 0;
     
     pid = fork();
     
     if(pid == -1)	/* 프로세스 생성 실패 시 */
     {
     	return 1;
     }
     else  if(pid != 0)	 /* 부모 프로세스 */
     {   	
      	count++;
      	printf("This is parent.. : %d\n",count);
     }

     if(pid == 0)	 /* 자식 프로세스 */
     {
     	count++;
     	printf("This is child.. : %d\n",count);
     }
     
     return 0;
}
