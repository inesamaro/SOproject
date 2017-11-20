#include "header.h"

void *triagem(Node_paciente queuePacientes, int mqid) {
  printf("entrou na triagem\n");
  int mqid;
  Node_paciente paciente;
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&mutex);
  //elimina o primeiro paciente da queuePacientes
  paciente = queuePacientes;
  queuePacientes = queuePacientes->next;

  //printa a queuePacientes para termos a certeza que ele foi emsmo eliminado.
  Node_paciente aux = queuePacientes->next;
  while(aux->next != NULL) {
    printf("nome: %s\n", aux->nome);
    aux = aux->next;
  }
  pthread_mutex_unlock(&mutex);

  sleep(paciente->tempoTriagem);
  //chamada da função relativa á messagequeue que recebe este paciente
  putInMQ(Node_paciente paciente, mqid);

  pthread_mutex_lock(&mutex);
  (*shared_var).nTriados ++;
  pthread_mutex_unlock(&mutex);
  //fazer sleep no tempo definido na estrutura paciente
  //chamar a função sendMessageQueue

  return NULL;
}
