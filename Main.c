#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Para el srand
#include <sys/types.h>
#include <unistd.h>
#include <signal.h> //Para los números de las señales
#include <sys/wait.h>
void tec(int sig);
void encar(int sig);
void asis(int sig);
int main(int argc, char *argv[])
{
	srand(time(NULL)); // Semilla del aleatorio
	pid_t tecnico, encargado, *asistentes;
	int estadoAvion, overbooking, numAsistentes, pasajeros, pasajerosAsistente;
	struct sigaction ss;
	tecnico = fork();
	if (tecnico == -1)
	{
		perror("Error con el técnico");
	}
	else if (tecnico == 0)
	{
		// TECNICO
		ss.sa_handler = tec;
		if (-1 == sigaction(SIGUSR1, &ss, NULL))
		{
			perror("TECNICO: sigaction");
		}
		while (1)
			pause();
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
		ss.sa_handler = encar;
		if (-1 == sigaction(SIGUSR1, &ss, NULL))
		{
			perror("ENCARGADO: sigaction");
		}
		while (1)
			pause();
		// FIN DEL ENCARGADO
	}
	// COORDINADOR

	// Comprobación del avión:
	sleep(1); // Tiempo de margen por seguridad
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
	printf("PATATA %d", numAsistentes);
	asistentes = (pid_t *)malloc(sizeof(pid_t) * numAsistentes);
	printf("PATATA");
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
			ss.sa_handler = asis;
			if (-1 == sigaction(SIGUSR2, &ss, NULL))
			{
				perror("ASISTENTE: sigaction");
			}
			while (1)
				pause();

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
void tec(int sig)
{
	printf("TÉCNICO:\t Comprobando estado del avión.\n");
	sleep(rand() % 4 + 3);
	exit(rand() % 2);
}

void encar(int sig)
{
	printf("ENCARGADO:\t Comprobando overbooking.\n");
	sleep(2);
	exit(rand() % 2);
}
void asis(int sig)
{
	sleep(rand() % 4 + 3);
	exit(rand() % 11 + 20);
}