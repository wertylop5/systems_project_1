shell: main.o
	gcc -o main.o
	make clean

main.o: main.c
	gcc -c main.c

clean:
	rm *.o

run:
	./shell

