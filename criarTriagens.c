#include "header.h"
void criarTriagens(Config *config) {
  pthread_t vTriagens[config->nTriagens];
  int i;
  int idsTriagens[config->nTriagens];
  //cria o numero de triagens necessarias
  for (i=0; i<config->nTriagens; i++) {
    idsTriagens[i] = i;
    pthread_create(&vTriagens[i], NULL, triagem, &idsTriagens[i]);
    printf("NOVA TRIAGEM\n");
    
  }

  for (i=0; i<config->nTriagens; i++) {
    pthread_join(vTriagens[i], NULL);
  }
}