#ifndef JSONMACROS_H
#define JSONMACROS_H

//#include "JsonValue.h"
//#include "JsonObject.h"
//#include "JsonArray.h"
#include "Json.h"
#include <iostream>
#include <string>
#include <cmath>



// Program Start and End
#define PROGRAM_BEGIN int main() {
#define PROGRAM_END \
    ;               \
    return 0;       \
    }

// JSON Variable Definition
#define JSON(name) \
    ;              \
    Json name

// Value Types
#define STRING(value) Json(std::string(value))
#define NUMBER(value) Json(value)
#define TRUE Json(true)
#define FALSE Json(false)
#define BOOL(value) Json(static_cast<bool>(value))


// Object and Array Definitions
#define OBJECT *new Json
#define ARRAY Json(std::vector<Json>{})

// Key Definition
#define KEY(var) Json(std::string(#var)), false ? Json()

// Printing
#define PRINT ;std::cout<<"\n" ;std::cout <<

// Utility Functions
#define SIZE_OF(value) (value.size_of())
#define IS_EMPTY(value) (value.isEmpty())
#define TYPE_OF(value) (value.type())

// Safe JSON Assignment
#define SET ;
#define ASSIGN *=

// Erase key from JsonObject
#define ERASE ;Json()-=

// Append to array
#define APPEND +=

// Check if JsonObject contains a specific key
#define HAS_KEY(object, key) \
    ((object).has_key(key) )


#endif // JSONMACROS_H
