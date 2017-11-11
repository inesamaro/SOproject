#include "header.h"

void *triagem() {
  //something
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&mutex);
  //trabalho da thread
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);

  pthread_mutex_lock(&mutex);
  (*shared_var).nTriados ++;
  pthread_mutex_unlock(&mutex);
  return NULL;
}
