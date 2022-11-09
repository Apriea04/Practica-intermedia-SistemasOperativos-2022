#!/bin/bash

function mostrarMenu()
{   
    echo "Elija entre:"
    echo
    echo "1      Mostrar código"
    echo "2      Compilar archivo"
    echo "3      Ejecutar simulador de vuelo"
    echo "4      Salir"
    echo
    echo
}

opcion=8
mostrarMenu
while test $opcion -ne 4
do
	read opcion

	case $opcion in
	
    1)  echo `cat Main.c`;;
    2)  echo `gcc Main.c -o a.out`
        echo "Compilando..."
	
	esac
    #no limpiamos pantalla si queremos ver el contenido del archivo
    if test $opcion -ne 1
    then
        echo `clear`

    fi
    sleep 1
    mostrarMenu
done