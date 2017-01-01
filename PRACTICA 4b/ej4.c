#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

//Manejador
void manejador();

pid_t pid;

int main (int argc, char * argv[]) {

	//Comprobación de parámetros
	if (argc != 2)
		fprintf (stdout, "¡¡ERROR!!. La sintaxis correcta es: ej4 num_segundos\n");
	else {

		//Conversión de los segundos introducidos
		int segundos;
		segundos = atoi (argv[1]); //Convierte a entero

		//Guardamos el pid
		pid = getpid();

		//Establecemos el tratamienlto para la señal de alarma.
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
