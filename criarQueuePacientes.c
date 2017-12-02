#include "header.h"

Paciente* criarQueuePacientes() {
  //criar cabeçalho da lista de pacientes (queue)
  Paciente* aux;
  aux = (Paciente*)malloc(sizeof(Paciente));
  if (aux != NULL) {
    aux->mtype = 0;
    printf("oi\n");
    strcpy(aux->info.nome, "");
    printf("oi\n");
    aux->info.numChegada = 0;
    printf("oi\n");
    aux->info.tempoTriagem = 0;
    printf("oi\n");
    aux->info.tempoAtend = 0;
    printf("oi\n");
    aux->info.inicio = 0;
    printf("oi\n");
    aux->info.inicioTriagem = 0;
    printf("oi\n");
    aux->info.inicioAtend = 0;
    printf("oi\n");
    aux->info.fimAtend = 0;
    printf("oi\n");
    aux->info.next = NULL;
    printf("oi\n");
  }
  printf("cria queuePacientes com sucesso!\n");
  return aux;
}
