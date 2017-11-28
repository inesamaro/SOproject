#include "header.h"

Node_paciente criarQueuePacientes() {
  //criar cabeçalho da lista de pacientes (queue)
  Node_paciente aux;
  aux = (Node_paciente)malloc(sizeof(Paciente));
  if (aux != NULL) {
    strcpy(aux->nome, "");
    aux->numChegada = 0;
    aux->tempoTriagem = 0;
    aux->tempoAtend = 0;
    aux->prioridade = 0;
    aux->inicio = 0;
    aux->fim = 0;
    aux->next = NULL;
  }
  printf("cria queuePacientes com sucesso!\n");
  return aux;
}
