#include <stdio.h>

void say_hello(char *name) {
	printf("Hello, %s!\n\n", name);
}

int main(char** args) {
	say_hello("world");
}
