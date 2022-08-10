#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>

uint16_t SCREEN[8192];
uint16_t KEYBOARD = 0;

int main()
{

    uint16_t *p = &SCREEN;

    while (1)
    {
        if (KEYBOARD == 0)
        {
            if ((p - 16384) > 0)
            {
                p = p - 1;
                *p = 0;
            }
        }
        else
        {
            if ((p - 24576) < 0)
            {
                *p = -1;
                p = p + 1;
            }
        }
    }

    exit(EXIT_SUCCESS);
}
