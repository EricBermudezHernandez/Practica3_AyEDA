#ifndef CLASES_DERIVADAS_H
#define CLASES_DERIVADAS_H

#include "bigint_exception.hpp"

// Clase para manejar la presencia de un dígito no válido en la cadena de inicialización de un objeto BigInt<Base>.
class BigIntBadDigit : public BigIntException {
 public:
  BigIntBadDigit() : BigIntException() {}
  // ????
};

class BigIntDivisionByZero : public BigIntException {
 public:
  BigIntDivisionByZero() : BigIntException() {}
};

class BigIntBaseNotImplemented : public BigIntException {
 public: 
  BigIntBaseNotImplemented(size_t base) : BigIntException() {
    base_ = base;
  }

  // Hacer método para que el usuario haga algo con la base
 private:
  size_t base_;
};

#endif