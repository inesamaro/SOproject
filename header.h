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

typedef struct infoPaciente {
  char nome[50];
  int numChegada;
  int tempoTriagem;
  int tempoAtend;
  clock_t inicio; //para calcularmos qunato tempo e que cada paciente gastou desde que entrou no sistema atá que saiu
  clock_t inicioTriagem;;
  clock_t inicioAtend;
  clock_t fimAtend;
  Node_paciente next;
} InfoPaciente;


typedef struct paciente {
  long int mtype;
  InfoPaciente info;
  /*char nome[50];
  int numChegada;
  int tempoTriagem;
  int tempoAtend;
  clock_t inicio; //para calcularmos qunato tempo e que cada paciente gastou desde que entrou no sistema atá que saiu
  clock_t inicioTriagem;;
  clock_t inicioAtend;
  clock_t fimAtend;
  Node_paciente next;*/
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
Paciente* queuePacientes;
//vars for mq
int shmid;
int mqid;
//vars for pipe
int fdpipe;
//sem_t semAtend;
//sem_init(&semAtend, 0, 1);

void lerFichConfig();
Paciente* namedPipe();
Paciente* criarQueuePacientes();
void criarMemPartilhada();
void criarMQ();
void criarTriagens();
void *triagem();
void criarDoutor();
void atendimento();
void sendMQ(Paciente paciente);
