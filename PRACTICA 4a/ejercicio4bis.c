#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char * argv[]) 
{

	if (argc < 2)
		fprintf (stdout, "¡¡ERROR!!. La sintaxis correcta es: arbol num_entero\n");

	int n;
	n = atoi (argv[1]); 		//Convierte a entero
	if ( (n < 2) || (n > 5))
		fprintf (stdout, "¡¡ERROR!!. El numero introducido debe estar comprendido entre 2 y 5\n");

	//generar los hijos
	int i;
	for (i= 0; i < n; i++)
		if (fork() != -1) {
			fprintf (stdout, "%d ", i);
			fprintf (stdout, "%d ", getpid());
			fprintf (stdout, "%d\n", getppid());
		}	
}

//¿Cuántos procesos se han generado?
//SHELL:
//./ejercicio4 3 | sort -k1 | cut -f2 -d' ' | uniq -u | wc -l ==> 8 (en este ejemplo)
