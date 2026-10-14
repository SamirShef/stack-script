#include "vm/value.h"

#include <math.h>

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

int
val_add (Value a, Value b, Value *res) {
    if (val_is_num (a) && val_is_num (b)) {
        if (val_is_real (a) && val_is_integer (b)) {
            *res = (Value){ .kind      = VkReal,
                            .data.real = a.data.real + (double) b.data.integer };
        } else if (val_is_real (a) && val_is_real (b)) {
            *res = (Value){ .kind = VkReal, .data.real = a.data.real + b.data.real };
        } else if (val_is_integer (a) && val_is_real (b)) {
            *res = (Value){ .kind      = VkReal,
                            .data.real = (double) a.data.integer + b.data.real };
        } else {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = a.data.integer + b.data.integer };
        }
        return 1;
    }
    return 0;
}

int
val_sub (Value a, Value b, Value *res) {
    if (val_is_num (a) && val_is_num (b)) {
        if (val_is_real (a) && val_is_integer (b)) {
            *res = (Value){ .kind      = VkReal,
                            .data.real = a.data.real - (double) b.data.integer };
        } else if (val_is_real (a) && val_is_real (b)) {
            *res = (Value){ .kind = VkReal, .data.real = a.data.real - b.data.real };
        } else if (val_is_integer (a) && val_is_real (b)) {
            *res = (Value){ .kind      = VkReal,
                            .data.real = (double) a.data.integer - b.data.real };
        } else {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = a.data.integer - b.data.integer };
        }
        return 1;
    }
    return 0;
}

int
val_mul (Value a, Value b, Value *res) {
    if (val_is_num (a) && val_is_num (b)) {
        if (val_is_real (a) && val_is_integer (b)) {
            *res = (Value){ .kind      = VkReal,
                            .data.real = a.data.real * (double) b.data.integer };
        } else if (val_is_real (a) && val_is_real (b)) {
            *res = (Value){ .kind = VkReal, .data.real = a.data.real * b.data.real };
        } else if (val_is_integer (a) && val_is_real (b)) {
            *res = (Value){ .kind      = VkReal,
                            .data.real = (double) a.data.integer * b.data.real };
        } else {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = a.data.integer * b.data.integer };
        }
        return 1;
    }
    return 0;
}

int
val_div (Value a, Value b, Value *res) {
    if (val_is_num (a) && val_is_num (b)) {
        if (val_is_real (a) && val_is_integer (b)) {
            *res = (Value){ .kind      = VkReal,
                            .data.real = a.data.real / (double) b.data.integer };
        } else if (val_is_real (a) && val_is_real (b)) {
            *res = (Value){ .kind = VkReal, .data.real = a.data.real / b.data.real };
        } else if (val_is_integer (a) && val_is_real (b)) {
            *res = (Value){ .kind      = VkReal,
                            .data.real = (double) a.data.integer / b.data.real };
        } else {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = a.data.integer / b.data.integer };
        }
        return 1;
    }
    return 0;
}

int
val_rem (Value a, Value b, Value *res) {
    if (val_is_num (a) && val_is_num (b)) {
        if (val_is_real (a) && val_is_integer (b)) {
            *res = (Value){ .kind      = VkReal,
                            .data.real = fmod (a.data.real, (double) b.data.integer) };
        } else if (val_is_real (a) && val_is_real (b)) {
            *res
                = (Value){ .kind = VkReal, .data.real = fmod (a.data.real, b.data.real) };
        } else if (val_is_integer (a) && val_is_real (b)) {
            *res = (Value){ .kind      = VkReal,
                            .data.real = fmod ((double) a.data.integer, b.data.real) };
        } else {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = a.data.integer % b.data.integer };
        }
        return 1;
    }
    return 0;
}

int
val_gt (Value a, Value b, Value *res) {
    if (val_is_num (a) && val_is_num (b)) {
        if (val_is_real (a) && val_is_integer (b)) {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = a.data.real > (double) b.data.integer };
        } else if (val_is_real (a) && val_is_real (b)) {
            *res = (Value){ .kind = VkInt, .data.integer = a.data.real > b.data.real };
        } else if (val_is_integer (a) && val_is_real (b)) {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = (double) a.data.integer > b.data.real };
        } else {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = a.data.integer > b.data.integer };
        }
        return 1;
    }
    return 0;
}

int
val_gteq (Value a, Value b, Value *res) {
    if (val_is_num (a) && val_is_num (b)) {
        if (val_is_real (a) && val_is_integer (b)) {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = a.data.real >= (double) b.data.integer };
        } else if (val_is_real (a) && val_is_real (b)) {
            *res = (Value){ .kind = VkInt, .data.integer = a.data.real >= b.data.real };
        } else if (val_is_integer (a) && val_is_real (b)) {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = (double) a.data.integer >= b.data.real };
        } else {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = a.data.integer >= b.data.integer };
        }
        return 1;
    }
    return 0;
}

int
val_lt (Value a, Value b, Value *res) {
    if (val_is_num (a) && val_is_num (b)) {
        if (val_is_real (a) && val_is_integer (b)) {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = a.data.real < (double) b.data.integer };
        } else if (val_is_real (a) && val_is_real (b)) {
            *res = (Value){ .kind = VkInt, .data.integer = a.data.real < b.data.real };
        } else if (val_is_integer (a) && val_is_real (b)) {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = (double) a.data.integer < b.data.real };
        } else {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = a.data.integer < b.data.integer };
        }
        return 1;
    }
    return 0;
}

int
val_lteq (Value a, Value b, Value *res) {
    if (val_is_num (a) && val_is_num (b)) {
        if (val_is_real (a) && val_is_integer (b)) {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = a.data.real <= (double) b.data.integer };
        } else if (val_is_real (a) && val_is_real (b)) {
            *res = (Value){ .kind = VkInt, .data.integer = a.data.real <= b.data.real };
        } else if (val_is_integer (a) && val_is_real (b)) {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = (double) a.data.integer <= b.data.real };
        } else {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = a.data.integer <= b.data.integer };
        }
        return 1;
    }
    return 0;
}

int
val_eqeq (Value a, Value b, Value *res) {
    if (val_is_num (a) && val_is_num (b)) {
        if (val_is_real (a) && val_is_integer (b)) {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = a.data.real == (double) b.data.integer };
        } else if (val_is_real (a) && val_is_real (b)) {
            *res = (Value){ .kind = VkInt, .data.integer = a.data.real == b.data.real };
        } else if (val_is_integer (a) && val_is_real (b)) {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = (double) a.data.integer == b.data.real };
        } else {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = a.data.integer == b.data.integer };
        }
        return 1;
    }
    return 0;
}

int
val_neq (Value a, Value b, Value *res) {
    if (val_is_num (a) && val_is_num (b)) {
        if (val_is_real (a) && val_is_integer (b)) {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = a.data.real != (double) b.data.integer };
        } else if (val_is_real (a) && val_is_real (b)) {
            *res = (Value){ .kind = VkInt, .data.integer = a.data.real != b.data.real };
        } else if (val_is_integer (a) && val_is_real (b)) {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = (double) a.data.integer != b.data.real };
        } else {
            *res = (Value){ .kind         = VkInt,
                            .data.integer = a.data.integer != b.data.integer };
        }
        return 1;
    }
    return 0;
}

int
val_not (Value a, Value *res) {
    if (val_is_num (a)) {
        if (val_is_real (a)) {
            *res = (Value){ .kind = VkInt, .data.integer = a.data.real == 0 };
        } else {
            *res = (Value){ .kind = VkInt, .data.integer = !a.data.integer };
        }
        return 1;
    }
    return 0;
}
