#include<stdio.h>

#include"include/parse.h"

int main() {
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
	
	execvp(args[0], args);
	
	
	return 0;
}
