#include "header.h"

int main(int argc, char *argv[]) {
  Config *config;
  config = (struct config*)malloc(sizeof(config));
  int shmid;

  //argv[1] num de pacientes;
  signal(SIGINT, finalizar);

  printf("Leitura do config.txt\n");
  lerFichConfig(&config);

  //criação do pipe
  if (mkfifo(PIPE_NAME, O_CREAT|O_EXCL|0600) < 0) {
    perror("cannot open pipe!");
    exit(0);
  }

  int fd;
	if ((fd = open(PIPE_NAME, O_RDWR)) < 0) {
		perror("Cannot open pipe for writing: ");
		exit(0);
	}
  sendPipe(fd, argv[1]);
  receivePipe(fd);
  
  printf("Criação da memória partilhada.\n");
  shmid = criarMemPartilhada();

  printf("Criação das threads triagem.\n");
  criarTriagens(&config);

  //printf(" num doutores antes: %d\n", config->nDoutores);
  printf("Criação dos processos doutor.\n");
  criarDoutores(&config);


}
