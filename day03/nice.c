#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

int main()
{
	int priority = getpriority(PRIO_PROCESS, 13094);
	//get the process priority
	//13094  is a process id (PID)

	printf("priority:%d\n", priority);
	int ret = setpriority(PRIO_PROCESS, 13094, 5);
	//nice value is nothing but a Process priority
	//to change process priority we used setpriority() systemcall
	
	if (ret == 0){
		printf("priority is set");
	}else {
		printf("not set");
	}
}
