#include "header.h"

void *triagem(Paciente *paciente){
  printf("TRIAGEM HAPPENING\n");

  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

  pthread_mutex_lock(&mutex);
  while(1){
    sleep((int)paciente->tempoTriagem);
    shared_var->nTriados += 1;
    printf("numero de pessoas triadas: %d \n", (shared_var)->nTriados);
    sendMQ(paciente);
    if(queuePacientes->next != NULL){
      paciente = queuePacientes->next;
      printf("----------------------------\n");
      queuePacientes->next = (queuePacientes->next)->next;
    }
    else{
      break; //esta break porque o numero de pacientes nao se altera, aqui vai ficar um sleep(1) para que de 1 em 1 segundo ver se chegou alguem ao hospital para ser triado ate ao hospital fechar com o ctrl-c ou assim, acho eu ahah
    }
  }



  pthread_mutex_unlock(&mutex);

  return NULL;
}
