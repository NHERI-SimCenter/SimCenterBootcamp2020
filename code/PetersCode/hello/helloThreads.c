#include "omp.h"
#include <stdio.h>

int main(int argc, char **argv) {

#pragma omp parallel
    
    {
    int ID=omp_get_thread_num();

    printf("Hello, (%d) ", ID);
    printf("World! (%d)\n", ID);

    }

    return 0;
}
