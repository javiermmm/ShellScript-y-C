#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char * argv[]) 
{

	if (argc < 2)
		fprintf (stdout, "¡¡ERROR!!. Se esperaba un numero natural como argumento\n");

	int n;
	n = atoi (argv[1]); 		//Convierte a entero
	
	int i = 0;
	fprintf (stdout, "%d ", i);
	fprintf (stdout, "%d ", getpid());
	fprintf (stdout, "%d\n", getppid());
	for (i= 0; i< n; i++) {
		int hijo;
		hijo = fork();
		system ("sleep 2"); //Es necesario, porque sino, el proceso padre, muere rapidamente
		if (hijo == 0) {
			fprintf (stdout, "%d ", i+1);
			fprintf (stdout, "%d ", getpid());
			fprintf (stdout, "%d\n", getppid());
			break;
		}
	}
	return 0;
}
