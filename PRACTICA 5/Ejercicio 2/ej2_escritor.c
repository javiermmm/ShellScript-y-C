/***
    PROGRAMA: wrfifo.c
    DESCRIPCION:
       Escritura en un FIFO.
    FORMA DE USO:
       wrfifo (Necesita la ejecución del programa rdfifo)
***/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>  // Para PIPE_BUF = 4 Mb
#include <time.h>

int main(void) {

   int fd;              /* Descriptor del FIFO. */
   int len;             /* Bytes escritos en el FIFO. */
   /*char buf[5];*/		char buf[PIPE_BUF];  /* Se asegura de escrituras atómicas. */
   time_t tp;           /* Para albergar la hora actual. */
   int i;
   printf("Soy el proceso %d\n", getpid());

   /* Abre el FIFO de sólo escritura. */
   if ( (fd = open("fifo1", O_WRONLY)) < 0)
   {
      perror("Apertura FIFO");
      exit(EXIT_FAILURE);
   }

//------------------------------------
//MODIFICACION 2
//------------------------------------


   /* Genera algunos datos para escribir en el FIFO */
//   for (i=0; i<5; i++)
//   {
      time(&tp); // Obtiene la hora actual
      len = sprintf(buf, "wrfifo: %d envía %s", getpid(), ctime(&tp));
      /* Utiliza (len + 1) porque 'sprintf' no cuenta el nulo final. */
      if (write(fd, buf, len + 1) < 0)
      {
         perror("Escritura");
         exit(EXIT_FAILURE);
      }
      sleep(3);
//   }

  close(fd);
  exit(EXIT_SUCCESS);

}

