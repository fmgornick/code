#include <stdio.h>
#include <string.h>

void do_stuff(void);

int main() {
	do_stuff();
	return 0;
}

void do_stuff(void) {
        char *str1 = "My first string";
        char str2[101];
        strncpy(str2,str1,100);
        printf("Length is %d\n",strlen(str2));
        strcat(str2," ...is cool!");
        printf("New string: %s\n",str2);
}
								

