#include <stdint.h>

#include "s21_string.h"

#define INTEGER_PART(mantisa) ((mantisa)&0x8000000000000000L)
#define FRACTION_PART(mantisa) ((mantisa)&0x7FFFFFFFFFFFFFFFL)

#define SIGN_BIT_OFFSET 15
#define EXP_BITS 0x7FFF
#define EXP_OFFSET 16383
#define MANTISA_FRACTION_OFFSET 63
#define INT_PART_BUFFER_SIZE 8 * 1024
#define FRACT_PART_BUFFER_SIZE 16447 /* EXP_OFFSET + 64 */
#define TWO_DEGREE_TWENTY 1048576L
#define BIGINTEGER_SIZE 600
#define BIGINTEGER_BASE 1000000000L
#define BIGINTEGER_DIGIT_LENGTH 9

#define RESET_MANTISA_INTEGER_BITS(mant, exp) \
  if (0 <= (exp)) {                           \
    (mant) <<= 1 + (exp);                     \
    (mant) >>= 1 + (exp);                     \
  }

#define FILL_FRACTION_BUFFER_WITH_BITS(buf, mant, exp)           \
  for (int i = MANTISA_FRACTION_OFFSET - (exp)-1; i >= 0; --i) { \
    (buf)[i] = (mant)&0x1;                                       \
    (mant) >>= 1;                                                \
  }

#define FILL_FRACTION_BUFFER_WITH_DIGITS(buf, exp, carry)          \
  for (int i = MANTISA_FRACTION_OFFSET - (exp)-1; i >= 0; --i) {   \
    for (int j = MANTISA_FRACTION_OFFSET - (exp)-1; j >= i; --j) { \
      (buf)[j] *= 5;                                               \
    }                                                              \
    for (int j = MANTISA_FRACTION_OFFSET - (exp)-1; j > 0; --j) {  \
      (carry) = (buf)[j] / 10;                                     \
      (buf)[j] %= 10;                                              \
      (buf)[j - 1] += (carry);                                     \
    }                                                              \
  }

#define ROUND_FRACTION_BUFFER(buf, exp, precision, carry) \
  (carry) = 0;                                            \
  if ((precision) < MANTISA_FRACTION_OFFSET - (exp)) {    \
    (carry) = (buf)[(precision)] / 5;                     \
    for (int i = (precision)-1; i >= 0; --i) {            \
      (buf)[i] += (carry);                                \
      (carry) = (buf)[i] / 10;                            \
      (buf)[i] %= 10;                                     \
    }                                                     \
  }

#define FRACTION_BUFFER_TO_ASCII(buf, exp, precision, carry)     \
  for (int i = MANTISA_FRACTION_OFFSET - (exp)-1; i >= 0; --i) { \
    (buf)[i] += '0';                                             \
  }                                                              \
  if ((carry)) {                                                 \
    (buf)[0] = '\0';                                             \
  } else if ((precision) < MANTISA_FRACTION_OFFSET - (exp)) {    \
    (buf)[(precision)] = '\0';                                   \
  } else {                                                       \
    (buf)[MANTISA_FRACTION_OFFSET - (exp)] = '\0';               \
  }

#define ADD_CARRY_TO_INTEGER_PART(num, p, sign, mantisa) \
  if ((sign)) {                                          \
    (num) -= 1.0L;                                       \
  } else {                                               \
    (num) += 1.0L;                                       \
  }                                                      \
  (p) = (uint64_t *)(void *)&(num);                      \
  (mantisa) = *p++;                                      \
  exp = (int)((*p) & EXP_BITS) - EXP_OFFSET;

#define DEGREE_OF_TWO(n, exp) \
  (n) = 1;                    \
  while ((exp)-- > 0) (n) *= 2;

#define INIT_BIGINTEGER(bi, mant)             \
  (bi)[0] = (mant) % BIGINTEGER_BASE;         \
  (bi)[1] = (mant) / BIGINTEGER_BASE;         \
  for (int i = 2; i < BIGINTEGER_SIZE; ++i) { \
    (bi)[i] = 0;                              \
  }

#define BIGINTEGER_MULTI_INT(bi, n)                  \
  for (int i = 0, x = 0; i < BIGINTEGER_SIZE; ++i) { \
    (bi)[i] *= (n);                                  \
    (bi)[i] += x;                                    \
    x = (bi)[i] / BIGINTEGER_BASE;                   \
    (bi)[i] %= BIGINTEGER_BASE;                      \
  }

#define BIGINTEGER_DIGIT_TO_ASCII(bid, buf)                \
  for (int i = BIGINTEGER_DIGIT_LENGTH - 1; i >= 0; --i) { \
    (buf)[i] = ((bid) % 10) + '0';                         \
    (bid) /= 10;                                           \
  }

#define BIGINTEGER_TO_ASCII(bi, buf)                                      \
  uint64_t *biptr = (bi) + BIGINTEGER_SIZE;                               \
  char *intpart_ptr = (buf);                                              \
  while (*--biptr == 0)                                                   \
    ;                                                                     \
  intpart_ptr += s21_ullitoa_base(*biptr, 10, "0123456789", intpart_ptr); \
  while (--biptr >= (bi)) {                                               \
    BIGINTEGER_DIGIT_TO_ASCII(*biptr, intpart_ptr);                       \
    intpart_ptr += BIGINTEGER_DIGIT_LENGTH;                               \
  }                                                                       \
  *intpart_ptr = '\0';

static char fraction_part[FRACT_PART_BUFFER_SIZE];
static char integer_part[INT_PART_BUFFER_SIZE];

int s21_ldtoa(long double num, int precision, char **intpart,
              char **fractpart) {
  int carry;
  int exp;
  int sign;
  uint64_t mantisa;
  uint64_t mant;
  uint64_t *p;

  p = (uint64_t *)(void *)&num;
  mantisa = *p++;
  sign = (int)((*p >> SIGN_BIT_OFFSET) & 0x1);
  exp = (int)((*p) & EXP_BITS);

  if (num != num) {
    s21_strcpy(integer_part, "nan");
    *intpart = integer_part;
    *fractpart = NULL;
  } else if (exp == 0x7FFF) {
    s21_strcpy(integer_part, "inf");
    *intpart = integer_part;
    *fractpart = NULL;
  } else if (exp == 0) {
    s21_strcpy(integer_part, "0");
    *fraction_part = '\0';
    *intpart = integer_part;
    *fractpart = fraction_part;
  } else {
    exp -= EXP_OFFSET;
    mant = mantisa;
    /* fraction part */
    if (exp >= MANTISA_FRACTION_OFFSET) {
      fraction_part[0] = '\0';
    } else {
      RESET_MANTISA_INTEGER_BITS(mant, exp);
      FILL_FRACTION_BUFFER_WITH_BITS(fraction_part, mant, exp);
      FILL_FRACTION_BUFFER_WITH_DIGITS(fraction_part, exp, carry);
      ROUND_FRACTION_BUFFER(fraction_part, exp, precision, carry);
      FRACTION_BUFFER_TO_ASCII(fraction_part, exp, precision, carry);
      if (carry) {
        ADD_CARRY_TO_INTEGER_PART(num, p, sign, mantisa);
      }
    }
    /* integer part */
    mant = mantisa;
    if (exp < 0) {
      s21_strcpy(integer_part, "0");
    } else if (exp <= 63) {
      mant >>= 63 - exp;
      s21_ullitoa_base(mant, 10, "0123456789", integer_part);
    } else {
      exp -= 63;
      uint64_t bi[BIGINTEGER_SIZE];
      INIT_BIGINTEGER(bi, mant);
      while (exp >= 20) {
        BIGINTEGER_MULTI_INT(bi, TWO_DEGREE_TWENTY);
        exp -= 20;
      }
      if (exp) {
        int n;
        DEGREE_OF_TWO(n, exp);
        BIGINTEGER_MULTI_INT(bi, n);
      }
      BIGINTEGER_TO_ASCII(bi, integer_part);
    }
    *intpart = integer_part;
    *fractpart = fraction_part;
  }
  return (sign);
}

int s21_ldtoa_exponential(long double num, int precision, char **numstr,
                          char **expstr, char expchar) {
  int exp;
  int exp10 = 0;
  int sign;
  uint64_t *p;

  p = (uint64_t *)(void *)&num;
  p++;
  sign = (int)((*p >> SIGN_BIT_OFFSET) & 0x1);
  exp = (int)((*p) & EXP_BITS);

  if (num != num) {
    const char *nanstr = expchar == 'e' ? "nan" : "NAN";
    s21_strcpy(integer_part, nanstr);
    *numstr = integer_part;
    *expstr = NULL;
  } else if (exp == 0x7FFF) {
    const char *infstr = expchar == 'e' ? "inf" : "INF";
    s21_strcpy(integer_part, infstr);
    *numstr = integer_part;
    *expstr = NULL;
  } else if (exp == 0) {
    s21_strcpy(integer_part, "0.");
    *fraction_part = '\0';
    *numstr = integer_part;
    fraction_part[0] = expchar;
    s21_strcpy(fraction_part + 1, "+00");
    *expstr = fraction_part;
  } else {
    char *intptr, *fractptr;
    s21_ldtoa(num, FRACT_PART_BUFFER_SIZE - 1, &intptr, &fractptr);
    if (*intptr != '0') {
      s21_memmove(intptr + 2, intptr, s21_strlen(intptr) + 1);
      *intptr = '\0';
      intptr[1] = intptr[2];
      intptr[2] = '.';
      exp10 = s21_strlen(intptr + 3);
      int n = precision - exp10 + 1;
      int fplen = (int)s21_strlen(fractptr);
      n = n < fplen ? n : fplen;
      int bufrem = INT_PART_BUFFER_SIZE - exp10 - 5;
      n = n > bufrem ? bufrem : n;
      n = n < 0 ? 0 : n;
      fractptr[n] = '\0';
      s21_strcat(intptr + 1 + 1 + exp10, fractptr);
    } else {
      exp10 = -1;
      while (*fractptr && *fractptr == '0') {
        ++fractptr;
        --exp10;
      }
      if (!*fractptr) {
        s21_strcpy(intptr, "0.");
      } else {
        int n = s21_strlen(fractptr);
        n = precision < n ? precision + 1 : n;
        s21_memcpy(intptr + 2, fractptr, n + 1);
        *intptr = '\0';
        intptr[1] = intptr[2];
        intptr[2] = '.';
      }
    }
    intptr++;
    fractptr = intptr + 2;
    if (precision >= 0 && precision < (int)s21_strlen(fractptr)) {
      int carry = fractptr[precision] - '0' >= 5;
      fractptr[precision] = '\0';
      while (carry && --precision >= 0) {
        fractptr[precision] -= '0';
        fractptr[precision] += carry;
        carry = fractptr[precision] / 10;
        fractptr[precision] %= 10;
        fractptr[precision] += '0';
      }
      if (carry) {
        *intptr = *intptr - '0' + carry;
        carry = *intptr / 10;
        *intptr = (*intptr % 10) + '0';
        if (carry) {
          *--intptr = '1';
          intptr[2] = '\0';
          intptr[1] = '.';
          ++exp10;
        }
      }
    }
    *numstr = intptr;
    char *expbuf = fraction_part;
    expbuf[0] = expchar;
    if (exp10 < 0) {
      expbuf[1] = '-';
      exp10 = -exp10;
    } else {
      expbuf[1] = '+';
    }
    if (exp10 / 10 == 0) {
      expbuf[2] = '0';
      s21_itoa(exp10, expbuf + 3);
    } else {
      s21_itoa(exp10, expbuf + 2);
    }
    *expstr = expbuf;
  }

  return (sign);
}
