#include "header.h"

void *triagem() {
  //something
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&mutex);
  //trabalho da thread
  //chama a queuePacientes e retira o ultimo
  //anda com a queue uma unidade para a frente
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);

  pthread_mutex_lock(&mutex);
  (*shared_var).nTriados ++;
  pthread_mutex_unlock(&mutex);
  //fazer sleep no tempo definido na estrutura paciente
  //chamar a função sendMessageQueue
  return NULL;
}
