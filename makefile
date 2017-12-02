CC = gcc
CFLAGS =	 -D_REENTRANT -Wall -g -pthread
all:	 main.o lerFichConfig.o namedPipe.o criarQueuePacientes.o criarMemPartilhada.o criarMQ.o criarTriagens.o triagem.o sendMQ.o

	$(CC)	$(CFLAGS)	-o	exe main.o lerFichConfig.o namedPipe.o criarQueuePacientes.o criarMemPartilhada.o criarMQ.o criarTriagens.o triagem.o sendMQ.o
main.o: main.c header.h
	$(CC) $(CFLAGS) -c main.c
#menu.o: menu.c header.h
#	        $(CC) $(CFLAGS) -c menu.c
lerFichConfig.o: lerFichConfig.c header.h
	$(CC) $(CFLAGS) -c lerFichConfig.c

namedPipe.o: namedPipe.c header.h
	$(CC) $(CFLAGS) -c namedPipe.c

criarQueuePacientes.o: criarQueuePacientes.c header.h
	$(CC) $(CFLAGS) -c criarQueuePacientes.c

criarMemPartilhada.o: criarMemPartilhada.c header.h
	$(CC) $(CFLAGS) -c criarMemPartilhada.c

criarMQ.o: criarMQ.c header.h
	$(CC) $(CFLAGS) -c criarMQ.c

criarTriagens.o: criarTriagens.c header.h
	$(CC) $(CFLAGS) -c criarTriagens.c

triagem.o: triagem.c header.h
	$(CC) $(CFLAGS) -c triagem.c

sendMQ.o: sendMQ.c header.h
	$(CC) $(CFLAGS) -c sendMQ.c

clean:
	rm -rf *.o

mrproper:	clean
		rm -rf header
