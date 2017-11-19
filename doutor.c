#include "header.h"
void doutor(Config *config/*, Estat *shared_var*/) {
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	clock_t inicio = clock();
	clock_t fim = clock();
	double tempoTurno = (double)(fim - inicio) / CLOCKS_PER_SEC;

	printf("-- entrou no doutor()\n");
  while (((int)tempoTurno < config->tempoTurno)) {
	 fim = clock();
	 tempoTurno = (double)(fim - inicio) / CLOCKS_PER_SEC;
  }

	pthread_mutex_lock(&mutex);
  (*shared_var).nAtendidos ++; //nao está a incrementar bem a shared_var
	pthread_mutex_unlock(&mutex);
}
