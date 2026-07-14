


#include <stdio.h>
#include <stdint.h>

#define GPOIFAKE_BASE (0x40000000U)
#define GPOIFAKE_OFFSET (0x14U + 1)
#define GPOIFAKE_REGISTER (GPOIFAKE_BASE + GPOIFAKE_OFFSET)

int main()
{

    volatile uint32_t* fakeRegister = (volatile uint32_t*)GPOIFAKE_REGISTER;

    printf("gpoifake_offset = %u\n", (GPOIFAKE_OFFSET));
    printf("gpoifake_offset * 2 = %u\n", (GPOIFAKE_OFFSET * 2));

    return 0;
}

