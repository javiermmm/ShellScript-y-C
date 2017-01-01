#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

int main() {

	pid_t pidPadre = getpid();

	pid_t hijo;

	int i;
	for (i=1; i<6; ++i) {
		if ((hijo = fork()) == 0)
			break;
	}

	if (hijo == 0)
		while(1);
	else
		kill (pidPadre, SIGTERM);

	return 0;

}
