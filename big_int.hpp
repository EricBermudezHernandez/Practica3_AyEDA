#ifndef BIG_INT_H
#define BIG_INT_H
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "bigint_exceptions.hpp"
#include "number.hpp"

class Number;

// Plantilla clase BigInt
template <size_t Base>
class BigInt : public Number {
 public:
  // Constructores
  BigInt(long long n = 0);
  BigInt(const std::string&);
  BigInt(const char*);
  BigInt(const BigInt<Base>&);  // Constructor de copia

  // Acceso:
  int sign() const { return signo_; }   // Signo: 1 o -1
  char operator[](int posicion) const;  // Acceso al i-ésimo dígito
  // Operadores:
  BigInt<Base>& operator=(const BigInt<Base>&);
  // Inserción / Extracción

  // BORRAR LOS DOS MÉTODOS E IMPLEMENTAR SU CÓDIGO EN EL READ/WRITE
  template <size_t Bass>
  friend std::ostream& operator<<(std::ostream&, const BigInt<Bass>&);
  template <size_t Bass>
  friend std::istream& operator>>(std::istream&, BigInt<Bass>&);

  // Operadores de comparación
  template <size_t Bass>
  friend bool operator==(const BigInt<Bass>& numero1,
                         const BigInt<Bass>& numero2);
  bool operator!=(const BigInt<Base>&) const;
  template <size_t Bass>
  friend bool operator>(const BigInt<Bass>& numero1,
                        const BigInt<Bass>& numero2);
  bool operator>=(const BigInt<Base>&) const;
  template <size_t Bass>
  friend bool operator<(const BigInt<Bass>& numero1,
                        const BigInt<Bass>& numero2);
  bool operator<=(const BigInt<Base>&) const;
  // Operadores de incremento / decremento
  BigInt<Base>& operator++();    // Pre-incremento
  BigInt<Base> operator++(int);  // Post-incremento
  BigInt<Base>& operator--();    // Pre-decremento
  BigInt<Base> operator--(int);  // Post-decremento
  // Operadores aritméticos
  template <size_t Bass>
  friend BigInt<Bass> operator+(const BigInt<Bass>&, const BigInt<Bass>&);
  BigInt<Base> operator-(const BigInt<Base>& numero2) const;
  BigInt<Base> operator-() const;
  BigInt<Base> operator*(const BigInt<Base>& numero2) const;
  template <size_t Bass>
  friend BigInt<Bass> operator/(const BigInt<Bass>& numero1,
                                const BigInt<Bass>& numero2);
  BigInt<Base> operator%(const BigInt<Base>& numero2) const;
  // Potencia ab
  template <size_t Bass>
  friend BigInt<Bass> Pow(const BigInt<Bass>&, const BigInt<Bass>&);

  // Métodos number
  Number* add(const Number*) const;
  Number* subtract(const Number*) const;
  Number* multiply(const Number*) const;
  Number* divide(const Number*) const;
  Number* module(const Number*) const;
  Number* pow(const Number*) const;

  // Operadores para cambiar a otras bases:
  operator BigInt<2>() const;
  operator BigInt<8>() const;
  operator BigInt<10>() const;
  operator BigInt<16>() const;

 protected:
  std::ostream& write(std::ostream&) const;
  std::istream& read(std::istream&);
  int GetBase() const;

 private:
  int signo_;
  std::vector<char> numero_;
};

// ====== ESPECIALIZACIÓN CLASE BigInt PARA NÚMEROS BINARIOS ======

template <>
class BigInt<2> : public Number {
 public:
  // Constructores
  BigInt(long long n = 0);
  BigInt(const std::string& numero);
  BigInt(const char* numero);
  BigInt(const BigInt<2>& numero);
  // Método para complementar a 2 un BigInt
  BigInt<2>& C2();
  // Acceso
  int sign() const;
  bool operator[](int posicion) const;
  // Operadores:
  BigInt<2>& operator=(const BigInt<2>& segundo_numero);
  // Inserción / Extracción
  // BORRAR LOS DOS MÉTODOS E IMPLEMENTAR SU CÓDIGO EN EL READ/WRITE
  friend std::ostream& operator<<(std::ostream& os, const BigInt<2>& numero);
  friend std::istream& operator>>(std::istream& is, BigInt<2>& numero);
  ///////////
  // Operadores de comparación
  friend bool operator==(const BigInt<2>& numero1, const BigInt<2>& numero2);
  bool operator!=(const BigInt<2>& numero1) const;
  friend bool operator<(const BigInt<2>& numero1, const BigInt<2>& numero2);
  friend bool operator>(const BigInt<2>& numero1, const BigInt<2>& numero2);
  bool operator>=(const BigInt<2>&) const;
  bool operator<=(const BigInt<2>&) const;
  // Operadores de incremento / decremento
  BigInt<2>& operator++();    // Pre-incremento
  BigInt<2> operator++(int);  // Post-incremento
  BigInt<2>& operator--();    // Pre-decremento
  BigInt<2> operator--(int);  // Post-decremento
  // Operadores aritméticos
  friend BigInt<2> operator+(const BigInt<2>&, const BigInt<2>&);
  BigInt<2> operator-(const BigInt<2>& numero2) const;
  // Operador de cambio de signo
  BigInt<2> operator-() const;
  BigInt<2> operator*(const BigInt<2>& numero2) const;
  friend BigInt<2> operator/(const BigInt<2>& numero1,
                             const BigInt<2>& numero2);
  BigInt<2> operator%(const BigInt<2>& numero2) const;
  // Potencia ab
  friend BigInt<2> Pow(const BigInt<2>&, const BigInt<2>&);

  // Métodos de la clase Number:
  Number* add(const Number*) const;
  Number* subtract(const Number*) const;
  Number* multiply(const Number*) const;
  Number* divide(const Number*) const;
  Number* module(const Number*) const;
  Number* pow(const Number*) const;

  // Conversores de binario a otras bases:
  operator BigInt<2>() const;
  operator BigInt<8>() const;
  operator BigInt<10>() const;
  operator BigInt<16>() const;

 protected:
  std::ostream& write(std::ostream&) const;
  std::istream& read(std::istream&);
  int GetBase() const;

 private:
  // tener en cuenta que en "numero_" los números se guardan al revés
  std::vector<bool> numero_;
};

// =============== CONSTRUCTORES ===============

template <size_t Base>
BigInt<Base>::BigInt(long long n) {
  long long resto{0};
  // Comprobamos si el número es menor que 0 para determinar el signo
  if (n >= 0) {
    signo_ = 1;
  } else {
    signo_ = -1;
  }
  while (n > 9) {
    resto = n % 10;
    n /= 10;
    if (resto > Base) {
      throw(BigIntBadDigit("El dígito " + std::to_string(resto) +
                           " no es compatible con la base " +
                           std::to_string(Base) + '\n'));
    }
    numero_.emplace_back(resto);
  }
  numero_.emplace_back(n);
}

template <size_t Base>
BigInt<Base>::BigInt(const std::string& numero_string) {
  // Comprobamos si existe el carácter '-' para ver si el número es negativo o
  // no
  size_t signo_encontrado{numero_string.find('-')};
  if (signo_encontrado ==
      std::string::npos) {  // npos es una constante de string que dice si lo ha
                            // encontrado o no
    signo_ = 1;
  } else {
    signo_ = -1;
  }
  for (int i{(int)numero_string.size() - 1}; i >= 0; --i) {
    if (isalpha(numero_string[i])) {  // Comprobamos si el dígito es un caracter
                                      // para después comprobar si es un
                                      // caracter hexadecimal para hacer la
                                      // conversión y meterlo en el vector
      if (numero_string[i] == 'A' || numero_string[i] == 'B' ||
          numero_string[i] == 'C' || numero_string[i] == 'D' ||
          numero_string[i] == 'E' || numero_string[i] == 'F') {
        switch (numero_string[i]) {  // En caso de que sea una de las letras que
                                     // queremos, comprobamos cual es y metemos
                                     // su correspondiente valor en hexdecimal
          case 'A':
            numero_.emplace_back(10);
            break;
          case 'B':
            numero_.emplace_back(11);
            break;
          case 'C':
            numero_.emplace_back(12);
            break;
          case 'D':
            numero_.emplace_back(13);
            break;
          case 'E':
            numero_.emplace_back(14);
            break;
          case 'F':
            numero_.emplace_back(15);
            break;
          default:
            break;
        }
      } else {  // En caso de no ser ninguna de las letras hexadecimales, el
                // usuario nos habrá metido una incorrecta por lo que indicamos
                // el error
        throw(BigIntBadDigit("La letra " + numero_string[i] +
                           " no es compatible con la base hexadecimal\n"));
      }
    } else {  // Si no es ninguna letra, es que es un número, por lo que lo
              // metemos directamente
      numero_.emplace_back(
          numero_string[i] -
          '0');  // Le restamos '0' para convertirlo en un entero
    }
  }
}

template <size_t Base>
BigInt<Base>::BigInt(const char* numero) {
  std::vector<char> vector_aux;
  long long aux{std::stoll(numero)};
  // Comprobamos si el número es menor que 0 para determinar el signo
  if (aux >= 0) {
    signo_ = 1;
  } else {
    signo_ = -1;
  }
  while (*numero != '\0') {
    if (isalpha(*numero)) {  // Comprobamos si el dígito es un caracter para
                             // después comprobar si es un caracter hexadecimal
                             // para hacer la conversión y meterlo en el vector
      if (*numero == 'A' || *numero == 'B' || *numero == 'C' ||
          *numero == 'D' || *numero == 'E' || *numero == 'F') {
        switch (*numero++) {  // En caso de que sea una de las letras que
                              // queremos, comprobamos cual es y metemos su
                              // correspondiente valor en hexdecimal
          case 'A':
            vector_aux.emplace_back(10);
            break;
          case 'B':
            vector_aux.emplace_back(11);
            break;
          case 'C':
            vector_aux.emplace_back(12);
            break;
          case 'D':
            vector_aux.emplace_back(13);
            break;
          case 'E':
            vector_aux.emplace_back(14);
            break;
          case 'F':
            vector_aux.emplace_back(15);
            break;
          default:
            break;
        }
      } else {
        throw(BigIntBadDigit("La letra " + numero_string[i] +
                           " no es compatible con la base hexadecimal\n"));
      }
    } else {  // Si no es ninguna letra, es que es un número, por lo que lo
              // metemos directamente
      vector_aux.emplace_back(
          (*numero++) - '0');  // Le restamos '0' para convertirlo en un entero
    }
  }
  std::reverse(vector_aux.begin(),
               vector_aux.end());  // Invertimos el vector para que se guarde
                                   // alrevés en el vector de chars del objeto
  numero_ = vector_aux;
}

template <size_t Base>
BigInt<Base>::BigInt(const BigInt<Base>& segundo_numero) {
  BigInt<Base> aux{};
  if (segundo_numero >= aux) {
    signo_ = 1;
  } else {
    signo_ = -1;
  }
  numero_ = segundo_numero.numero_;
}

// =============== SOBRECARGA DE OPERADOR [] ===============

template <size_t Base>
char BigInt<Base>::operator[](int posicion) const {
  // Usamos la "fórmula" [(numero_.size() - 1) - posicion] para acceder a el
  // número que queremos, esto lo hacemos así ya que el vector de chars del
  // BigInt está dado la vuelta
  if (numero_[(numero_.size() - 1) - posicion] >=
      10) {  // Si el número es mayor o igual que 10 es que es una letra en
             // hexadecimal así que la convertimos a un número
    return (
        static_cast<char>('A' + numero_[(numero_.size() - 1) - posicion] - 10));
  }  // Si es menor que 10 es que es un número, por lo que lo convertimos a un
     // char o lo sacamos por pantalla
  return (static_cast<char>(numero_[(numero_.size() - 1) - posicion] + '0'));
}

// ============= SOBRECARGA DE OPERADORES DE INSERCIÓN/EXTRACCIÓN =============

template <size_t Base>
std::ostream& operator<<(std::ostream& os, const BigInt<Base>& numero) {
  for (unsigned long i{numero.numero_.size() - 1}; i != -1; --i) {
    if (numero.numero_[i] >=
        10) {  // Si el número es mayor o igual que 10 es que es una letra en
               // hexadecimal así que la convertimos a un número
      os << (static_cast<char>('A' + numero.numero_[i] - 10));
    } else {  // Si es menor que 10 es que es un número, por lo que lo
              // convertimos a un char o lo sacamos por pantalla
      os << (static_cast<char>(numero.numero_[i] + '0'));
    }
  }
  return os;
}

template <size_t Base>
std::istream& operator>>(std::istream& is, BigInt<Base>& big_int) {
  std::string aux_numero;
  is >> aux_numero;  // Guardamos el número en un string
  BigInt<Base> aux{
      aux_numero};  // Creamos un BigInt auxiliar para que el vector de chars de
                    // el número que queremos introducirle el valor sea cambiado
                    // por el que queramos
  big_int.numero_.clear();  // Borramos el contenido del BigInt para
                            // introducirle el nuevo valor
  big_int = aux;
  return is;
}

// =============== SOBRECARGA DE OPERADOR '=' ===============

template <size_t Base>
BigInt<Base>& BigInt<Base>::operator=(const BigInt<Base>& segundo_numero) {
  numero_ = segundo_numero.numero_;
  return *this;
}

// =============== SOBRECARGA DE OPERADORES DE COMPARACIÓN ===============

template <size_t Base>
bool operator==(const BigInt<Base>& numero1, const BigInt<Base>& numero2) {
  return numero1.numero_ == numero2.numero_;
}

template <size_t Base>
bool operator>(const BigInt<Base>& numero1, const BigInt<Base>& numero2) {
  std::vector<char> aux_vector_numero1{numero1.numero_},
      aux_vector_numero2{numero2.numero_};
  long unsigned int i{aux_vector_numero1.size() - 1},
      j{aux_vector_numero2.size() - 1}, size_maximo{};
  // Eliminamos los posibles 0s a la izquierda que puedan haber, para poder
  // comparar por el tamaño de los vectores
  while (static_cast<char>(aux_vector_numero1[i] + '0') == '0' &&
         aux_vector_numero1.size() > 1) {
    aux_vector_numero1.pop_back();
    i--;
  }
  while (static_cast<char>(aux_vector_numero2[j] + '0') == '0' &&
         aux_vector_numero2.size() > 1) {
    aux_vector_numero1.pop_back();
    j--;
  }
  if (aux_vector_numero1.size() > aux_vector_numero2.size() ||
      (numero1.sign() == 1 && numero2.sign() == -1)) {
    return true;
  } else if (aux_vector_numero2.size() > aux_vector_numero1.size() ||
             (numero1.sign() == -1 && numero2.sign() == 1)) {
    return false;
  }
  // Si hemos llegado a este punto, es que tienen el mismo tamaño, tenemos
  // invertir los vectores por que están alrevés por el propio constructor de
  // BigInt para después compararlos
  std::reverse(aux_vector_numero1.begin(), aux_vector_numero1.end());
  std::reverse(aux_vector_numero2.begin(), aux_vector_numero2.end());
  return aux_vector_numero1 > aux_vector_numero2;
}

template <size_t Bass>
bool operator<(const BigInt<Bass>& numero1, const BigInt<Bass>& numero2) {
  std::vector<char> aux_vector_numero1{numero1.numero_},
      aux_vector_numero2{numero2.numero_};
  long unsigned int i{aux_vector_numero1.size() - 1},
      j{aux_vector_numero2.size() - 1}, size_maximo{};
  // Eliminamos los posibles 0s a la izquierda que puedan haber, para poder
  // comparar por el tamaño de los vectores
  while (static_cast<char>(aux_vector_numero1[i] + '0') == '0' &&
         aux_vector_numero1.size() > 1) {
    aux_vector_numero1.pop_back();
    i--;
  }
  while (static_cast<char>(aux_vector_numero2[j] + '0') == '0' &&
         aux_vector_numero2.size() > 1) {
    aux_vector_numero1.pop_back();
    j--;
  }

  if (aux_vector_numero1.size() < aux_vector_numero2.size() ||
      (numero1.sign() == -1 && numero2.sign() == 1)) {
    return true;
  } else if (aux_vector_numero2.size() < aux_vector_numero1.size() ||
             (numero1.sign() == 1 && numero2.sign() == -1)) {
    return false;
  }
  // Si hemos llegado a este punto, es que tienen el mismo tamaño, tenemos
  // invertir los vectores por que están alrevés por el propio constructor de
  // BigInt para después compararlos
  std::reverse(aux_vector_numero1.begin(), aux_vector_numero1.end());
  std::reverse(aux_vector_numero2.begin(), aux_vector_numero2.end());
  return aux_vector_numero1 < aux_vector_numero2;
}

template <size_t Base>
bool BigInt<Base>::operator!=(const BigInt<Base>& numero2) const {
  return numero_ != numero2.numero_;
}

template <size_t Base>
bool BigInt<Base>::operator>=(const BigInt<Base>& numero2) const {
  std::vector<char> aux_vector_numero1{numero_},
      aux_vector_numero2{numero2.numero_};
  long unsigned i{aux_vector_numero1.size() - 1},
      j{aux_vector_numero2.size() - 1}, size_maximo{};
  // Eliminamos los posibles 0s a la izquierda que puedan haber, para poder
  // comparar por el tamaño de los vectores
  while (static_cast<char>(aux_vector_numero1[i] + '0') == '0' &&
         aux_vector_numero1.size() > 1) {
    aux_vector_numero1.pop_back();
    i--;
  }
  while (static_cast<char>(aux_vector_numero2[j] + '0') == '0' &&
         aux_vector_numero2.size() > 1) {
    aux_vector_numero1.pop_back();
    j--;
  }

  if (aux_vector_numero1.size() > aux_vector_numero2.size() ||
      (signo_ == 1 && numero2.sign() == -1)) {
    return true;
  } else if (aux_vector_numero2.size() > aux_vector_numero1.size() ||
             (signo_ == -1 && numero2.sign() == 1)) {
    return false;
  }
  // Si hemos llegado a este punto, es que tienen el mismo tamaño, tenemos
  // invertir los vectores por que están alrevés por el propio constructor de
  // BigInt para después compararlos
  std::reverse(aux_vector_numero1.begin(), aux_vector_numero1.end());
  std::reverse(aux_vector_numero2.begin(), aux_vector_numero2.end());
  return aux_vector_numero1 >= aux_vector_numero2;
}

template <size_t Base>
bool BigInt<Base>::operator<=(const BigInt<Base>& numero2) const {
  std::vector<char> aux_vector_numero1{numero_},
      aux_vector_numero2{numero2.numero_};
  long unsigned i{aux_vector_numero1.size() - 1},
      j{aux_vector_numero2.size() - 1}, size_maximo{};
  // Eliminamos los posibles 0s a la izquierda que puedan haber, para poder
  // comparar por el tamaño de los vectores
  while (static_cast<char>(aux_vector_numero1[i] + '0') == '0' &&
         aux_vector_numero1.size() > 1) {
    aux_vector_numero1.pop_back();
    i--;
  }
  while (static_cast<char>(aux_vector_numero2[j] + '0') == '0' &&
         aux_vector_numero2.size() > 1) {
    aux_vector_numero1.pop_back();
    j--;
  }
  if (aux_vector_numero1.size() < aux_vector_numero2.size() ||
      (signo_ == -1 && numero2.sign() == 1)) {
    return true;
  } else if (aux_vector_numero2.size() < aux_vector_numero1.size() ||
             (signo_ == 1 && numero2.sign() == -1)) {
    return false;
  }
  // Si hemos llegado a este punto, es que tienen el mismo tamaño, tenemos
  // invertir los vectores por que están alrevés por el propio constructor de
  // BigInt para después compararlos
  std::reverse(aux_vector_numero1.begin(), aux_vector_numero1.end());
  std::reverse(aux_vector_numero2.begin(), aux_vector_numero2.end());
  return aux_vector_numero1 <= aux_vector_numero2;
}

// =============== OPERADORES ARITMÉTICOS ===============

// Operador cambio de signo
template <size_t Base>
BigInt<Base> BigInt<Base>::operator-() const {
  BigInt<Base> aux{*this};
  if (aux.sign() == 1) {  // Si numero_.sign() = 1, es que es positivo, por lo
                          // que le añadimos el signo -(45)
    aux.signo_ = -1;
    aux.numero_.emplace_back('-' - '0');
  } else if (aux.sign() ==
             -1) {  // Si numero_.sign() = -1, es que es negativo, por lo que
                    // le quitamos el signo - para hacerlo positivo
    aux.signo_ = 1;
    aux.numero_.pop_back();
  }
  return aux;
}

// Operador resta
template <size_t Base>
BigInt<Base> BigInt<Base>::operator-(const BigInt<Base>& numero2) const {
  int carry = 0;
  BigInt<Base> aux_numero1{*this}, aux_numero2{numero2}, result;

  // Rellenando el número más corto con 0s
  int diferencia = aux_numero1.numero_.size() - aux_numero2.numero_.size();
  if (diferencia < 0) {  // numero2 es el menor de los dos
    for (int i = 0; i < -diferencia; i++) {
      aux_numero1.numero_.push_back(0);
    }
  } else if (diferencia > 0) {  // numero1 es el menor de los dos
    for (int i = 0; i < diferencia; i++) {
      aux_numero2.numero_.push_back(0);
    }
  }

  // Restando los números
  for (int i = 0; i < aux_numero1.numero_.size(); i++) {
    int difference = aux_numero1.numero_[i] - aux_numero2.numero_[i] - carry;
    if (difference < 0) {
      carry = 1;
      difference += Base;
    } else {
      carry = 0;
    }
    result.numero_.push_back(difference);
  }

  // Al final de cada operación se añade un 0 adicional al resultado de la
  // multiplicación, por lo que se elimina antes de devolver el resultado
  // invirtiendo el número, quitando el 0 y volviendo a invertir el número
  std::reverse(result.numero_.begin(), result.numero_.end());
  result.numero_.pop_back();
  std::reverse(result.numero_.begin(), result.numero_.end());
  return result;
}

// Operador suma
template <size_t Base>
BigInt<Base> operator+(const BigInt<Base>& numero1,
                       const BigInt<Base>& numero2) {
  int carry = 0;
  BigInt<Base> aux_numero1{numero1}, aux_numero2{numero2},
      result;  // resultado como BigInt

  // Rellenando el número más corto con 0s
  auto diferencia{aux_numero1.numero_.size() - aux_numero2.numero_.size()};
  if (diferencia < 0) {  // numero1 es el menor de los dos
    for (int i{0}; i < -diferencia; ++i) {
      aux_numero1.numero_.push_back(0);
    }
  } else if (diferencia > 0) {  // numero2 es el menor de los dos
    for (int i = 0; i < diferencia; i++) {
      aux_numero2.numero_.push_back(0);
    }
  }

  // Sumando los números
  for (int i = 0; i < aux_numero1.numero_.size(); i++) {
    int sum = aux_numero1.numero_[i] + aux_numero2.numero_[i] + carry;
    result.numero_.push_back(sum % Base);
    carry = sum / Base;
  }

  // Añadiendo el carry si es que hay
  if (carry > 0) {
    result.numero_.push_back(carry);
  }

  // Al final de cada operación se añade un 0 adicional al resultado de la suma,
  // por lo que se elimina antes de devolver el resultado invirtiendo el número,
  // quitando el 0 y volviendo a invertir el número
  std::reverse(result.numero_.begin(), result.numero_.end());
  result.numero_.pop_back();
  std::reverse(result.numero_.begin(), result.numero_.end());
  return result;
}

// Operador multiplicación
template <size_t Base>
BigInt<Base> BigInt<Base>::operator*(const BigInt<Base>& numero2) const {
  BigInt<Base> aux{*this}, result{"0"};
  for (int i = 0; i < aux.numero_.size(); i++) {
    int carry = 0;
    BigInt<Base> aux_result;
    for (int j = 0; j < numero2.numero_.size() || carry > 0; j++) {
      int mul = aux.numero_[i] *
                    (j < numero2.numero_.size() ? numero2.numero_[j] : 0) +
                carry;
      aux_result.numero_.push_back(mul % Base);
      carry = mul / Base;
    }
    for (int j = 0; j < i; j++) {
      aux_result.numero_.insert(aux_result.numero_.begin(), 0);
    }
    result = result + aux_result;
  }
  // Al final de cada operación se añade un 0 adicional al resultado de la
  // multiplicación, por lo que se elimina antes de devolver el resultado
  // invirtiendo el número, quitando el 0 y volviendo a invertir el número
  std::reverse(result.numero_.begin(), result.numero_.end());
  result.numero_.pop_back();
  std::reverse(result.numero_.begin(), result.numero_.end());
  return result;
}

// Operador división
template <size_t Base>
BigInt<Base> operator/(const BigInt<Base>& numero1,
                       const BigInt<Base>& numero2) {
  // Si se cumplen las siguientes dos condiciones, el divisor, que en este caso
  // es "numero2", es 0. Una división por 0 no es posible, por lo que lo
  // indicamos y salimos del programa
  if (numero2.numero_.size() == 1 && numero2.numero_[0] == 0) {
    throw(BigIntDivisionByZero("No es posible realizar una división por 0\n"));
  }

  // Verificar si el dividendo(numero1) es menor que el divisor(numero2), si
  // esto es así, el cociente de la división dará 0, por lo que retornamos un
  // BigInt con valor 0.
  if (numero1 < numero2) {
    return BigInt<Base>{};
  }

  // realizar la división
  BigInt<Base> resta{numero1},
      resultado{};  // Contador que después de hacer restas consecutivas, será
                    // el resultado de la división
  while (resta >= numero2) {
    resta = resta - numero2;
    resultado++;
  }
  return resultado;
}

// Operador módulo
template <size_t Base>
BigInt<Base> BigInt<Base>::operator%(const BigInt<Base>& numero2) const {
  // Si se cumplen las siguientes dos condiciones, el divisor, que en este
  // caso es "numero2", es 0. Una división por 0 no es posible, por lo que lo
  // indicamos y salimos del programa
  if (numero2.numero_.size() == 1 && numero2.numero_[0] == 0) {
    std::cout << "No es posible realizar una división por 0" << std::endl;
    exit(1);
  }

  // Verificar si el dividendo(numero1) es menor que el divisor(numero2), si
  // esto es así, el cociente de la división dará 0, por lo que retornamos un
  // BigInt con valor 0.
  if (*this < numero2) {
    return BigInt<Base>{};
  }

  // realizar la división
  BigInt<Base> resta{*this},
      resultado{};  // Contador que después de hacer restas consecutivas, será
                    // el resultado de la división
  while (resta >= numero2) {
    resta = resta - numero2;
    resultado++;
  }

  // Quitamos el 0 sobrante
  resta.numero_.pop_back();
  return resta;
}

// Potencia
template <size_t Base>
BigInt<Base> Pow(const BigInt<Base>& base, const BigInt<Base>& exponente) {
  BigInt<Base> resultado{1}, contador{};
  while (contador < exponente) {
    resultado = resultado * base;  // vamos haciendo la potencia multiplicando
                                   // el número por si mismo iterativamente
    contador++;
  }
  return resultado;
}

// =============== OPERADORES DE INCREMENTO / DECREMENTO ===============

template <size_t Base>
BigInt<Base>& BigInt<Base>::operator++() {  // Pre-incremento
  // BigInt auxiliar inicializado a '1' para poder hacer el incremento con la
  // sobrecarga del operador '+'
  BigInt<Base> aux{1};
  *this = *this + aux;
  return *this;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator++(int) {  // Post-incremento
  // primero hacemos el incremento del objeto que está invocando el método y
  // después devolvemos una copia del mismo objeto antes de ser incrementado.
  // Esto se hace así para que el operador de post-incremento no sume antes de
  // utilizar el número
  BigInt<Base> aux{1}, result{*this};
  *this = *this + aux;
  return result;
}

template <size_t Base>
BigInt<Base>& BigInt<Base>::operator--() {  // Pre-decremento
  // Como no se puede restar un BigInt con una constante, Inicializamos un
  // BigInt con valor 1 para poder restar aprovechando la sobrecarga del
  // operador
  BigInt<Base> restando{1};
  *this = *this - restando;
  return *this;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator--(int) {  // Post-decremento
  BigInt<Base> aux{*this}, restando{1};
  *this = *this - restando;
  return aux;
}

// Métodos de la clase Number
template <size_t Base>
Number* BigInt<Base>::add(const Number* numero) const {
  BigInt<Base> n = static_cast<BigInt<Base>>(*numero);
  return reinterpret_cast<Number*>(new BigInt<Base>{*this + n});
}

template <size_t Base>
Number* BigInt<Base>::subtract(const Number* numero) const {
  BigInt<Base> n = static_cast<BigInt<Base>>(*numero);
  return reinterpret_cast<Number*>(new BigInt<Base>{*this - n});
}

template <size_t Base>
Number* BigInt<Base>::multiply(const Number* numero) const {
  BigInt<Base> n = static_cast<BigInt<Base>>(*numero);
  return reinterpret_cast<Number*>(new BigInt<Base>{*this * n});
}

template <size_t Base>
Number* BigInt<Base>::divide(const Number* numero) const {
  BigInt<Base> n = static_cast<BigInt<Base>>(*numero);
  return reinterpret_cast<Number*>(new BigInt<Base>{*this / n});
}

template <size_t Base>
Number* BigInt<Base>::module(const Number* numero) const {
  BigInt<Base> n = static_cast<BigInt<Base>>(*numero);
  return reinterpret_cast<Number*>(new BigInt<Base>{*this % n});
}

template <size_t Base>
Number* BigInt<Base>::pow(const Number* numero) const {
  BigInt<Base> n = static_cast<BigInt<Base>>(*numero);
  return reinterpret_cast<Number*>(new BigInt<Base>{Pow(*this, n)});
}

template <size_t Base>
std::ostream& BigInt<Base>::write(std::ostream& os) const {
  os << *this;
  return os;
}

template <size_t Base>
std::istream& BigInt<Base>::read(std::istream& is) {
  is >> *this;
  return is;
}

// Operadores de cambio de tipo:

template <size_t Base>
BigInt<Base>::operator BigInt<2ULL>() const {
  // Se omite el caso de convertir de base 2 a base 2
  if (Base == 10) {
    // Se convierte a decimal por el método de los residuos
    std::string numero, residuos;
    BigInt<Base> aux{*this};
    for (unsigned long i{aux.numero_.size() - 1}; i != -1; --i) {
      if (aux.numero_[i] >= 10) {
        numero.push_back(static_cast<char>('A' + numero_[i] - 10));
      } else {
        numero.push_back((static_cast<char>(numero_[i] + '0')));
      }
    }
    long long aux_numero{std::stoll(numero)};
    int resto;
    while (aux_numero >= 2) {
      resto = aux_numero % 2;
      residuos.push_back(static_cast<char>(resto + '0'));
      aux_numero /= 2;
    }
    residuos.push_back(static_cast<char>(aux_numero + '0'));
    if (aux.sign() == 1) {
      residuos.push_back(static_cast<char>(0 + '0'));
    }
    std::reverse(residuos.begin(), residuos.end());
    BigInt<2> resultado{residuos};
    return resultado;
  } else if (Base == 8) {
    // Se convierte a binario sustituyendo cada valor en octal por su
    // equivalente en binario
    BigInt<Base> aux{*this};
    std::string resultado{
        ""};  // auxiliar que nos permite ir guardando el número en binario
    for (unsigned long i{aux.numero_.size() - 1}; i != -1; --i) {
      switch (aux.numero_[i]) {
        case 1: {
          resultado += {"001"};
          break;
        }
        case 2: {
          resultado += {"010"};
          break;
        }
        case 3: {
          resultado += {"011"};
          break;
        }
        case 4: {
          resultado += {"100"};
          break;
        }
        case 5: {
          resultado += {"101"};
          break;
        }
        case 6: {
          resultado += {"110"};
          break;
        }
        case 7: {
          resultado += {"111"};
          break;
        }
        default: {
          resultado += {"000"};
          break;
        }
      }
    }
    BigInt<2> resultado_binario{resultado};
    return resultado_binario;
  } else if (Base == 16) {
    // Para pasar de hexadecimal a binario, si lo hicieramos a papel miraríamos
    // cada dígito a hexadecimal y lo sustituiriamos por su equivalente en
    // binario, en este caso con 4 bits, y lo iríamos añadiendo al final de el
    // número
    BigInt<Base> aux{*this};
    std::string resultado{
        ""};  // auxiliar que nos permite ir guardando el número en binario
    for (unsigned long i{aux.numero_.size() - 1}; i != -1;
         --i) {  // For a la inversa por que el número está al revés
      switch (aux.numero_[i]) {
        case 1: {
          resultado += {"0001"};
          break;
        }
        case 2: {
          resultado += {"0010"};
          break;
        }
        case 3: {
          resultado += {"0011"};
          break;
        }
        case 4: {
          resultado += {"0100"};
          break;
        }
        case 5: {
          resultado += {"0101"};
          break;
        }
        case 6: {
          resultado += {"0110"};
          break;
        }
        case 7: {
          resultado += {"0111"};
          break;
        }
        case 8: {
          resultado += {"0100"};
          break;
        }
        case 9: {
          resultado += {"0101"};
          break;
        }
        case 10: {
          resultado += {"1010"};
          break;
        }
        case 11: {
          resultado += {"1011"};
          break;
        }
        case 12: {
          resultado += {"1100"};
          break;
        }
        case 13: {
          resultado += {"1101"};
          break;
        }
        case 14: {
          resultado += {"1110"};
          break;
        }
        case 15: {
          resultado += {"1111"};
          break;
        }
        default: {
          resultado += {"00000"};
          break;
        }
      }
    }
    BigInt<2> resultado_binario{
        resultado};  // Declaramos un BigInt<2> para poder hacer la conversión
    return resultado_binario;
  }
  return *this;
}

template <size_t Base>
BigInt<Base>::operator BigInt<8UL>() const {
  // Omitimos la base 2, por que el conversor de tipo está hecho en la
  // especialización
  if (Base == 10) {
    // Hacer por residuos dividiendo entre 8
    std::string numero, residuos;
    BigInt<Base> aux{*this};
    for (unsigned long i{aux.numero_.size() - 1}; i != -1; --i) {
      if (aux.numero_[i] >= 10) {
        numero.push_back(static_cast<char>('A' + numero_[i] - 10));
      } else {
        numero.push_back((static_cast<char>(numero_[i] + '0')));
      }
    }
    long long aux_numero{std::stoll(numero)};
    int resto;
    while (aux_numero >= 8) {
      resto = aux_numero % 8;
      residuos.push_back(static_cast<char>(resto + '0'));
      aux_numero /= 8;
    }
    residuos.push_back(static_cast<char>(aux_numero + '0'));
    std::reverse(residuos.begin(), residuos.end());
    BigInt<8> resultado{residuos};
    return resultado;
  } else if (Base == 16) {
    // 1. Pasar de hexadecimal a binario, para después pasarlo a octal, para
    // ello usamos el conversor de cualquier base a binario
    BigInt<2> numero_binario{*this};

    // 2. Pasar de binario a octal, usando el conversor de la especialización
    BigInt<8> resultado_final{
        numero_binario};  // Usamos el conversor de la especialización
    return resultado_final;
  }
  // Caso pasar de octal a octal
  return *this;  // Si se pasa de octal a octal el número se queda igual
}

template <size_t Base>
BigInt<Base>::operator BigInt<10UL>() const {
  // Omitimos la base 2, por que el conversor de tipo está hecho en la
  // especialización
  if (Base == 8) {
    BigInt<Base> aux{*this};
    long long resultado{0};
    for (unsigned long i{0}; i < aux.numero_.size(); ++i) {
      resultado += (aux.numero_[i] * std::pow(8, i));
    }
    return BigInt<10>{resultado};
  } else if (Base == 16) {
    BigInt<Base> aux{*this};
    long long resultado{0};
    for (unsigned long i{0}; i < aux.numero_.size(); ++i) {
      resultado += (aux.numero_[i] * std::pow(16, i));
    }
    return BigInt<10>{resultado};
  }
  return *this;
}

template <size_t Base>
BigInt<Base>::operator BigInt<16UL>() const {
  // Omitimos la base 2, por que el conversor de tipo está hecho en la
  // especialización
  if (Base == 8) {
    // Primero pasamos de octal a binario, usando el conversor de cualquier base
    // a binario
    BigInt<2> resultado_binario{*this};
    // Pasamos de binario a hexadecimal con el conversor de la especialización
    return BigInt<16>{resultado_binario};
  } else if (Base == 10) {
    // Pasamos de decimal a hexadecimal por el método de los residuos:
    std::string numero, residuos;
    BigInt<Base> aux{*this};
    for (unsigned long i{aux.numero_.size() - 1}; i != -1; --i) {
      if (aux.numero_[i] >= 10) {
        numero.push_back(static_cast<char>('A' + numero_[i] - 10));
      } else {
        numero.push_back((static_cast<char>(numero_[i] + '0')));
      }
    }
    long long aux_numero{std::stoll(numero)};
    int resto;
    while (aux_numero >= 16) {
      resto = aux_numero % 16;
      switch (resto) {
        case 10: {
          residuos.push_back('A');
          break;
        }
        case 11: {
          residuos.push_back('B');
          break;
        }
        case 12: {
          residuos.push_back('C');
          break;
        }
        case 13: {
          residuos.push_back('D');
          break;
        }
        case 14: {
          residuos.push_back('E');
          break;
        }
        case 15: {
          residuos.push_back('F');
          break;
        }
        default: {
          residuos.push_back(static_cast<char>(resto + '0'));
          break;
        }
      }
      aux_numero /= 16;
    }
    residuos.push_back(static_cast<char>(aux_numero + '0'));
    std::reverse(residuos.begin(), residuos.end());
    return BigInt<16>{residuos};
  }
  // Caso pasar de hexadecimal a hexadecimal
  return *this;
}

// Método para obtener la base
template <size_t Base>
int BigInt<Base>::GetBase() const {
  return Base;
}

#endif
