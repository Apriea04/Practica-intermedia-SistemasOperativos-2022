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
int busca(pid_t valor, pid_t *array, int tamanyo);
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		return -1;
	}
	srand(time(NULL)); // Semilla del aleatorio
	pid_t tecnico, encargado, *asistentes, tmp;
	int estadoAvion, overbooking, numAsistentes, pasajeros, pasajerosAsistente, asistente, asistentesRestantes;
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
		exit(2);
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
	asistentes = (pid_t *)malloc(sizeof(pid_t) * numAsistentes);

	for (int i = 0; i < numAsistentes; i++)
	{
		tmp = fork();
		if (tmp == -1)
		{
			perror("Error con un asistente");
		}
		else if (tmp == 0)
		{
			// ASISTENTE
			ss.sa_handler = asis;
			if (-1 == sigaction(SIGUSR2, &ss, NULL))
			{
				perror("ASISTENTE: sigaction");
			}
			srand(getpid());
			while (1)
				pause();

			// Fin del asistente
		}
		else
		{
			asistentes[i] = tmp;
		}
	}

	// Asistentes contratados

	sleep(2); // Esperamos 2 segundos
	// Envío de órdenes a todos

	for (int i = 0; i < numAsistentes; i++)
	{
		kill(asistentes[i], SIGUSR2);
	}
	pasajeros = 0;

	// Recepción de pasajeros
	asistentesRestantes = numAsistentes; // Contador de asistentes sin finalizar
	tmp = wait(&pasajerosAsistente);
	while (tmp != -1)
	{
		asistentesRestantes--;
		asistente = busca(tmp, asistentes, numAsistentes);
		if (asistentesRestantes == 0 && overbooking)
		{ // Si es el último asistente y hay overbooking
			printf("COORDINADOR:\t El asistente %d intentó embarcar a %d pasajeros, pero solo hubo asiento para %d\n", asistente, WEXITSTATUS(pasajerosAsistente), WEXITSTATUS(pasajerosAsistente) - 10);
			pasajeros += WEXITSTATUS(pasajerosAsistente) - 10;
		}
		else
		{
			printf("COORDINADOR:\t El asistente %d ha embarcado a %d pasajeros\n", asistente, WEXITSTATUS(pasajerosAsistente));
			pasajeros += WEXITSTATUS(pasajerosAsistente);
		}

		tmp = wait(&pasajerosAsistente);
	}

	free(asistentes);
	printf("COORDINADOR:\t El vuelo sale con %d pasajeros\n", pasajeros);
	if (pasajeros > 550)
	{
		return (1);
	}
	else
	{
		return 0;
	}
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
/*
	Devuelve la posición de un valor en el vector. Precondición: el valor debe estar en el array.
*/
int busca(pid_t valor, pid_t *array, int tamanyo)
{
	int pos = 0;
	while (pos < tamanyo)
	{
		if (array[pos] == valor)
		{
			return pos + 1;
		}
		pos++;
	}
	return -1;
}