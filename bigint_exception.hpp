#ifndef BIG_INT_EXCEPTION_H
#define BIG_INT_EXCEPTION_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <exception>

class BigIntException : public std::exception { 
 public:  
  // Constructor
  BigIntException(const std::string& mensaje) { mensaje_ = mensaje;}

  const char* what() const throw() {
    return mensaje_.c_str();
  }

 private:
 std::string mensaje_;
};

// Clase para manejar la presencia de un dígito no válido en la cadena de inicialización de un objeto BigInt<Base>.
class BigIntBadDigit : public BigIntException {
 public:
  BigIntBadDigit(const std::string& mensaje) : BigIntException(mensaje) {}
};

class BigIntDivisionByZero : public BigIntException {
 public:
  BigIntDivisionByZero(const std::string& mensaje) : BigIntException(mensaje) {}
};

class BigIntBaseNotImplemented : public BigIntException {
 public: 
  BigIntBaseNotImplemented(const std::string& mensaje) : BigIntException(mensaje) {}
};

#endif
