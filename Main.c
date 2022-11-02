#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Para el srand
#include <sys/types.h>
#include <unistd.h>
#include <signal.h> //Para los números de las señales
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	srand(time(NULL)); // Semilla del aleatorio
	pid_t tecnico, encargado, *asistentes;
	int estadoAvion, overbooking, numAsistentes, pasajeros, pasajerosAsistente;
	tecnico = fork();
	if (tecnico == -1)
	{
		perror("Error con el técnico");
	}
	else if (tecnico == 0)
	{
		// TECNICO
		while (SIGUSR1 != pause())
			;
		printf("TÉCNICO:\t Comprobando estado del avión.\n");
		sleep(rand() % 4 + 3);
		exit(rand() % 2);
		// FIN DEL TÉCNICO
	}
	// COORDINADOR
	encargado = fork();
	if (encargado == -1)
	{
		perror("Error con el encargado");
	}
	else if (encargado == 0)
	{
		// ENCARGADO
		while (SIGUSR1 != pause())
			;
		printf("ENCARGADO:\t Comprobando overbooking.\n");
		sleep(2);
		exit(rand() % 2);
		// FIN DEL ENCARGADO
	}
	// COORDINADOR

	// Comprobación del avión:
	kill(tecnico, SIGUSR1);
	wait(&estadoAvion);
	estadoAvion = WEXITSTATUS(estadoAvion);
	if (estadoAvion)
	{
		// Si el vuelo es viable
		printf("COORDINADOR:\t El vuelo es viable.\n");
	}
	else
	{
		// Si el vuelo no es viable
		printf("COORDINADOR:\t El vuelo no es viable.\n");
		kill(encargado, SIGKILL); // Matamos al encargado
		exit(0);
	}

	// Comprobación de las reservas
	kill(encargado, SIGUSR1);
	wait(&overbooking);
	overbooking = WEXITSTATUS(overbooking);
	if (overbooking)
	{
		printf("COORDINADOR:\t Hay overbooking.\n");
	}
	else
	{
		printf("COORDINADOR:\t No hay overbooking.\n");
	}

	// CONTRATACIÓN DE ASISTENTES
	numAsistentes = atoi(argv[1]);
	asistentes = (pid_t *)malloc(sizeof(int) * numAsistentes);
	for (int i = 0; i < numAsistentes; i++)
	{
		*(asistentes + i) = fork();
		if (*(asistentes + i) == -1)
		{
			perror("Error con un asistente");
		}
		else if (*(asistentes) == 0)
		{
			// ASISTENTE
			sleep(rand() % 4 + 3);
			exit(rand() % 11 + 20);
			// Fin del asistente
		}
	}

	// Asistentes contratados
	sleep(2); // Esperamos 2 segundos
	pasajeros = 0;
	for (int i = 0; i < numAsistentes; i++)
	{
		kill(asistentes[i], SIGUSR2);
		wait(&pasajerosAsistente);
		pasajeros += WEXITSTATUS(pasajerosAsistente);
	}
	if (overbooking)
	{
		printf("COORDINADOR:\t Restamos 10 pasajeros por overbooking.\n");
		pasajeros -= 10;
	}
	printf("COORDINADOR:\t Despegamos con %d pasajeros.\n", pasajeros);
	return (0);
}