#include "header.h"

void *triagem() {
  printf("Entrou na funcao triagem\n");
  Node_paciente paciente;
  printf("%s\n", queuePacientes->next->nome);
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

  pthread_mutex_lock(&mutex);

  //elimina o primeiro paciente da queuePacientes
  //printf("Paciente na queue: %s\n", queuePacientes->next->nome);
  paciente = queuePacientes->next;
  printf("Paciente que vai ser eliminado: %s\n", paciente->nome);
  queuePacientes->next = (queuePacientes->next)->next;

  //printa a queuePacientes para termos a certeza que ele foi emsmo eliminado.
  Node_paciente aux = queuePacientes;
  printf("QueuePacientes depois de eliminar: \n");
  while(aux->next != NULL) {
    aux = aux->next;
    printf("nome: %s\n", aux->nome);
  }

  sleep((int)paciente->tempoTriagem);
  printf("\nAntes da putInMQ\n");
  //putInMQ(paciente);
  int msgsend;
  if ((msgsend = msgsnd(mqid, &paciente, sizeof(Paciente)-sizeof(long), 0)) == -1){
    perror("Oh boy");
  }

  pthread_mutex_unlock(&mutex);

  pthread_mutex_lock(&mutex);
  (*shared_var).nTriados ++;
  pthread_mutex_unlock(&mutex);
  //fazer sleep no tempo definido na estrutura paciente
  //chamar a função sendMessageQueue

  return NULL;
}
