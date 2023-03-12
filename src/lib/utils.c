#include "../s21_decimal.h"

int get_bit(int val, int index) {
    return (val & (1 << index)) ? 1 : 0;
}

void set_bit(int *val, int index, int bit) {
    if (bit == 1) {
        (*val) |= 1 << index;
    } else {
        (*val) &= ~(1 << index);
    }
}

int get_sign(const s21_decimal* val) {
    return (val->bits[3] & (1 << SIGN_BIT)) ? NEGATIVE : POSITIVE;
}

void set_sign(s21_decimal* val, int sign) {
    set_bit(&val->bits[3], SIGN_BIT, sign);
}

int get_exponent(const s21_decimal* val) {
    return (val->bits[3] & EXPONENT_MASK) >> 16;
}

void set_exponent(s21_decimal* val, int exp) {
    for (int i = 0; i < 8 && exp > 0; ++i) {
        set_bit(&val->bits[3], 16 + i, exp % 2);
        exp /= 2;
    }
}
