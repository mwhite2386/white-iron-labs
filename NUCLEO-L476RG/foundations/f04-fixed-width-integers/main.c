
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int main(){

    int primitiveInt = 0;
    uint32_t unsignedInt32 = 0;
    uint32_t counter = 0;

    counter--;

    printf("Counter = %u\n\n", counter);
    printf("UINT32_MAX = %u\n\n", UINT32_MAX);
    printf("Size of (int) %ld \n\n", sizeof(primitiveInt));
    printf("Size of (uint32_t) %ld \n\n", sizeof(unsignedInt32));


    return 0;
}