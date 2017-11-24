#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include"include/parse.h"
#include"include/shell.h"

int main() {
	while (1) {
		char l[50];
		fgets(l, sizeof(l), stdin);
		
		char *s = strip(l);
		if (!s) exit(0);
		
		printf("%s\n", s);
		
		char **args = parse_args(s);
		
		int x = 0;
		for (; *(args+x) != 0; x++) {
			printf("%s\n", *(args+x));
		}
	
		//execvp(args[0], args);
		execute(args);
	}
	
	return 0;
}
