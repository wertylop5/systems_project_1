shell: main.o parse.o shell.o
	gcc -o shell main.o parse.o shell.o
	make clean

main.o: main.c include/parse.h include/shell.h
	gcc -c main.c include/parse.h

parse.o: src/parse.c include/parse.h
	gcc -c src/parse.c include/parse.h

shell.o: src/shell.c include/shell.h
	gcc -c src/shell.c include/shell.h

clean:
	rm *.o

run:
	./shell

