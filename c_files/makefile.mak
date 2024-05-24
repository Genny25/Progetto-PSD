main.exe: utile.o data.o sala.o lista_sala.o evento.o bst_evento.o conferenza.o main.o
	gcc -I./header_files utile.o data.o sala.o lista_sala.o evento.o bst_evento.o conferenza.o main.o -o main.exe

utile.o: utile.c header_files/utile.h
	gcc -c -I./header_files utile.c

data.o: data.c header_files/data.h
	gcc -c -I./header_files data.c

sala.o: sala.c header_files/sala.h
	gcc -c -I./header_files sala.c

lista_sala.o: lista_sala.c header_files/lista_sala.h
	gcc -c -I./header_files lista_sala.c

evento.o: evento.c header_files/evento.h
	gcc -c -I./header_files evento.c

bst_evento.o: bst_evento.c header_files/bst_evento.h
	gcc -c -I./header_files bst_evento.c

conferenza.o: conferenza.c header_files/conferenza.h
	gcc -c -I./header_files conferenza.c

main.o: main.c header_files/conferenza.h
	gcc -c -I./header_files main.c

clean:
	rm -f *.o main.exe
