#include <stdio.h>
#include <unistd.h>


void main()
{
	printf("Inicio Programa\n");
	fork();
	printf("Fin Programa\n");
}

//Salida
/*
Inicio Programa
Fin Programa
Fin Programa
*/
//EXPLICACION: El mensaje de fin de programa sale dos veces porque no se tiene cuidado con la llamada al sistema fork.
//Desde la ejecucion de esa llammada al sistema en adelante se crean dos lineas de ejecucion: una del proceso padre, y otra del proceso hijo
//por eso el mensaje sale dos veces, una por cada uno
