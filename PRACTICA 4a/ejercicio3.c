#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main () 
{
	srand(time(NULL));

	pid_t hijo = fork();

	int i;

	if (hijo == -1) {
		perror ("fork");	//Error en la llamada a fork()
		exit (EXIT_FAILURE);
	}
	else if (hijo == 0) {	//ESTAMOS EN EL HIJO
		for (i= 0; i < 10; i++) {
			int j;
			//Generar numeros aleatorios
			for (j= 0; j < 1000000; j++) {
				int num;
				num = random()%100;
			}
			//Sacar Traza
			fprintf (stdout, "HIJO: Iteracion numero %d\n", i+1);
		}
		exit (EXIT_SUCCESS);
	      }
	      else {		//ESTAMOS EN EL PADRE
		for (i= 0; i < 10; i++) {
			int j;
			//Generar numeros aleatorios
			for (j= 0; j < 1000000; j++) {
				int num;
				num = random()%100;
			}
			//Sacar Traza
			fprintf (stdout, "PADRE: Iteracion numero %d\n", i+1);
		}
		exit (EXIT_SUCCESS);
	      }
}
