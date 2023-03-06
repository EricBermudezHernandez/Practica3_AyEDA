#ifndef CLASES_DERIVADAS_H
#define CLASES_DERIVADAS_H

#include "bigint_exception.hpp"

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
