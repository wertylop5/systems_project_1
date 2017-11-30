#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include"include/parse.h"
#include"include/shell.h"

// doesn't work when i put it in parse.c


int main() {


	// parse_semis(read_line()); // returns array of arguments from input

	//just for testing, will definitely need read_line
	while (1) {
		char * l = read_line();
		//char *l[256];
		//fgets(l, sizeof(l), stdin);
		//l = read_line();
		char *s = strip(l);
		if (!s) continue;

		//printf("%s\n", s);
		char **args = parse_args(s);

		int x = 0;
		for (; *(args+x) != 0; x++) {
			printf("%s\n", *(args+x));
		}

		//execvp(args[0], args);
		if (execute(args)) break;
	}

	return 0;
}
