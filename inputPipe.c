//#include "header.h"
#define PIPE_NAME "input_pipe"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

typedef struct paciente {
  char *nome;
  int numTriagem;
  int numAtend;
  int prioridade;
  clock_t inicio; //para calcularmos qunato tempo e que cada paciente gastou desde que entrou no sistema atá que saiu
  clock_t fim;
} Paciente;

int main(int argc, char *argv[]) {
	printf("ola");
	int i;
	srand(time(NULL));
	Paciente p;
	if(argc != 2) {
		perror ("<numero de pacientes>");
		exit(1);
	}

	if (mkfifo(PIPE_NAME, O_CREAT|O_EXCL|0600) < 0) {
		perror("cannot open pipe!");
		exit(0);
	}

	// Opens the pipe for writing
	int fd;
	if ((fd = open(PIPE_NAME, O_WRONLY)) < 0) {
		perror("Cannot open pipe for writing: ");
		exit(0);
	}

	char nomes[100][15] = {"Ines", "Filipa", "Ricardo", "José", "Maria", "António", "Luis", "Ana", "Adriana", "Mariana", "Carolina", "Bruno", "André", "Joana"};
	printf("ola");

	for (i=0; i<atoi(argv[0]); i++) {
		printf("A criar um novo paciente: \n");
		strcpy(p.nome, nomes[rand()% 15]);
		p.numTriagem = rand() % 50;
		p.numAtend = rand() % 50;
		p.prioridade = rand() % 3;
		p.inicio = clock();
		p.fim = 0;
		printf("A mandar para o pipe\n");
		write(fd, &p, sizeof(Paciente));
	}

	return 0;
}
