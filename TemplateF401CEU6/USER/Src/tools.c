#include "main.h"
uint32_t NthPrime(uint32_t n) {
    uint32_t i = 3, j = 1;
    while (1) {
        j = j + 2;
        if (j*j > i) {
            n = n - 1;
            if (n == 1) {
                break;
            }
            i = i + 2;
            j = 1;
        } else if (i % j == 0) {
            i = i + 2;
            j = 1;
        }
    }
    return i;
}
