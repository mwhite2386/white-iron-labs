
#include<stdint.h>

extern uint32_t _estack;

int main();
void Reset_Handler(void);
void NMI_Handler(void);

void (*const vector_table[106])(void) __attribute__((section(".isr_vector"))) = {
    [0] = (void(*)(void))&_estack,
    [1] = Reset_Handler,
    [2] = NMI_Handler
};

void Reset_Handler(void)
{
    main();
}