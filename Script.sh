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

function compilar() {
    gcc Main.c -o a.out
}

function comprobarArgumentos() {
    v=0
    echo "Introduce el número de asistentes"
    echo
    while test $v -ne 1; do
        read asistentes
        if [[ $asistentes =~ ^[0-9]+$ ]]; then
            if test $asistentes -eq 0; then
                echo "Se necesita al menos un asistente"
            else
                break
            fi
        else
            echo "Has de introducir un entero positivo"
            sleep 1
        fi
    done
}

function titulo() {
    echo "

______  _  _         _      _          _____  _                    _         _                
|  ___|| |(_)       | |    | |        /  ___|(_)                  | |       | |               
| |_   | | _   __ _ | |__  | |_       \ \`--.  _  _ __ ___   _   _ | |  __ _ | |_   ___   _ __ 
|  _|  | || | / _\` || '_ \ | __|       \`--. \| || '_ \` _ \ | | | || | / _\` || __| / _ \ | '__|
| |    | || || (_| || | | || |_       /\__/ /| || | | | | || |_| || || (_| || |_ | (_) || |   
\_|    |_||_| \__, ||_| |_| \__|      \____/ |_||_| |_| |_| \__,_||_| \__,_| \__| \___/ |_|   
               __/ |                                                                     
              |___/                                                                      

    
                                        __|__
                                        \___/
                                         | |
                                         | |
                                        _|_|______________
                                                /|\\ 
                                              */ | \\*
                                              / -+- \\
                                          ---o--(_)--o---
                                            /  0 ' 0  \\
                                          */     |     \\*
                                          /      |      \\
                                        */       |       \\*
    "
}

function plane() {
    echo '
                      ___
                      \\ \
                       \\ `\
    ___                 \\  \
   |    \                \\  `\
   |_____\                \    \
   |______\                \    `\
   |       \                \     \
   |      __\__---------------------------------._.
 __|---~~~__o_o_o_o_o_o_o_o_o_o_o_o_o_o_o_o_o_o_[][\__
|___                         /~      )                \__
    ~~~---..._______________/      ,/_________________/
                           /      /
                          /     ,/
                         /     /
                        /    ,/
                       /    /
                      //  ,/
                     //  /
                    // ,/
                   //_/
                   
                   
                   '
}
opcion=8
mostrarMenu
while test $opcion -ne 4; do
    read opcion

    case $opcion in

    1)  cat Main.c
        echo;;
    2)
        echo "Compilando..."
        compilar
        sleep 1
        clear
        ;;
    3)
        echo $(clear)
        if ! test -f "a.out"; then
            echo "Para otra vez, recuerde compilar antes de ejecutar."
            sleep 2
            echo "Compilación automática"
            compilar
            sleep 1
        fi
        titulo
        comprobarArgumentos
        if test $asistentes -gt 25
        then
            echo "No existe un avión capaz de transportar a más de 550 personas."
            sleep 2
            echo "Aún así, lo intentaremos..."
            echo
            sleep 1
        else
            plane
            sleep 1
        fi
        ./a.out $asistentes
        ;;
    4)
        echo "Saliendo..."
        exit 0
        ;;
    *)
        clear
        echo "Debe seleccionar una opción válida"
        ;;

    esac

    sleep 1
    mostrarMenu
done
