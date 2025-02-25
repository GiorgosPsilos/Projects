#ifndef JSON_H
#define JSON_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <algorithm>


class Json {
public:
    enum ValueType { STRING, NUMBER, BOOLEAN, OBJECT, ARRAY, NULL_TYPE };
    #undef NULL
    #define NULL Json()


    // Constructors
    Json();
    explicit Json(const std::string& str);
    explicit Json(double num);
    explicit Json(int num);
    explicit Json(bool boolean);
    explicit Json(const std::vector<Json> &arr);
    explicit Json(std::initializer_list<Json> init);
    explicit Json(size_t num);

    Json operator[](Json Head);
    //Json operator[](Json *Head) { return *Head; };

    Json operator,(const Json& next) const {
        Json result;
        result.valueType = ARRAY;

        // If the current Json is already an array, merge it
        if (valueType == ARRAY) {
            result.arrayValue = arrayValue;
        } else {
            result.arrayValue.push_back(*this);
        }

        // If the next Json is also an array, merge it
        if (next.valueType == ARRAY) {
            result.arrayValue.insert(result.arrayValue.end(), next.arrayValue.begin(), next.arrayValue.end());
        } else {
            result.arrayValue.push_back(next);
        }

        return result;
    }

    // Type and Utility Functions
    std::string type() const;
    size_t size() const;
    bool isEmpty() const;

    //Assign Overload
    Json operator*=(const Json &other);

    // Arithmetic Operators
    Json operator+(const Json& other) const;
    Json operator-(const Json& other) const;
    Json operator*(const Json& other) const;
    Json operator/(const Json &other) const;
    Json operator%(const Json &other) const;

    //bigger,lower etc
    Json operator>(const Json& other) const;
    Json operator<(const Json& other) const;
    Json operator>=(const Json& other) const;
    Json operator<=(const Json &other) const;

    // Logical Operators
    Json operator&&(const Json& other) const;
    Json operator||(const Json& other) const;
    Json operator!() const;

    // Comparison Operators
    Json operator==(const Json& other) const;
    Json operator!=(const Json& other) const;

    // Accessors for Object and Array
    Json& operator[](const std::string& key);
    const Json& operator[](const std::string& key) const;

    Json& operator[](size_t index);
    const Json& operator[](size_t index) const;

    // Erase
    Json &operator-=( Json &other) const;
    // Append operator
    Json operator+=(const Json& other);

    //sizeof
    Json size_of() const;
    //is_empty
    Json is_empty() const;
    //has_key
    Json has_key(const std::string key) const;
    //type_of
    Json type_of() const;

    // Print Function
    void print() const;
    friend std::ostream &operator<<(std::ostream &os, const Json &j);

  private:
    ValueType valueType;
    std::string stringValue;
    double numberValue;
    bool boolValue;
    std::unordered_map<std::string, Json> objectValue;
    std::vector<Json> arrayValue;
};

#endif // JSON_H
