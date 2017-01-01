#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main () {

	pid_t hijo = fork();

	int i;

	if (hijo == -1) {
		perror ("fork");	//Error en la llamada a fork()
		exit (EXIT_FAILURE);
	}
	else if (hijo == 0) {	//ESTAMOS EN EL HIJO
		fprintf (stdout, "PID: %d   ", getpid());
		fprintf (stdout, "PPID: %d\n", getppid());
		system("sleep 2");
		fprintf (stdout, "PID: %d   ", getpid());
		fprintf (stdout, "PPID: %d\n", getppid());
		exit(EXIT_SUCCESS);
	     }
	     else {
		system("sleep 1");
		exit(EXIT_SUCCESS);
	     }

	return 0;
}

//Le decimos al padre que espere un segundo para dar tiempo al hijo a escribir su ppid.
//Tras esto, le decimos al hijo, que espere 2 segundos, para dar tiempo al padre a que muera.
//Pasados los dos segundos volvemos a escribir, y efectivamente, vemos que el proceso hijo ha sido adoptado
