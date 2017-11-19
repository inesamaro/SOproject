
#define PIPE_NAME "input_pipe"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>

typedef struct paciente *Node_paciente;
typedef struct paciente {
  char *nome;
  int numChegada;
  int tempoTriagem;
  int tempoAtend;
  int prioridade;
  clock_t inicio; //para calcularmos qunato tempo e que cada paciente gastou desde que entrou no sistema atá que saiu
  clock_t fim;
  Node_paciente next;
} Paciente;

Node_paciente criarQueuePacientes() {
  //criar cabeçalho da lista de pacientes (queue)
  Node_paciente aux;
  aux = (Node_paciente)malloc(sizeof(Paciente));
  if (aux != NULL) {
    aux->nome = NULL;
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

int main(int argc, char *argv[]) {
  if ((mkfifo(PIPE_NAME, O_CREAT|O_EXCL|0600) < 0) & (errno!= EEXIST)) {
    perror("cannot open pipe!");
    exit(0);
  }

  int fd;
  if ((fd = open(PIPE_NAME, O_RDWR)) < 0) {
    perror("Cannot open pipe for writing: ");
    exit(0);
  }

  FILE *fich = fopen("infoPacientes.txt", "r");
  char linha[400], info[50];
  int i, j;
  //envia cada uma das linhas do ficheiro pelo pipe. LE TODAS AS LINHAS
  while (fscanf(fich, " %[^\n]", linha) != EOF) {
    write(fd, linha, 400);
    printf("linha lida: %s\n", linha);


    char line[400], c;
    int count=0, valor;
    int ind = 0;
    Node_paciente queuePacientes = criarQueuePacientes();
      read(fd, line, 400);
      printf("leu uma linha!\n");
      Node_paciente p;
      p = (Node_paciente)malloc(sizeof(Paciente));
      //nome
      p->nome = (char*)malloc(sizeof(char)*50);
      while ((c = line[ind]) != ' ') {
        info[count] = c;
        count ++;
        ind ++;
      }
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
      printf("info %s\n", info);
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
      printf("prioridade: %d\n", p->prioridade);


      printf("antes do while\n");
      while (queuePacientes->next != NULL) {
        queuePacientes = queuePacientes->next;
      }
      queuePacientes->next = p;
      printf("nome na queue: %s\n", queuePacientes->next->nome);
      p->next = NULL;
  }
  printf("criou paciente!\n");
}
