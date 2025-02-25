#include "Json.h"

// Constructors
Json::Json() : valueType(NULL_TYPE) {}
Json::Json(const std::string &str) : valueType(STRING), stringValue(str) {}
Json::Json(double num) : valueType(NUMBER), numberValue(num) {}
Json::Json(size_t num) : valueType(NUMBER), numberValue(num) {}

Json::Json(int num) : valueType(NUMBER), numberValue(num) {}
Json::Json(bool boolean) : valueType(BOOLEAN), boolValue(boolean) {}
// Json::Json(const std::initializer_list<std::pair<const std::string, Json>>&
// obj) : valueType(OBJECT), objectValue(obj) {}
Json::Json(const std::vector<Json> &arr) : valueType(ARRAY), arrayValue(arr) {}
Json::Json(std::initializer_list<Json> init) : valueType(OBJECT) {
  std::vector<Json> JsonVector(init);
  Json temp;
  for (size_t i = 0; i + 1 < JsonVector.size(); i += 2) {
    if (JsonVector[i].valueType != Json::STRING) {
      throw std::invalid_argument("Keys in an object must be strings");
    }
    temp.objectValue.emplace(JsonVector[i].stringValue, JsonVector[i + 1]);

    // temp.emplace_back(std::get<std::string>(JsonVector[i].value),
    // JsonVector[i + 1]);
  }
  objectValue = temp.objectValue;
}
// Type and Utility Functions
std::string Json::type() const {
  switch (valueType) {
  case STRING:
    return "string";
  case NUMBER:
    return "number";
  case BOOLEAN:
    return "boolean";
  case OBJECT:
    return "object";
  case ARRAY:
    return "array";
  case NULL_TYPE:
    return "null";
  }
  return "unknown";
}

Json Json::operator[](Json Head) {
    if (Head.valueType == ARRAY) {
        return Head;
    }
    else
    {
        valueType = ARRAY;
        arrayValue.push_back(Head);
        return *this;
    }
};

size_t Json::size() const {
  if (valueType == OBJECT)
    return objectValue.size();
  if (valueType == ARRAY)
    return arrayValue.size();
  return 1;
}

bool Json::isEmpty() const {
  if (valueType == OBJECT)
    return objectValue.empty();
  if (valueType == ARRAY)
    return arrayValue.empty();
  return false;
}

// Arithmetic Operators
Json Json::operator+(const Json &other) const {
  if (valueType == NUMBER && other.valueType == NUMBER)
    return Json(numberValue + other.numberValue);
  if (valueType == STRING && other.valueType == STRING)
    return Json(stringValue + other.stringValue);
  throw std::runtime_error("Invalid types for + operator");
}

Json Json::operator-(const Json &other) const {
  if (valueType == NUMBER && other.valueType == NUMBER)
    return Json(numberValue - other.numberValue);
  throw std::runtime_error("Invalid types for - operator");
}

Json Json::operator*(const Json &other) const {
  if (valueType == NUMBER && other.valueType == NUMBER)
    return Json(numberValue * other.numberValue);
  throw std::runtime_error("Invalid types for * operator");
}

Json Json::operator/(const Json &other) const {
  if (valueType == NUMBER && other.valueType == NUMBER)
    return Json(numberValue / other.numberValue);
  throw std::runtime_error("Invalid types for / operator");
}

 Json Json::operator%(const Json &other) const {
   if (valueType == NUMBER && other.valueType == NUMBER)
     return Json(std::fmod(numberValue , other.numberValue));
   throw std::runtime_error("Invalid types for % operator");
 }

//bigger,lower etc
Json Json::operator>(const Json &other) const {
  if (valueType == NUMBER && other.valueType == NUMBER)
    return Json(numberValue > other.numberValue);
  throw std::runtime_error("Invalid types for > operator");
}

Json Json::operator<(const Json &other) const {
  if (valueType == NUMBER && other.valueType == NUMBER)
    return Json(numberValue < other.numberValue);
  throw std::runtime_error("Invalid types for < operator");
}

Json Json::operator>=(const Json &other) const {
  if (valueType == NUMBER && other.valueType == NUMBER)
    return Json(numberValue >= other.numberValue);
  throw std::runtime_error("Invalid types for >= operator");
}

 Json Json::operator<=(const Json &other) const {
   if (valueType == NUMBER && other.valueType == NUMBER)
    return Json(numberValue <= other.numberValue);
  throw std::runtime_error("Invalid types for >= operator");
 }


// Logical Operators
Json Json::operator&&(const Json &other) const {
  if (valueType == BOOLEAN && other.valueType == BOOLEAN)
    return Json(boolValue && other.boolValue);
  throw std::runtime_error("Invalid types for && operator");
}

Json Json::operator||(const Json &other) const {
  if (valueType == BOOLEAN && other.valueType == BOOLEAN)
    return Json(boolValue || other.boolValue);
  throw std::runtime_error("Invalid types for || operator");
}

Json Json::operator!() const {
  if (valueType == BOOLEAN)
    return Json(!boolValue);
  throw std::runtime_error("Invalid type for ! operator");
}

// Comparison Operators
Json Json::operator==(const Json &other) const {
  if (valueType != other.valueType)
    return Json(true);
  switch (valueType) {
  case STRING:
    return Json(stringValue == other.stringValue);
  case NUMBER:
    return Json(numberValue == other.numberValue);
  case BOOLEAN:
    return Json(boolValue == other.boolValue);
	//case OBJECT:                                        // Gia Object kai Array eimai ili8ios oti den douleuei swsta
  //  return Json(objectValue == other.objectValue);
  //case ARRAY:
  //  return Json(arrayValue == other.arrayValue);
  case NULL_TYPE:
    return Json(true);
  }
  return Json(false);
}

Json Json::operator!=(const Json &other) const { return Json(!(*this == other)); }

// Accessors for Object and Array
Json &Json::operator[](const std::string &key) {
    if (valueType == NULL_TYPE)
    {
		auto& obj = objectValue;
		obj.emplace(key, Json());
        return obj[key];
    }
  if (valueType != OBJECT)
    throw std::runtime_error("Not an object1");
  return objectValue[key];
}

const Json &Json::operator[](const std::string &key) const {
  if (valueType != OBJECT)
    throw std::runtime_error("Not an object2");
  auto it = objectValue.find(key);
  if (it == objectValue.end())
    throw std::runtime_error("Key not found");
  return it->second;
}

Json &Json::operator[](const size_t index) {
  if (valueType != ARRAY)
    throw std::runtime_error("Not an array");
  return arrayValue.at(index);
}

const Json &Json::operator[](const size_t index) const {
  if (valueType != ARRAY)
    throw std::runtime_error("Not an array");
  return arrayValue.at(index);
}

Json &Json::operator-=(Json &other) const {
  if (other.valueType == OBJECT) {
    other.objectValue.clear();
    other.valueType = NULL_TYPE;
  } else if (other.valueType == ARRAY) {
    other.arrayValue.clear();
    other.valueType = NULL_TYPE;
  } else {
    other.valueType = NULL_TYPE;
  }
  return other;
}

// Print Function
void Json::print() const {
  switch (valueType) {
  case STRING:
    std::cout << "\"" << stringValue << "\"";
    break;
  case NUMBER:
    std::cout << numberValue;
    break;
  case BOOLEAN:
    std::cout << (boolValue ? "true" : "false");
    break;
  case OBJECT:
    std::cout << "{ ";
    for (auto it = objectValue.begin(); it != objectValue.end(); ++it) {
      std::cout << "\"" << it->first << "\": ";
      it->second.print();
      if (std::next(it) != objectValue.end())
        std::cout << ", ";
    }
    std::cout << " }";
    break;
  case ARRAY:
    std::cout << "[ ";
    for (size_t i = 0; i < arrayValue.size(); ++i) {
      arrayValue[i].print();
      if (i < arrayValue.size() - 1)
        std::cout << ", ";
    }
    std::cout << " ]";
    break;
  case NULL_TYPE:
    std::cout << "null";
    break;
  }
}
std::ostream &operator<<(std::ostream &os, const Json &json) {
  switch (json.valueType) {
  case Json::ValueType::STRING:
    os << "\"" << json.stringValue << "\"";
    break;
  case Json::ValueType::NUMBER:
    os << json.numberValue;
    break;
  case Json::ValueType::BOOLEAN:
    os << (json.boolValue ? "true" : "false");
    break;
  case Json::ValueType::OBJECT:
    os << "{ ";
    for (auto it = json.objectValue.begin(); it != json.objectValue.end();
         ++it) {
      os << "\"" << it->first << "\": " << it->second;
      if (std::next(it) != json.objectValue.end())
        os << ", ";
    }
    os << " }";
    break;
  case Json::ValueType::ARRAY:
    os << "[ ";
    for (size_t i = 0; i < json.arrayValue.size(); ++i) {
      os << json.arrayValue[i];
      if (i < json.arrayValue.size() - 1)
        os << ", ";
    }
    os << " ]";
    break;
  case Json::ValueType::NULL_TYPE:
    os << "null";
    break;
  }
  os << std::endl;
  return os;
}

Json Json::operator*=(const Json &other) {
  *this = other;
  return *this;
}
// Append
Json Json::operator+=(const Json &other) {
  if (valueType != ARRAY)
    throw std::runtime_error("Not an array");
  arrayValue.push_back(other);
  return *this;
}

//sizeof
Json Json::size_of()const{
   std::size_t count;
  if(valueType==ARRAY){
     count= count_if(arrayValue.begin(), arrayValue.end(),[](const auto &element) {
                        return element.valueType != NULL_TYPE;
                    });
  }
  else if(valueType==OBJECT){
     count= count_if(objectValue.begin(), objectValue.end(),[](const auto &pair) {
                        return pair.second.valueType != NULL_TYPE;
                    });
  }else{
     count = 1;

  }
  return Json(count);
};

//is_empty
Json Json::is_empty()const{
   
   std::size_t count;
  if(valueType==ARRAY){
     count= count_if(arrayValue.begin(), arrayValue.end(),[](const auto &element) {
                        return element.valueType != NULL_TYPE;
                    });
  }
  else if(valueType==OBJECT){
     count= count_if(objectValue.begin(), objectValue.end(),[](const auto &pair) {
                        return pair.second.valueType != NULL_TYPE;
                    });
  }else{
     count = 1;

  }
  return Json(count==0);
};

//has_key

Json Json::has_key(const std::string key)const {
   if (valueType == OBJECT)
    {
		auto& obj = objectValue;
		for (auto &[k, val]: obj) {
                if (k == key && val.valueType !=NULL_TYPE) {
                    return Json(true);
                }
            }
    }
  return Json(false);
}

//type_of
Json Json::type_of()const {
  switch (valueType) {
            case NUMBER:
                return Json(std::string("Number"));
            case STRING:
                return Json(std::string("String"));
            case ARRAY:
                return Json(std::string("Array"));
            case OBJECT:
                return Json(std::string("Object"));
            case BOOLEAN:
                return Json(std::string("Boolean"));
            default:
                return Json(std::string("Null"));
        }
}