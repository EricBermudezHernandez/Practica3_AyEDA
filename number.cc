#include "number.hpp"
#include "big_int.hpp"

std::ostream& operator<<(std::ostream& os, const Number& numero) {
    return numero.write(os);
}

std::istream& operator>>(std::istream& is, Number& numero) {
  return numero.read(is);
}

Number* Number::create(size_t base, const std::string& s) {
  switch (base) {
  case 2: {
    return reinterpret_cast<Number*>(new BigInt<2>{s});
    break;
  }
  case 8:
    return reinterpret_cast<Number*>(new BigInt<8>{s});
    break;  

  case 10:
    return reinterpret_cast<Number*>(new BigInt<10>{s});
    break;
  
  case 16:
    return reinterpret_cast<Number*>(new BigInt<16>{s});
    break;

  default:
    throw("La base no está implementada");
    break;
  }
}
