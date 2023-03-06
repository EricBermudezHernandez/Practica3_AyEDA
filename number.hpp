#ifndef NUMBER_H
#define NUMBER_H
#include "big_int.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

template <size_t Base>
class BigInt;

template <>
class BigInt<2>;

class Number {
 public:
  // Constructor por defecto
  Number() = default;
  // Operadores aritméticos
  virtual Number* add(const Number*) const = 0;
  virtual Number* subtract(const Number*) const = 0;
  virtual Number* multiply(const Number*) const = 0;
  virtual Number* divide(const Number*) const = 0;
  virtual Number* module(const Number*) const = 0;
  virtual Number* pow(const Number*) const = 0;
  // Conversores de tipo
  virtual operator BigInt<2>() const = 0;
  virtual operator BigInt<8>() const = 0;
  virtual operator BigInt<10>() const = 0;
  virtual operator BigInt<16>() const = 0;
  // Método para crear
  static Number* create(size_t base, const std::string& s);
 protected:
  // Métodos protegidos para realizar la lectura y escritura de datos de tipo Number
  virtual std::ostream& write(std::ostream&) const = 0;
  virtual std::istream& read(std::istream&) = 0;
  friend std::ostream& operator<<(std::ostream& os, const Number& n);
  friend std::istream& operator>>(std::istream&, Number&);
};

std::ostream& operator<<(std::ostream& os, const Number& numero) {
    return numero.write(os);
}

std::istream& operator>>(std::istream& is, Number& numero) {
  return numero.read(is);
}

Number* Number::create(size_t base, const std::string& s) {
  switch (base) {
  case 2: {
    std::string aux{s};
    return new BigInt<2>{aux};
    break;
  }
    /*
  case 8:
    return new BigInt<8>{s};
    break;  

  case 10:
    return new BigInt<10>{s};
    break;
  
  case 16:
    return new BigInt<16>{s};
    break;
  */
  default:
    throw("La base no está implementada");
    break;
  }
}

#endif
