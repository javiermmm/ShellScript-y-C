#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void manejador1 ();
void manejador2 ();

int main () {
	
	//Tratamiento de señales
	signal (SIGKILL, SIG_DFL);

	signal (SIGUSR1, SIG_IGN);

	signal (SIGINT, manejador1);

	signal (SIGUSR2, manejador2);

	signal (SIGTERM, SIG_DFL);

	//Bucle Infinito
	while (1) {}
}

void manejador1 () {

	fprintf (stdout, "\nEnvía la señal SIGINT (pulsa Ctrl+C)\n");
	signal (SIGINT, SIG_DFL);
}

void manejador2 () {

	fork();

}
