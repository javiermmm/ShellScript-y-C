#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char * argv[]) 
{

	if (argc < 2)
		fprintf (stdout, "¡¡ERROR!!. Se esperaba un numero natural como argumento\n");

	int n;
	n = atoi (argv[1]); 		//Convierte a entero
	
	int i;
	for (i= 0; i< n; i++) {
		int hijo;
		hijo = fork();
		if (hijo != 0) {
//			system ("sleep 2");	//Es necesario para que el padre no muera tan rapidamente, y poder ver los ppid adecuadosç
                        wait(NULL);
			break;
		}
		fprintf (stdout, "%d ", i);
		fprintf (stdout, "%d ", getpid());
		fprintf (stdout, "%d\n", getppid());
	}
	return 0;
}
