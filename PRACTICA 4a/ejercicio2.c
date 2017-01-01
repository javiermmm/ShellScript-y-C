#include <stdio.h>
#include <unistd.h>

void main()
{

	pid_t pid;

	pid = fork();

	fprintf(stdout, "pid=%d\n", getpid());
	fprintf(stdout, "pid=%d\n", getppid());
	system("sleep 30");
}

//
