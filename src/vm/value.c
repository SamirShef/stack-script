#include "vm/value.h"

Value
val_from_str (char *data, size_t len, size_t cap) {
    return (Value){
        .kind     = VkStr,
        .data.str = { data, len, cap }
    };
}

Value
val_from_real (double real) {
    return (Value){ .kind = VkReal, .data.real = real };
}

Value
val_from_integer (int64_t integer) {
    return (Value){ .kind = VkInt, .data.integer = integer };
}
