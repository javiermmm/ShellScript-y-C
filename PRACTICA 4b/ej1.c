#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void man1 ();

int main () {

	//Creaci�n del otro proceso
	if (fork() > 0)
		//tratamiento de se�ales
		signal (SIGINT, man1);


	//Duraci�n larga (Infinita)
	while (1) {
		pause();
	}
	
	//Finalizacion
	exit (EXIT_FAILURE);

	return 0;
}

void man1 () {

	signal (SIGINT, SIG_DFL);
}
