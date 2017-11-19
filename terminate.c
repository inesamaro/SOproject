void terminate() {
  shmdt(shared_var);
  shmctl(shmid, IPC_RMID, NULL);
  //pthread_exit(NULL); terminar as threads em segunça
}
