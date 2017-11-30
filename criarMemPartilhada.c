#include "header.h"
int criarMemPartilhada() {
  if ((shmid = shmget(IPC_PRIVATE, sizeof(Estat), IPC_CREAT|0777)) > 0 ) {

    shared_var = shmat(shmid, NULL, 0);
    (*shared_var).nTriados = 0;
    (*shared_var).nAtendidos = 0;
    (*shared_var).tempoMedioAntesTriagem = 0;
    (*shared_var).tempoMedioAteAtend = 0;
    (*shared_var).tempoMedioTotal = 0;

    /*printf("Valores:\n");
    printf("nTriados %d\n", (*shared_var).nTriados);
    printf("nAtendidos %d\n", (*shared_var).nAtendidos);
    printf("tempoMedioAntesTriagem %d\n", (*shared_var).tempoMedioAntesTriagem);
    printf("tempoMedioAteAtend %d\n", (*shared_var).tempoMedioAteAtend);
    printf("tempoMedioTotal %d\n", (*shared_var).tempoMedioTotal);*/
  }
  else {
    printf("Erro ao criar a memória partilhada!");
  }
  return shmid;
}
