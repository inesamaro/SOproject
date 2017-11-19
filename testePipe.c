
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

char* itoa(int val, int base){
	static char buf[32] = {0};
	int i = 30;

	for(; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return &buf[i+1];
}

int main(int argc, char *argv[]) {
  if ((mkfifo(PIPE_NAME, O_CREAT|O_EXCL|0600) < 0) & (errno!= EEXIST)) {
    perror("cannot open pipe!");
    exit(0);
  }

  int fd;
  if ((fd = open(PIPE_NAME, O_RDWR)) < 0) {
    perror("Cannot open pipe for writing: ");
    exit(0);
  }

  char array[100][6];
  char nomes[100][15] = {"Ines", "Filipa", "Ricardo", "José", "Maria", "António", "Luis", "Ana", "Adriana", "Mariana", "Carolina", "Bruno", "André", "Joana"};
  int i;
  for (i=0; i<3; i++) {
    printf("A criar o primeiro array\n");
    strcpy(&array[100][0], &nomes[100][rand()% 15]);
    printf("array[0] %s", &array[100][0]);

    strcpy(&array[100][1], itoa(rand() % 50, 10));
    printf("array[1] %s", &array[100][0]);

    strcpy(&array[100][2], itoa(rand() % 50, 10));
    printf("array[2] %s", &array[100][0]);

    strcpy(&array[100][3], itoa(rand() % 3, 10));
    printf("array[3] %s", &array[100][0]);
    strcpy(&array[100][4], itoa(clock(), 10));
    printf("array[4] %s", &array[100][0]);
    strcpy(&array[100][5], itoa(0, 10));
    printf("array[5] %s", &array[100][0]);

    printf("A mandar para o pipe\n");
    write(fd, array, 6);
  }

  Node_paciente queuePacientes = criarQueuePacientes();

  read(fd, array, 6);
  printf("leu array!");

  Node_paciente p;
  p = (Node_paciente)malloc(sizeof(Paciente));

  p->nome = (char*)malloc(sizeof(50*sizeof(char)));
  strcpy(p->nome, &array[100][0]);
  p->numTriagem = array[100][1];
  p->numAtend = array[100][2];
  p->prioridade = array[100][3];
  p->inicio = array[100][4];
  p->fim = array[100][5];

  while (queuePacientes->next != NULL) {
    queuePacientes = queuePacientes->next;
  }
  queuePacientes->next = p;
  p->next = NULL;
  printf("criou paciente!\n");
}
