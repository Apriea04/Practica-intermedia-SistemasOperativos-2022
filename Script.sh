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
    gcc programa.c -o programa
}

function comprobarArgumentos() {
    echo "Introduce el número de asistentes"
    echo
    while true
    do
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

function nave() {
    echo "
                   /\\
                  /''\\
                 /    \\
                /      \\
               /        \\
              /          \\
             '------------'
              |__________|
              /----/\----\\
             /|    ||    |\\
            //|____||____|\\\\
           //  |   ||   |  \\\\
          / |  |___||___|  | \\
          | |   '._||_.'   | |
          | |    |_||_|    | |
          | |  .'  ||  '.  | |
          | | /    ||    \ | |
          | ||     ||     || |
          | ||     ||     || |
          | | \    ||    / | |
          | |  '. _||_ .'  | |
          | | _    ||    _ | |
          | |/ \_.'||'._/ \| |
          | |\_/ '.||.' \_/| |
          | |     _||_     | |
         /| |  .'  ||  '.  | |\\
        / '.| /    ||    \ |.' \\
       /   |||     ||     |||   \\
      /    |||     ||     |||    \\
     /     || \    ||    / ||     \\
    /____/\||__'. _||_ .'__||/\____\\
           |_.--^--||--^--._|
          / .'/_'''||'''_\'. \\
         / /   /___||___\   \ \\
        / /     /__||__\     \ \\
       / /         ||         \ \\
      /.'          ||          '.\\
     //            ||            \\\\
  __//_          __||__          _\\\\__
 '====='        '======'        '====='

"
}

function cancelled() {
    echo '

   ____    _    _   _  ____ _____ _     _     _____ ____  
  / ___|  / \  | \ | |/ ___| ____| |   | |   | ____|  _ \ 
 | |     / _ \ |  \| | |   |  _| | |   | |   |  _| | | | |
 | |___ / ___ \| |\  | |___| |___| |___| |___| |___| |_| |
  \____/_/   \_\_| \_|\____|_____|_____|_____|_____|____/ 
                                                          

    '
}
opcion=8
mostrarMenu
while true
do
    read opcion
    
    case $opcion in

    1)  cat programa.c
        echo;;
    2)
        echo "Compilando..."
        compilar
        sleep 2
        clear
        ;;
    3)
        echo $(clear)
        if ! test -f "programa"; then
            echo "Ha de compilar antes de ejecutar."
            sleep 2
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
        fi
        ./programa $asistentes
        pasajeros=$?
        sleep 1
        if test $pasajeros -eq 1
        then
            echo
            echo "No existe un avión capaz de transportar a tantos pasajeros."
            sleep 2
            echo "Preparando nave..."
            echo
            echo
            sleep 1
            nave
            sleep 2
            i=0
            while test $i -lt 60
            do
                sleep 0.05
                echo
                i=`expr $i + 1`
            done
        elif test $pasajeros -eq 0
        then
            plane
        else
            cancelled
        fi
        exit 0
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

    mostrarMenu

done
