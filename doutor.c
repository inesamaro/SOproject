#include "header.h"
void doutor(Config *config, int mqid) {
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	clock_t inicio = clock();
	clock_t fim = clock();
	double tempoTurno = (double)(fim - inicio) / CLOCKS_PER_SEC;

	printf("-- entrou no doutor()\n");
  while (((int)tempoTurno < config->tempoTurno)) {
	 fim = clock();
	 tempoTurno = (double)(fim - inicio) / CLOCKS_PER_SEC;
  }

	int msgrecieved;
	Node_paciente paciente = (Node_paciente)malloc(sizeof(Paciente));
	if ((msgrecieved = msgrcv(mqid, &paciente, sizeof(Paciente)-sizeof(long), -3, 0)) == -1){
		perror("Oh boy u got a error recieving a msg from the messagequeue");
	}
	printf("Paciente a ser tratado: %s\n", paciente->nome);

	pthread_mutex_lock(&mutex);
  (*shared_var).nAtendidos ++; //nao está a incrementar bem a shared_var
	pthread_mutex_unlock(&mutex);
}
