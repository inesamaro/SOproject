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
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/msg.h>


#define PIPE_NAME "input_pipe"

typedef struct paciente *Node_paciente;
typedef struct paciente {
  long prioridade;
  char nome[50];
  int numChegada;
  int tempoTriagem;
  int tempoAtend;
  clock_t inicio; //para calcularmos qunato tempo e que cada paciente gastou desde que entrou no sistema atá que saiu
  clock_t fim;
  Node_paciente next;
} Paciente;

typedef struct estat {
  int nTriados;
  int nAtendidos;
  int tempoMedioAntesTriagem;
  int tempoMedioAteAtend;
  int tempoMedioTotal;
} Estat;

typedef struct config {
  int nTriagens;
  int nDoutores;
  int tempoTurno;
  int queueMax;
} Config;

Estat *shared_var;
Config *config;
Node_paciente queuePacientes;
int shmid;
int mqid;


int main(int argc, char *argv[]);
void finalizar();
void lerFichConfig();
void criarDoutores();
void doutor();
void *triagem();
void criarTriagens();
int criarMemPartilhada();
int criarMQ();
void putInMQ();
void recieveFromMQ();

Node_paciente sendReceivePipe();
Node_paciente criarQueuePacientes();
