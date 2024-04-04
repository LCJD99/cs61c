#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg) {
    uint8_t flag = (*reg) & 1;
    flag ^= ((*reg) >> 2) & 1;
    flag ^= ((*reg) >> 3) & 1;
    flag ^= ((*reg) >> 5) & 1;
    (*reg) >>= 1;
    uint8_t bit = ((*reg) >> 15) & 1;
    (*reg) ^= ((bit ^ flag) << 15);
}

