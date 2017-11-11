#include "header.h"

int main(int argc, char *argv[]) {
  Config *config;
  config = (struct config*)malloc(sizeof(config));
  int shmid;

  signal(SIGINT, finalizar);

  printf("O programa vai começar!\n");
  printf("Leitura do config.txt\n");
  lerFichConfig(&config);

  printf("Criação da memória partilhada.\n");
  shmid = criarMemPartilhada();

  printf("Criação das threads triagem.\n");
  criarTriagens(&config);

  //printf(" num doutores antes: %d\n", config->nDoutores);
  printf("Criação dos processos doutor.\n");
  criarDoutores(&config);


}
