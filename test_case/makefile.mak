run_test.exe: c_files/utile.o c_files/data.o c_files/sala.o c_files/lista_sala.o c_files/evento.o c_files/bst_evento.o c_files/conferenza.o utile_test.o run_test.o
	gcc -I./header_files c_files/utile.o c_files/data.o c_files/sala.o c_files/lista_sala.o c_files/evento.o c_files/bst_evento.o c_files/conferenza.o utile_test.o run_test.o -o run_test.exe

c_files/utile.o: c_files/utile.c header_files/utile.h
	gcc -c -I./header_files c_files/utile.c -o c_files/utile.o

c_files/data.o: c_files/data.c header_files/data.h
	gcc -c -I./header_files c_files/data.c -o c_files/data.o

c_files/sala.o: c_files/sala.c header_files/sala.h
	gcc -c -I./header_files c_files/sala.c -o c_files/sala.o

c_files/lista_sala.o: c_files/lista_sala.c header_files/lista_sala.h
	gcc -c -I./header_files c_files/lista_sala.c -o c_files/lista_sala.o

c_files/evento.o: c_files/evento.c header_files/evento.h
	gcc -c -I./header_files c_files/evento.c -o c_files/evento.o

c_files/bst_evento.o: c_files/bst_evento.c header_files/bst_evento.h
	gcc -c -I./header_files c_files/bst_evento.c -o c_files/bst_evento.o

c_files/conferenza.o: c_files/conferenza.c header_files/conferenza.h
	gcc -c -I./header_files c_files/conferenza.c -o c_files/conferenza.o

utile_test.o: utile_test.c header_files/utile_test.h
	gcc -c -I./header_files utile_test.c

run_test.o: run_test.c header_files/utile_test.h
	gcc -c -I./header_files run_test.c

clean:
	rm -f c_files/*.o *.o run_test.exe
