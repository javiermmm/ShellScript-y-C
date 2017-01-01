#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX 128

int main()
{
	int pid, tuberia[2], numBytes, nBytes;
	char mensaje[MAX];

	/* Creación de una tubería sin nombre. */
	if ( pipe(tuberia) == -1 ) {
		perror("pipe");
		exit(-1);
	}

	/* Creación del proceso hijo. */
	if ( (pid = fork()) == -1 ) {
		perror("fork");
		exit(-1);
	}

	if ( pid == 0 ) {
		/* Código del proceso hijo. */
		/* El proceso hijo (receptor) se
		va a encargar de leer un mensaje
		de la tubería y presentarlo en pantalla. */
		sleep (10);
		close(tuberia[1]);
		while ((nBytes = read(tuberia[0], mensaje, 5)) > 0 &&
		strcmp(mensaje, "Q") != 0 )
		{
			fprintf(stdout,"Proceso Receptor. Mensaje: %s\n", mensaje);
			//memset(mensaje, 0, 5); 
			// Rellena todo el mensaje con nulos
		}
		close(tuberia[0]);
		exit(0);
	}
	else /* Código del proceso padre. */
	{
	/* El proceso padre (emisor) se va a encargar de leer un mensaje
	 de la entrada estándar y lo escribe en la tubería para que
	 lo reciba el proceso hijo. */
	close(tuberia[0]);

	do {
		numBytes = read(0, mensaje, MAX);
		if (mensaje[numBytes-1] == '\n')
			mensaje[numBytes-1] = 0;
		write(tuberia[1], mensaje, numBytes);
	} while (strcmp(mensaje, "Q") != 0);

	close(tuberia[1]);
	exit(0);
	}
}
