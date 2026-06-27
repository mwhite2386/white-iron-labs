
#include <stdio.h>
#include <stdint.h>

int main()
{
    uint32_t registerA = 12;
    uint32_t registerB = 10;


    printf("Register A = 0x%x\n", registerA);
    printf("Register B = 0x%x\n", registerB);

    printf("[Operator AND] 0x%x\n", (registerA&registerB));
    printf("[Operator OR] 0x%x\n", (registerA|registerB));
    printf("[Operator XOR] 0x%x\n", (registerA^registerB));

    printf("[Operator NOT] 0x%x\n", ~(registerA));
    printf("[Operator >>] 0x%x\n", (registerA >> 3));
    printf("[Operator <<] 0x%x\n", (registerA << 3));

    return 0;
}