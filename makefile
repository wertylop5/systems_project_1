shell: main.o parse.o
	gcc -o shell main.o parse.o
	make clean

main.o: main.c include/parse.h
	gcc -c main.c include/parse.h

parse.o: src/parse.c include/parse.h
	gcc -c src/parse.c include/parse.h

clean:
	rm *.o

run:
	./shell

