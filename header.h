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

typedef struct paciente {
  char *nome;
  int numTriagem;
  int numAtend;
  int prioridade;
  clock_t inicio;
  clock_t fim;
} Paciente;

typedef struct estat {
  int nTriados;
  int nAtendidos;
  int tempoMedioAntesTriagem;
  int tempoMedioAteAtend;
  int tempoMedioTotal;
} Estat;

Estat *shared_var;
int shmid;

typedef struct config {
  int nTriagens;
  int nDoutores;
  int tempoTurno;
  int queueMax;
} Config;

int main(int argc, char *argv[]);
void finalizar();
void lerFichConfig();
void criarDoutores();
void doutor();
void *triagem();
void criarTriagens();
int criarMemPartilhada();
