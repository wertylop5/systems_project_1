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
		int num_args = semis(l);
		//char *l[256];
		//fgets(l, sizeof(l), stdin);
		//l = read_line();
		char *s = strip(l);
		if (!s) continue;

		//printf("%s\n", s);
		// loop through parse semis: for every arg run parse_args and execute
		char **args = parse_semis(s);

		int x = 0;
		for (; x < num_args; x++) {
			//parse_args(args[x]);
			//printf("executed command: \n");
			if (execute( parse_args(args[x]) )) break;
		}
			//printf("%s\n", *(args+x));
		}

		//execvp(args[0], args);
		//if (execute(args)) break;
	//}

	return 0;
}
