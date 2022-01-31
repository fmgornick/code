#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
	char *random_string = "Some Random-Length String";
	char *s = (char *)malloc(strlen(random_string)+1);
	strcpy(s,random_string);
	char *t = s;
	while (*t != '\0') { *t = tolower(*t); t++; }
	printf("Started: %s\nFinished: %s\n",random_string,s);
	free(s);
	return 0;
}

