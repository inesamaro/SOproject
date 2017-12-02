#include "header.h"

Paciente* criarQueuePacientes() {
  //criar cabeçalho da lista de pacientes (queue)
  Paciente* aux;
  aux = (Paciente*)malloc(sizeof(Paciente));
  if (aux != NULL) {
    strcpy(aux->nome, "");
    aux->numChegada = 0;
    aux->tempoTriagem = 0;
    aux->tempoAtend = 0;
    aux->prioridade = 0;
    aux->inicio = 0;
    aux->inicioTriagem = 0;
    aux->inicioAtend = 0;
    aux->fimAtend = 0;
    aux->next = NULL;
  }
  printf("cria queuePacientes com sucesso!\n");
  return aux;
}
