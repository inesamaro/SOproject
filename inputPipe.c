//#include "header.h"
#define PIPE_NAME "input_pipe"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>

typedef struct paciente *Node_paciente;
typedef struct paciente {
  char *nome;
  int numTriagem;
  int numAtend;
  int prioridade;
  clock_t inicio; //para calcularmos qunato tempo e que cada paciente gastou desde que entrou no sistema atá que saiu
  clock_t fim;
  Node_paciente next;
} Paciente;

Node_paciente criarQueuePacientes() {
  //criar cabeçalho da lista de pacientes (queue)
  Node_paciente aux;
  aux = (Node_paciente)malloc(sizeof(Paciente));
  if (aux != NULL) {
    aux->numTriagem = 0;
    aux->numAtend = 0;
    aux->prioridade = 0;
    aux->inicio = 0;
    aux->fim = 0;
  }
  return aux;
}

int main(int argc, char *argv[]) {
	printf("ola");
	int i;
	srand(time(NULL));
	Node_paciente p;
	if(argc != 2) {
		perror ("<numero de pacientes>");
		exit(1);
	}
  printf("argv 0 : %s\n", argv[0]);
  printf("argv 1 : %s\n", argv[1]);

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

  Node_paciente queuePacientes = criarQueuePacientes();

	for (i=0; i<atoi(argv[0]); i++) {
		printf("A criar um novo paciente: \n");
    p = (Node_paciente)malloc(sizeof(Paciente));
    p->nome = (char*)malloc(sizeof(50*sizeof(char)));
		strcpy(p->nome, nomes[rand()% 15]);
		p->numTriagem = (rand() % 50);
		p->numAtend = (rand() % 50);
		p->prioridade = (rand() % 3);
		p->inicio = clock();
		p->fim = 0;

		printf("A mandar para o pipe\n");
		write(fd, &p, sizeof(Paciente));
    //A adicionar o paciente a queue
    while (queuePacientes->next != NULL) {
      queuePacientes = queuePacientes->next;
    }
    queuePacientes->next = p;
    p->next = NULL;
	}

	return 0;
}
