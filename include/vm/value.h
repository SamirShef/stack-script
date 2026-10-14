#pragma once
#include <stddef.h>
#include <stdint.h>

#define val_is_str(val) ((val).kind == VkStr)
#define val_is_real(val) ((val).kind == VkReal)
#define val_is_integer(val) ((val).kind == VkInt)
#define val_is_num(val) ((val_is_real (val)) || (val_is_integer (val)))

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

int
val_add (Value a, Value b, Value *res);

int
val_sub (Value a, Value b, Value *res);

int
val_mul (Value a, Value b, Value *res);

int
val_div (Value a, Value b, Value *res);

int
val_rem (Value a, Value b, Value *res);

int
val_gt (Value a, Value b, Value *res);

int
val_gteq (Value a, Value b, Value *res);

int
val_lt (Value a, Value b, Value *res);

int
val_lteq (Value a, Value b, Value *res);

int
val_eqeq (Value a, Value b, Value *res);

int
val_neq (Value a, Value b, Value *res);

int
val_not (Value a, Value *res);
