
#include <stdio.h>
#include <stdint.h>

int main()
{

    uint32_t req = 0;

    req |= (1U<<5);
    printf("0x%08x \n", req);

    req |= (1U<<3);
    printf("0x%08x \n", req);

    req &= ~(1U<<5);
    printf("0x%08x \n", req);

    req ^= (1U<<3);
    printf("0x%08x \n", req);

    if ((req & (1U << 3)) != 0) {
        printf("bit 3 is set \n");
    }else
    {
        printf("bit 3 is clear \n");
    }

    req = (req & ~(0x3U << 2)) | (2 << 2);
    printf("0x%08x \n", req);
    return 0;
}