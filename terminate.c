void terminate() {
  shmdt(all_statistics);
  shmctl(shmid, IPC_RMID, NULL);
  //pthread_exit(NULL); terminar as threads em segunça
}
