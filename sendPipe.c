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


void main() {
  char array[6];
  char nomes[100][15] = {"Ines", "Filipa", "Ricardo", "José", "Maria", "António", "Luis", "Ana", "Adriana", "Mariana", "Carolina", "Bruno", "André", "Joana"};

  for (i=0; i<1; i++) {
    printf("A criar o primeiro array\n");
	  array[0] = nomes[rand()% 15];
		array[1] = itoa(rand() % 50);
		array[2] = itoa(rand() % 50);
		array[3] = itoa(rand() % 3);
		array[4] = itoa(clock());
		array[5] = "0";

		printf("A mandar para o pipe\n");
		write(fd, array, 6);
	}
}
