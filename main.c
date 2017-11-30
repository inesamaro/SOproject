#include "header.h"
#define PIPE_NAME "input_pipe"

int main(int argc, char *argv[]) {
  config = (struct config*)malloc(sizeof(Config));
  //definir a variavel queuePacientes aqui ou no header?
  //criar aqui a queue pacientes

  //criar a messagequeue
  criarMQ();

  printf("Criou a message queue\n");

  //argv[1] num de pacientes;
  signal(SIGINT, finalizar);
  printf("-------------------- mqid: %d\n", mqid);
  printf("Leitura do config.txt\n");
  lerFichConfig(config);
  printf("------ mqid: %d\n", mqid);
  //criação do pip
  if ((mkfifo(PIPE_NAME, O_CREAT|O_EXCL|0600) < 0) & (errno!= EEXIST)) {
    perror("cannot open pipe!");
    exit(0);
  }
  printf("Criou o pipe\n");

  int fd;
	if ((fd = open(PIPE_NAME, O_RDWR)) < 0) {
		perror("Cannot open pipe for writing: ");
		exit(0);
	}

  queuePacientes = sendReceivePipe(fd);

  printf("Criação da memória partilhada.\n");
  shmid = criarMemPartilhada();

  printf("Criação das threads triagem.\n");
  criarTriagens(config);

  printf("Criação dos processos doutor.\n");
  criarDoutores(config);

  //criamos aqui a função continuacaoTriagem() ?
  wait(NULL);
}
