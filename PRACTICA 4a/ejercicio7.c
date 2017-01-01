#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char * argv[]) 
{
	//COMPROBAMOS LA CORRECION DEL PARAMETRO
	if (argc < 2)
		fprintf (stdout, "¡¡ERROR!!. La sintaxis correcta es: esperas numero_hijos\n");

	//DECLARACION DE VARIABLES
	int n, estado, contador;
	contador = 0;
	pid_t pid;
	n = atoi (argv[1]); 		//Convierte a entero
	int i = 0;

	//MOSTRAMOS EL PID Y EL PPID AL EMPEZAR
	fprintf (stdout, "PID_main: %d ", getpid());
	fprintf (stdout, "PPID_main: %d\n\n", getppid());


	for (i= 1; i<= n; i++) {
		//VARIABLES LOCALES AL BUCLE
		int tiempo;
		tiempo = 10*i;
		pid_t hijo;

		//CREAMOS EL NUEVO PROCESO
		hijo = fork();

		if (hijo == -1) {//ESTAMOS EN EL CASO DE QUE HAYA FALLADO EL FORK()
			perror ("fork");//Error en la llamada a fork()
			exit (EXIT_FAILURE);
		}
		else if (hijo == 0) {//ESTAMOS EN EL HIJO
			//MOSTRAMOS POR PANTALLA
			fprintf (stdout, "PID: %d   ", getpid());
			fprintf (stdout, "Tiempo durmiendo: %d\n\n", tiempo);
			
			//DORMIR
			system ("sleep " + tiempo);

			//AVISO DE FINAL EXITOSO
			exit(EXIT_SUCCESS);
		}
		else {//ESTAMOS EN EL PADRE
			//ESPERAMOS COMUNICACION DEL HIJO
			pid = wait (&estado); 

			//MOSTRAMOS POR PANTALLA
			fprintf (stdout, "El proceso hijo con PID=%d", pid);
			fprintf (stdout, " ha estado durmiendo %d", tiempo);
			puts (" segundos\n\n");	

			//ACTUALIZAMOS LA SUMA TOTAL DE SEGUNDOS
			contador = contador + tiempo;
		}
	}
	
	//HEMOS ACABADO Y MOSTRAMOS LA SUMA TOTAL DE SEGUNDOS
	fprintf (stdout, "PADRE: ejecución terminada. Mis hijos han estado durmiendo un total de %d", contador);
	puts (" segundos");

	//TERMINAMOS EL PROGRAMA CORRECTAMENTE
	return 0;
}
