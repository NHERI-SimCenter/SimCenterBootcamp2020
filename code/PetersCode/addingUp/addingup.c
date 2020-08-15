#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    // printf("argc: %d\n",argc);

    int sum=0;

    if (argc > 1) {

	sum = atoi(argv[1]);
	printf("%s",argv[1]);

	for (int i=2; i<argc; i++) {
	    // printf("argv[%d] : %s\n", i, argv[i]);
	    printf(" + %s", argv[i]);
	    sum += atoi(argv[i]);
	}

	printf(" = %d\n",sum);
    }
}
