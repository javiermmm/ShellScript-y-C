#!/bin/bash

#ejecutamos el programa en la shell ANTES de nada, con la siguiente linea y asumimos que esto se habrá hecho
#$HOME/PRUEBA/generaHuerfanos

if [ $# -ne 1 ]
then
	echo Número de parámetros $# incorrecto: debe ser introducido un solo parámetro
else

    #a)

	#mostramos los procesos
	echo '                                                                   '
	echo --------------------------------------------------------------------
	echo A continuacion se muestran los procesos pertenecientes al usuario
	echo --------------------------------------------------------------------
	echo '                                                                   '
	ps -a

    #b)

	#Sacamos un listado de los procesos, buscamos coincidencias con el nombre del programa
	#pasado como argumento, nos quedamos las columnas que nos interesan y volcamos las
	#columnas en ficheros separados para después juntarlas en el orden deseado
	#Por último, borramos los ficheros auxiliares para no dejar basura
	ps -al | tr -s ' ' | grep $1 | cut -f4 -d' ' >> aux1 ####################################FALLAN ESTAS DOS LINEAS AL GUARDAR EN LOS FICHEROS
	ps -al | tr -s ' ' | grep $1 | cut -f3 -d' ' >> aux2
	paste aux1 aux2 >> procHuerfanos
	rm aux1
	rm aux2

	#Almacenamos el número de procesos huerfanos del tipo del parametro recibido para el apartado e)
	numProcEliminados=`ps -al | grep $1 | wc -l`



    #c)

	#Terminamos todos los procesos huerfanos del tipo recibido como parametro
	echo '                                                                   '
	echo --------------------------------------------------------------------
	echo Terminando procesos huerfanos del tipo recibido como parámetro
	echo --------------------------------------------------------------------
	echo '                                                                   '      
	usuario=`ps -al | tr -s ' ' | grep $1 | cut -f3 -d' ' | head -1`
	echo usuario vale $usuario
	killall -9 -u $usuario $1

    #d)

	#listamos el contenido del fichero creado
	echo '                                                                   '
	echo --------------------------------------------------------------------
	echo A continuacion se muestran los procesos pertenecientes al usuario
	echo --------------------------------------------------------------------
	echo '                                                                   '
	cat procHuerfanos

    #e)

	#Mostramos el mensaje con el número de procesos terminados y el tipo de proceso
	echo Se han terminado $numProcEliminados procesos huérfanos correspondientes al proceso $1

    #f)

	#Mostramos por segunda vez la lista de procesos del usuario para confirmar que los procesos huérfanos han muerto
	echo '                                                                   '
	echo --------------------------------------------------------------------
	echo Mostramos los procesos del usuario para confirmar que han terminado
	echo los procesos huerfanos generados por $1
	echo --------------------------------------------------------------------
	echo '                                                                   '
	ps -a
	echo '                                                                   '

fi
