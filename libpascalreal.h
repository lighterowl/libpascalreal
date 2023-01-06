#ifndef LIBPASCALREAL_H
#define LIBPASCALREAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

double libpascalreal_to_double(const uint8_t*);

void libpascalreal_from_double(uint8_t*, double);

#ifdef __cplusplus
}
#endif

#endif
