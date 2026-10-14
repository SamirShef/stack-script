#pragma once
#include <stddef.h>
#include <stdint.h>

typedef enum : uint8_t { VkStr, VkReal, VkInt } ValueKind;

typedef struct {
    ValueKind kind;
    union {
        struct {
            char  *data;
            size_t len;
            size_t cap;
        } str;
        double  real;
        int64_t integer;
    } data;
} Value;

Value
val_from_str (char *data, size_t len, size_t cap);

Value
val_from_real (double real);

Value
val_from_integer (int64_t integer);
