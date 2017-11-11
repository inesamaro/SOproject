#include "header.h"
void lerFichConfig(Config *config) {

  FILE *fich = fopen("config.txt", "r");
  int count=0, len;
  char linha[500], numero[400];

  while (fscanf(fich, " %[^=]", linha) != EOF) {
    fgetc(fich);
    fscanf(fich, " %[^\n]", numero);

    len = strlen(numero);
    if (count == 0) {
      config->nTriagens = atoi(numero);
    }
    else if (count == 1) {
      config->nDoutores = atoi(numero);
    }
    else if (count == 2) {
      config->tempoTurno = atoi(numero);
    }
    else if (count == 3) {
      config->queueMax = atoi(numero);
    }
    count ++;
  }

  printf("nTriagens %d\n", config->nTriagens);
  printf("nDoutores %d\n", config->nDoutores);
  printf("tempoTurno %d\n", config->tempoTurno);
  printf("queueMax %d\n", config->queueMax);
}
