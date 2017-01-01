#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

//PID's para el padre y el hijo
pid_t hijo, padre;

//Di�logo
char* dialogo [] = {"Hola Ana", "Hola Jose", "�Qu� tal andas?", 
		    "Bien gracias, �y t�?", "Adi�s1", "Adi�s2" };

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

	//Definimos el tratamiento de las se�ales, 
	//para que el hijo sepa qu� hacer con ellas.
	if (hijo > 0) //Estamos en el padre
		signal (SIGUSR1, manejadorPadre);	
	
	if (hijo == 0) //Estamos en el hijo
		signal (SIGUSR2, manejadorHijo);	

	//Primer env�o de se�al. Arranque del programa.
	if (hijo == 0)
		kill (padre, SIGUSR1);

	//Bucle infinito (en espera de se�al)
	while (1)
		pause();

	//FIN
	return 0;
}

//Si elimin�ramos el c�digo de las l�neas 25-31
//el programa se quedar�a en espera de una se�al externa.
//Es decir, tendr�amos que hacer desde otra shell: 'kill -10 PID_Padre'

void manejadorPadre () {

	//mostrar mensaje
	fprintf (stdout, "%s\n", dialogo[i]);

	//incrementar indice
	i = i+2;
	
	//mandar se�al al hijo
	kill (hijo, SIGUSR2);
}

//Como hemos elegido que sea el padre el que empiece el dialogo,
//el padre no debe terminar los procesos, porque en la secuencia de di�logo
//evitar�a la aparici�n de la �ltima frase, por interactuar alternativamente
//los procesos

void manejadorHijo () {

	//mostrar mensaje
	fprintf (stdout, "%s\n", dialogo[j]);
	
	//Si no se ha llegado al final...
	if (dialogo[j] != "Adi�s2") {
		//incrementar indice
		j = j+2;
		
		//mandar se�al al padre
		kill (padre, SIGUSR1);
	}
	else {//HEMOS LLEGADO AL FINAL
	
		//Como ya hemos terminado el dialogo mandamos 
		//la se�al de terminaci�n a ambos procesos
		kill (hijo, SIGTERM);
		kill (padre, SIGTERM);
	}
}

//En este caso, s� debemos poner el env�o de la se�al de terminaci�n
//a ambos procesos, porque el di�logo llega a su completo final
//Si no lo copntrol�ramos suceder�a un acceso a posiciones no v�lidas del array
