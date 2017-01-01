#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

//Manejadores
void manejador1 ();
void manejador2 ();
void manejadorHijo ();

//Variables globales
pid_t hijo[3];
int turno = 0;
pid_t pidPadre;

int main () {

	//Averiguamos el PID del proceso padre
	pidPadre = getpid();

	int i;
	for (i=0; i<3; ++i) {
		//Si estamos en el hijo...
		if ((hijo[i] = fork()) == 0) {

			//Definimos el tratamiento de la señal SIGUSR1 (Sólo en los hijos)
			signal (SIGUSR1, manejadorHijo);
			signal (SIGTERM, manejador1);

			//bucle infinito, para que los hijos no avancen
			while (1) {
				pause();
			}
		}
	}

	//Tratamiento de las señales (sólo para el Padre)
	signal (SIGTERM, manejador1);
	//Con esta linea se mata a TODOS los procesos cuando 
	//se envía la señal SIGTERM al proceso padre

	signal (SIGALRM, manejador2);

	//Bucle infinito
	while (1) {
		//Aviso cada 5 segundos
		alarm (5);
		//En espera de una señal
		pause();
	}

	return 0;

}

void manejador1 () {

	//Enviamos la señal de terminacion a los hijos
	int i;
	for (i=0; i<3; ++i)
		kill (hijo[i], SIGKILL);
	//Enviamos la señal de terminacion al padre
	kill (pidPadre , SIGKILL);

}

void manejador2 () {

	//Pasamos el turno al siguiente proceso hijo e incrementamos el contador
	kill (hijo[turno%3], SIGUSR1);
	turno++;

}

void manejadorHijo () {
	//Sacamos la traza para ver el PID del proceso que tiene el turno
	fprintf (stdout, "El turno es del proceso con PID ");
	fprintf (stdout, "%d\n", getpid());

}
