#!/bin/bash

function mostrarMenu() {
    echo "Elija entre:"
    echo
    echo "1      Mostrar código"
    echo "2      Compilar archivo"
    echo "3      Ejecutar simulador de vuelo"
    echo "4      Salir"
    echo
    echo
}

function comprobarArgumentos() {
    v=0
    echo "Introduce el número de asistentes"
        while test $v -ne 1
        do
            read asistentes
            if [[ $asistentes =~ ^[0-9]+$ ]];
            then
                if test $asistentes -eq 0
                then
                    echo "Se necesita al menos un asistente"
                else
                    break
                fi
            else
               echo "Has de introducir un entero positivo"
            fi
        done
}

opcion=8
mostrarMenu
while test $opcion -ne 4
do
    read opcion

    case $opcion in

    1) echo $(cat Main.c) ;;
    2)
        echo $(gcc Main.c -o a.out)
        echo "Compilando..."
        sleep 1
        echo $(clear)
        ;;
    3) echo `clear`
        if test -f "Main.c"
        then
            comprobarArgumentos
            
            echo `./a.out $asistentes`
        else
            echo "Primero se ha de compilar (opción 2)"
        fi;;
    4)
        echo "Saliendo..."
        exit 0
        ;;
    *) echo "Debe seleccionar una opción válida" ;;

    esac

    sleep 1
    mostrarMenu
done