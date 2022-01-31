#include <stdio.h>


#include "apple.h"

struct complex_num {
	float real;
	float imaginary;
};

typedef struct complex_num complex_num_t;

int main() {
	char mystring[] = "Guess what I am!?...";
	printf("Hi there...%s",mystring);
	apple();
	return 0;
}

