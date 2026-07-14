

#include <stdio.h>
#include <stdint.h>

int main()
{
    int x = 5;

    printf("[initial] int x = %d \n", x);
    int *p = &x;
    *p = 10;

    printf("[changed] int x = %d \n", x);


    volatile uint32_t* gpioA = (volatile uint32_t*)0x48000000U;
    printf("%u\n", *gpioA);








}