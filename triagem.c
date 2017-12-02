#include "header.h"

void *triagem(Paciente *paciente){
  printf("TRIAGEM HAPPENING\n");

  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

  pthread_mutex_lock(&mutex);

  sleep((int)paciente->tempoTriagem);
  sendMQ(paciente);

  //shared_var->nTriados = 1;
  //printf("tempo: %d \n", (shared_var)->nTriados);

  pthread_mutex_unlock(&mutex);

  return NULL;
}
