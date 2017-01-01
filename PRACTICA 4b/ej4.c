#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

//Manejador
void manejador();

pid_t pid;

int main (int argc, char * argv[]) {

	//Comprobaci�n de par�metros
	if (argc != 2)
		fprintf (stdout, "��ERROR!!. La sintaxis correcta es: ej4 num_segundos\n");
	else {

		//Conversi�n de los segundos introducidos
		int segundos;
		segundos = atoi (argv[1]); //Convierte a entero

		//Guardamos el pid
		pid = getpid();

		//Establecemos el tratamienlto para la se�al de alarma.
		signal (SIGALRM, manejador);
	
		//Arrancamos el temporizador
		alarm (segundos);

		//Esperamos (bucle infinito)
		while (1) {}
	}

}

void manejador() {

	kill (pid, SIGTERM);

}
