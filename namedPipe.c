#include "header.h"

Paciente* namedPipe() {
  if ((mkfifo(PIPE_NAME, O_CREAT|O_EXCL|0600) < 0) & (errno!= EEXIST)) {
    perror("cannot open pipe!");
    exit(0);
  }
  else{
    printf("Criou o pipe\n");
  }

  if ((fdpipe = open(PIPE_NAME, O_RDWR)) < 0) {
    perror("Cannot open pipe for writing: ");
    exit(0);
  }


  FILE *fich = fopen("infoPacientes.txt", "r");
  char linha[400], info[50];
  //envia cada uma das linhas do ficheiro pelo pipe. LE TODAS AS LINHAS
  while (fscanf(fich, " %[^\n]", linha) != EOF) {
    write(fdpipe, linha, 400);
    printf("linha lida: %s\n", linha);

    char line[400], c;
    int count = 0;
    int ind = 0;

    read(fdpipe, line, 400);
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
    strcpy(p->info.nome, info);
    c = line[ind++];
    count = 0;
    printf("nome: %s\n", p->info.nome);

    //tempoTriagem
    while ((c = line[ind]) != ' ') {
      info[count] = c;
      count ++;
      ind ++;
    }
    p->info.tempoTriagem = atoi(info);
    c = line[ind++];
    count =0;
    printf("tempotriagem: %d\n", p->info.tempoTriagem);

    //tempoAtend
    while ((c = line[ind]) != ' ') {
      info[count] = c;
      count ++;
      ind ++;
    }
    p->info.tempoAtend = atoi(info);
    c = line[ind++];
    count =0;
    printf("tempoAtend: %d\n", p->info.tempoAtend);

    //prioridade
    while ((c = line[ind]) != EOF) {
      info[count] = c;
      count ++;
      ind ++;
    }
    p->mtype = atoi(info);
    count =0;
    printf("prioridade: %ld\n", p->mtype);

    p->info.inicio = clock();
    p->info.inicioAtend = 0;
    p->info.inicioTriagem = 0;
    p->info.fimAtend = 0;

    Node_paciente aux = queuePacientes;
    while (aux->info.next != NULL) {
      aux = aux->info.next;
    }
    aux->info.next = p;
    printf("nome na queue: %s\n", (aux->info.next)->info.nome);
    p->info.next = NULL;
  }
  return queuePacientes;
}
