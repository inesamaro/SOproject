#include "header.h"

void criarTriagens() {
  pthread_t vTriagens[config->nTriagens];
  int i;
  int idsTriagens[config->nTriagens];
  Paciente * paciente;

  //cria o numero de triagens necessarias
  for (i=0; i<config->nTriagens; i++) {
    idsTriagens[i] = i;
    paciente = queuePacientes->next;
    printf("Paciente que vai ser eliminado: %s\n", paciente->nome);
    queuePacientes->next = (queuePacientes->next)->next;

    pthread_create(&vTriagens[i], NULL, triagem, paciente);

    Paciente* aux = queuePacientes;
    printf("QueuePacientes depois de eliminar: \n");
    while(aux->next != NULL) {
      aux = aux->next;
      printf("nome: %s\n", aux->nome);
    }
  }

  for (i=0; i<config->nTriagens; i++) {
    pthread_join(vTriagens[i], NULL);
  }
}
 
