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

void main() {
  char array[6];
  Node_paciente queuePacientes = criarQueuePacientes();

  read(fd, array, 6);

  p = (Node_paciente)malloc(sizeof(Paciente));

  p->nome = (char*)malloc(sizeof(50*sizeof(char)));
  strcpy(p->nome, array[0]);
  p->numTriagem = array[1];
  p->numAtend = array[2];
  p->prioridade = array[3];
  p->inicio = array[4];
  p->fim = array[5];

  while (queuePacientes->next != NULL) {
    queuePacientes = queuePacientes->next;
  }
  queuePacientes->next = p;
  p->next = NULL;
  return(0);
}
