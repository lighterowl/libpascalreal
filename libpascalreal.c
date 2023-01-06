#include "libpascalreal.h"

#include <math.h>
#include <string.h>

#define PREAL_EXP_OFFSET 129
#define PREAL_BYTE_SIZE 6

double libpascalreal_to_double(const uint8_t *real) {
  const unsigned negative = ((real[5] & (1 << 7)) != 0);
  const int exponent = real[0] - PREAL_EXP_OFFSET;
  double rv = 1.0;
  double mant = 0.5;
  for (int i = 5; i >= 1; --i) {
    const uint8_t mant_byte = real[i];
    for (int j = (i == 5) ? 6 : 7; j >= 0; --j) {
      if (mant_byte & (1 << j)) {
        rv += mant;
      }
      mant /= 2;
    }
  }
  rv = ldexp(rv, exponent);
  return negative ? -rv : rv;
}

void libpascalreal_from_double(uint8_t *real, double val) {
  memset(real, 0, PREAL_BYTE_SIZE);
  if (fpclassify(val) != FP_NORMAL) {
    real[5] |= (1 << 7);
    return;
  }

  int exponent;
  double mant = (2 * frexp(fabs(val), &exponent)) - 1;
  exponent += PREAL_EXP_OFFSET - 1;

  const unsigned negative = val < 0;
  if (exponent > UINT8_MAX) {
    memset(real, 0xFF, PREAL_BYTE_SIZE);
    real[5] &= ~(1 << 7);
    real[5] |= (negative << 7);
    return;
  } else if (exponent < 0) {
    real[5] |= (negative << 7);
    return;
  }

  real[0] = exponent;
  real[5] |= (negative << 7);
  double cur_mant = 0.5;
  for (int i = 5; i >= 1; --i) {
    for (int j = (i == 5) ? 6 : 7; j >= 0; --j) {
      if ((mant - cur_mant) >= 0) {
        real[i] |= (1 << j);
        mant -= cur_mant;
      }
      if (mant == 0) {
        return;
      }
      cur_mant /= 2;
    }
  }
}
