CC = gcc
CFLAGS =	 -D_REENTRANT -Wall -g
all:	 main.o criarDoutores.o criarMemPartilhada.o criarTriagens.o doutor.o lerFichConfig.o triagem.o finalizar.o header.h

	$(CC)	$(CFLAGS)	-o	exe main.o criarDoutores.o criarMemPartilhada.o criarTriagens.o doutor.o lerFichConfig.o triagem.o finalizar.o
main.o: main.c header.h
	$(CC) $(CFLAGS) -c main.c
#menu.o: menu.c header.h
#	        $(CC) $(CFLAGS) -c menu.c
criarDoutores.o: criarDoutores.c header.h
	$(CC) $(CFLAGS) -c criarDoutores.c
criarMemPartilhada.o: criarMemPartilhada.c header.h
	$(CC) $(CFLAGS) -c criarMemPartilhada.c
criarTriagens.o: criarTriagens.c header.h
	$(CC) $(CFLAGS) -c criarTriagens.c
doutor.o: doutor.c header.h
	$(CC) $(CFLAGS) -c doutor.c
triagem.o: triagem.c header.h
	$(CC) $(CFLAGS) -c triagem.c
lerFichConfig.o: lerFichConfig.c header.h
	$(CC) $(CFLAGS) -c lerFichConfig.c
finalizar.o: finalizar.c header.h
	$(CC) $(CFLAGS) -c finalizar.c

clean:
	rm -rf *.o

mrproper:	clean
		rm -rf header
