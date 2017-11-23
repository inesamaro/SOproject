#include "header.h"
#define PIPE_NAME "input_pipe"

int main(int argc, char *argv[]) {
  Config *config;
  config = (struct config*)malloc(sizeof(config));
  int shmid;
  int mqid;

  //definir a variavel queuePacientes aqui ou no header?
  //criar aqui a queue pacientes

  //criar a messagequeue
  mqid = criarMQ();
  printf("a message queue foi criada com sucesso");

  //argv[1] num de pacientes;
  signal(SIGINT, finalizar);

  printf("Leitura do config.txt\n");
  lerFichConfig(&config);

  //criação do pipe
  if ((mkfifo(PIPE_NAME, O_CREAT|O_EXCL|0600) < 0) & (errno!= EEXIST)) {
    perror("cannot open pipe!");
    exit(0);
  }
  printf("criou o pipe\n");

  int fd;
	if ((fd = open(PIPE_NAME, O_RDWR)) < 0) {
		perror("Cannot open pipe for writing: ");
		exit(0);
	}

  Node_paciente queuePacientes = sendReceivePipe(fd);

  //printf("Criação da memória partilhada.\n");
  //shmid = criarMemPartilhada();

  printf("Criação das threads triagem.\n");
  criarTriagens(&config, &queuePacientes, mqid);

  //printf(" num doutores antes: %d\n", config->nDoutores);
  //printf("Criação dos processos doutor.\n");
  //criarDoutores(&config);

  //criamos aqui a função continuacaoTriagem() ?

}
