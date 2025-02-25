#include "JsonMacros.h"
PROGRAM_BEGIN

JSON(will_be_empty_array) = ARRAY[
    STRING("string"), NUMBER(0), FALSE, TRUE, NULL
]
ERASE will_be_empty_array

PRINT will_be_empty_array

JSON(will_be_empty_obj) =OBJECT{
    KEY(one) : NUMBER(1),
    KEY(two) : NUMBER(2),
    KEY(three) : NUMBER(3)
}
ERASE will_be_empty_obj

PRINT will_be_empty_obj

SET will_be_empty_obj["one"] ASSIGN OBJECT{
    KEY(brand) : STRING("realme"),
    KEY(model) : STRING("6")
}
PRINT will_be_empty_obj


PROGRAM_END