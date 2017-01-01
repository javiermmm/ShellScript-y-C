/***
    PROGRAMA: rdfifo.c
    DESCRIPCION:
       Lectura desde un FIFO.
    FORMA DE USO:
       rdfifo (Necesita la ejecución del programa wrfifo)
***/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h> // Para PIPE_BUF = 4Mb

int main(void) {

   int fd;              /* Descriptor del FIFO. */
   int len;             /* Bytes leídos del FIFO. */
   /*char buf [5];*/	 char buf[PIPE_BUF]; 

   /* Apertura del FIFO de sólo lectura. */

   if ( (fd = open("fifo1", O_RDONLY)) < 0)
   {
      perror("Apertura");
      exit(EXIT_FAILURE);
   }

   /* Lectura y visualización de la salida del FIFO hasta EOF. */
   while ( (len = read(fd, buf, PIPE_BUF-1)) > 0)
      fprintf(stdout, "Lectura de rdfifo: %s", buf);

//----------------------------------------------
//PRIMERA MODIFICACION. Se leen 5 bytes y acaba
//----------------------------------------------
/*
	read (fd, buf, 5);
	fprintf(stdout, "Lectura de rdfifo: %s", buf);
*/


   close(fd);
   exit(EXIT_SUCCESS);

}

