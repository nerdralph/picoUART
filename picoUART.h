#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void putx(uint8_t c);
uint8_t purx();

//helper functions
void prints(const char* s);

#ifdef __cplusplus
} // extern "C"
#endif
