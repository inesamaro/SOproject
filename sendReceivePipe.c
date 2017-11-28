#include "header.h"

Node_paciente sendReceivePipe(int fd) {
  Node_paciente queuePacientes = criarQueuePacientes();

  FILE *fich = fopen("infoPacientes.txt", "r");
  char linha[400], info[50];
  //envia cada uma das linhas do ficheiro pelo pipe. LE TODAS AS LINHAS
  while (fscanf(fich, " %[^\n]", linha) != EOF) {
    write(fd, linha, 400);
    printf("linha lida: %s\n", linha);

    char line[400], c;
    int count = 0;
    int ind = 0;

    read(fd, line, 400);
    printf("leu uma linha!\n");
    Node_paciente p;
    p = (Node_paciente)malloc(sizeof(Paciente));
    //nome
    while ((c = line[ind]) != ' ') {
      info[count] = c;
      count ++;
      ind ++;
    }
    info[count] = '\0';
    strcpy(p->nome, info);
    c = line[ind++];
    count = 0;
    printf("nome: %s\n", p->nome);

    //tempoTriagem
    while ((c = line[ind]) != ' ') {
      info[count] = c;
      count ++;
      ind ++;
    }
    p->tempoTriagem = atoi(info);
    c = line[ind++];
    count =0;
    printf("tempotriagem: %d\n", p->tempoTriagem);

    //tempoAtend
    while ((c = line[ind]) != ' ') {
      info[count] = c;
      count ++;
      ind ++;
    }
    p->tempoAtend = atoi(info);
    c = line[ind++];
    count =0;
    printf("tempoAtend: %d\n", p->tempoAtend);

    //prioridade
    while ((c = line[ind]) != EOF) {
      info[count] = c;
      count ++;
      ind ++;
    }
    p->prioridade = atoi(info);
    count =0;
    printf("prioridade: %ld\n", p->prioridade);

    Node_paciente aux = queuePacientes;
    while (aux->next != NULL) {
      aux = aux->next;
    }
    aux->next = p;
    printf("nome na queue: %s\n", aux->next->nome);
    p->next = NULL;
  }
  return queuePacientes;
}
