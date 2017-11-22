shell: main.o shell.o
	gcc -o shell main.o
	make clean

main.o: main.c include/shell.h
	gcc -c main.c include/shell.h

shell.o: src/shell.c include/shell.h
	gcc -c src/shell.c include/shell.h

clean:
	rm *.o

run:
	./shell

