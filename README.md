# Practica intermedia Sistemas Operativos 2022: Sincronización de procesos

## Objetivos
- Manejo de procesos y mecanismos de sincronización entre ellos.
-  Afianzar los conocimientos acerca del lenguaje C.
-  Afianzar los conocimientos acerca de los sistemas operativos.

## Evaluación
- Se comprobará el correcto funcionamiento del programa.
- Será obligatorio enviar el código a través de agora.unileon.es.
- La práctica se evaluará teniendo en cuenta el funcionamiento de la misma,
la claridad del código y la calidad de la solución aportada.

## Enunciado de la práctica
En este ejercicio se realizará un repaso de toda la materia vista hasta ahora así
como a algunos aspectos avanzados de C.
La presente pr´actica va a constar de dos partes:

1. Un programa que simula el funcionamiento del embarque de un vuelo. Para poder seguir la actividad del programa, es imprescindible que cada proceso muestre trazas de lo que hace en cada momento, identificando claramente qu´e proceso hace cada cosa.
2. Un script Shell que rpesenta un menú de cuatro opciones.

   - Si se selecciona la primera, opción el script muestra el código del
programa mediante el uso del comando ``cat`` (<code>cat programa.c</code>).
   - Si se selecciona la segunda, se lanzará la compilación del archivo .c
en que entregue el programa (``gcc programa.c -o programa``).
   - Si se escoge la tercera, se ejecutará el programa, siempre que exista el
ejecutable y tenga permisos de ejecución. Para proceder a dicha ejecución se pedirá el número de asistentes de vuelo que luego se pasará
como argumentos al programa. Debe controlarse que el mínimo de asistentes sea 1.
   - En caso de que se escoja la cuarta, se saldrá del script.

### Simulador de embarque

En este programa se va a simular el embarque de un vuelo. En concreto el
proceso principal simulará al coordinador del mismo. Este va a crear un proceso que será el técnico del avión, otro proceso que será el encargado del vuelo
y tantos procesos como asistentes de vuelo se hayan recibido como parámetros
en el programa. El técnico tiene que asegurarse de que el avión está listo para
despegar, el encargado de gestionar el overbooking, si lo hay, y los asistentes
asegurarse de que embarca cada grupo. Una vez creados los hijos técnico y encargado estos deberán esperar por la señal ``SIGUSR1`` que enviará el coordinador
dos segundos después de la creación de los procesos. En el caso del técnico,
una vez recibida la señal el proceso mostrará un mensaje, dormirá un número
aleatorio de segundos entre 3 y 6 y devolverá con exit un 1 si el vuelo es viable
y un 0 si no lo es (simule dicha situación con aleatorios). Si el vuelo no fuera
viable el coordinador matará a los procesos tecnico y encargado y terminará el
programa mostrando un mensaje con la razón. En caso de que sea viable el
coordinador enviará una señal (``SIGUSR1``) al proceso encargado que simulará si
hay overbooking con un aleatorio y dormirá 2 segundos. Si lo hubiera devolverá
un 1 y sino un 0. A diferencia del caso del técnico en este caso el coordinador
mostraría un mensaje de que hay overbooking y luego se procedería a enviar
una señal para proceder al embarque. Para ello el coordinador crearían tantos
procesos hijo como asistentes de vuelo haya. Dichos asistentes se quedarán esperando por la señal ``SIGUSR2`` que el coordinador enviará 2 segundos después
de haber creado los procesos. Una vez recibida la señal cada asistente simulará
el tiempo del embarque calculando un número aleatoria entre 3 y 6 segundos
que deberá dormir y finalizarán devolviendo un número entre 20 y 30 que serán
los pasajeros que embarca ese asistente. Nótese que el embarque no es secuencial sino que procederán todos los procesos a la vez. El coordinador recibirá los
pasajeros de cada asistente y debe imprimir la suma de todos ellos por pantalla.
En caso de que haya overbooking se restarán 10 al total de pasajeros.

## Otros aspectos a tener en cuenta
- **Es impresicndible que la práctica funcione correctamente**. Si esto no se tiene en cuenta, se obtendrá un 0
 en esta práctica
- No deben usarse variables globales a menos que los profesores especifiquen
lo contrario.
- Los nombres de las variables deben ser inteligibles.
-  El código debe estar indentado y deben usarse comentarios.
- Para esta práctica no deben utilizarse threads, solamente procesos y se˜nales
