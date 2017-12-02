#include "header.h"

int main(int argc, char *argv[]){
config = (Config*)malloc(sizeof(Config));
  lerFichConfig();

  queuePacientes = criarQueuePacientes();

  queuePacientes = namedPipe();

  criarMQ();

  criarTriagens();
}
