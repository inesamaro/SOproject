#include "header.h"

void *triagem(Paciente *paciente){
  printf("TRIAGEM HAPPENING\n");

  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

  pthread_mutex_lock(&mutex);
  sleep((int)paciente->tempoTriagem);
  shared_var->nTriados += 1;
  printf("numero de pessoas triadas: %d \n", (shared_var)->nTriados);
  sendMQ(paciente);
  pthread_mutex_unlock(&mutex);

  return NULL;
}
