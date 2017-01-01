#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

//PID's para el padre y el hijo
pid_t hijo, padre;

//Diálogo
char* dialogo [] = {"Hola Ana", "Hola Jose", "¿Qué tal andas?", 
		    "Bien gracias, ¿y tú?", "Adiós1", "Adiós2" };

//indices para el array
int i = 0;//Padre
int j = 1;//Hijo

//Manejadores
void manejadorPadre ();
void manejadorHijo ();

int main() {

	padre = getpid();

	//Creamos un hijo
	hijo = fork();

	//Definimos el tratamiento de las señales, 
	//para que el hijo sepa qué hacer con ellas.
	if (hijo > 0) //Estamos en el padre
		signal (SIGUSR1, manejadorPadre);	
	
	if (hijo == 0) //Estamos en el hijo
		signal (SIGUSR2, manejadorHijo);	

	//Primer envío de señal. Arranque del programa.
	if (hijo == 0)
		kill (padre, SIGUSR1);

	//Bucle infinito (en espera de señal)
	while (1)
		pause();

	//FIN
	return 0;
}

//Si elimináramos el código de las líneas 25-31
//el programa se quedaría en espera de una señal externa.
//Es decir, tendríamos que hacer desde otra shell: 'kill -10 PID_Padre'

void manejadorPadre () {

	//mostrar mensaje
	fprintf (stdout, "%s\n", dialogo[i]);

	//incrementar indice
	i = i+2;
	
	//mandar señal al hijo
	kill (hijo, SIGUSR2);
}

//Como hemos elegido que sea el padre el que empiece el dialogo,
//el padre no debe terminar los procesos, porque en la secuencia de diálogo
//evitaría la aparición de la última frase, por interactuar alternativamente
//los procesos

void manejadorHijo () {

	//mostrar mensaje
	fprintf (stdout, "%s\n", dialogo[j]);
	
	//Si no se ha llegado al final...
	if (dialogo[j] != "Adiós2") {
		//incrementar indice
		j = j+2;
		
		//mandar señal al padre
		kill (padre, SIGUSR1);
	}
	else {//HEMOS LLEGADO AL FINAL
	
		//Como ya hemos terminado el dialogo mandamos 
		//la señal de terminación a ambos procesos
		kill (hijo, SIGTERM);
		kill (padre, SIGTERM);
	}
}

//En este caso, sí debemos poner el envío de la señal de terminación
//a ambos procesos, porque el diálogo llega a su completo final
//Si no lo copntroláramos sucedería un acceso a posiciones no válidas del array
