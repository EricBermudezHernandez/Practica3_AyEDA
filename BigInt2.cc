#include "big_int.hpp"


// =============== CONSTRUCTORES ===============

BigInt<2>::BigInt(long long n) {
  int resto;
  while (n > 9) {
    resto = n % 10;
    n /= 10;
    numero_.emplace_back(resto);
  }
  numero_.emplace_back(n);
}

BigInt<2>::BigInt(const std::string& numero_binario) {
  for (unsigned long i{numero_binario.size() - 1}; i != -1; --i) {
    numero_.emplace_back(numero_binario[i] - '0');
  }
}

BigInt<2>::BigInt(const char* numero_binario) {
  while (*numero_binario != '\0') {
    numero_.emplace_back((*numero_binario++ - '0'));
  }
  // Le damos la vuelta para guardarlo al revés
  std::reverse(numero_.begin(), numero_.end());
}

BigInt<2>::BigInt(const BigInt<2>& numero_binario) {
  numero_ = numero_binario.numero_;
}  // Constructor de copia

// Complemento a 2 para realizar ciertas operaciones de manera más visual
BigInt<2>& BigInt<2>::C2() {
  // Se hace la operación NEG de izquierda a derecha por que el número está
  // guardado alrevés
  bool primer_uno_encontrado{
      false};  // variable que nos sirve para decir que el primer 1 ha sido
               // encontrado y hacer NOT de los demás bits
  for (int i{0}; i < numero_.size(); ++i) {
    if (primer_uno_encontrado) {
      if (numero_[i] == 0) {
        numero_[i] = 1;
      } else {
        numero_[i] = 0;
      }
    }
    if (numero_[i] == 1) {
      primer_uno_encontrado = true;
    }
  }
  return *this;
}

// =============== SOBRECARGA DE OPERADOR [] y getter signo ===============

bool BigInt<2>::operator[](int posicion) const {  // Acceso al i-ésimo dígito
  // Usamos la "fórmula" [(numero_.size() - 1) - posicion] para acceder a el
  // número que queremos, esto lo hacemos así ya que el vector de bool del
  // BigInt está dado la vuelta
  return numero_[numero_.size() - 1];
}

int BigInt<2>::sign() const {
  // Si hay un 1 en la primera posición devolvemos un 1, si no es un 1 es
  // positivo y por lo tanto devolvemos un 0
  if (numero_[numero_.size() - 1] == 1) {
    return 1;
  }
  return 0;
}
// ============= SOBRECARGA DE OPERADORES DE INSERCIÓN/EXTRACCIÓN =============

std::istream& operator>>(std::istream& is, BigInt<2>& numero) {
  // Este operador funciona asumiendo que el número que te van a introducir es
  // en binario
  std::string aux_numero;
  is >> aux_numero;
  BigInt<2> numero_final{aux_numero};
  numero.numero_.clear();
  numero = numero_final;
  return is;
}

std::ostream& operator<<(std::ostream& os, const BigInt<2>& numero) {
  for (unsigned long i{numero.numero_.size() - 1}; i != -1; --i) {
    os << numero.numero_[i];
  }
  return os;
}

// =============== SOBRECARGA DE OPERADOR '=' ===============

BigInt<2>& BigInt<2>::operator=(const BigInt<2>& segundo_numero) {
  numero_ = segundo_numero.numero_;
  return *this;
}

// =============== SOBRECARGA DE OPERADORES DE COMPARACIÓN ===============
bool operator==(const BigInt<2>& numero1, const BigInt<2>& numero2) {
  return numero1.numero_ == numero2.numero_;
}

bool BigInt<2>::operator!=(const BigInt<2>& numero1) const {
  return numero_ != numero1.numero_;
}

bool operator>(const BigInt<2>& numero1, const BigInt<2>& numero2) {
  BigInt<2> aux_numero1{numero1}, aux_numero2{numero2};
  BigInt<10> aux_numero1_decimal{aux_numero1},
      aux_numero2_decimal{
          aux_numero2};  // Usamos dos BigInt<10> auxiliares para comprobar si
                         // uno es mayor que el otro
  return aux_numero1_decimal > aux_numero2_decimal;
}

bool operator<(const BigInt<2>& numero1, const BigInt<2>& numero2) {
  BigInt<2> aux_numero1{numero1}, aux_numero2{numero2};
  BigInt<10> aux_numero1_decimal{aux_numero1},
      aux_numero2_decimal{
          aux_numero2};  // Usamos dos BigInt<10> auxiliares para comprobar si
                         // uno es menor que el otro
  return aux_numero1_decimal < aux_numero2_decimal;
}

bool BigInt<2>::operator>=(const BigInt<2>& numero2) const {
  BigInt<2> aux_numero1{*this}, aux_numero2{numero2};
  BigInt<10> aux_numero1_decimal{aux_numero1},
      aux_numero2_decimal{
          aux_numero2};  // Usamos dos BigInt<10> auxiliares para comprobar si
                         // uno es mayor o igual que el otro
  return aux_numero1_decimal >= aux_numero2_decimal;
}

bool BigInt<2>::operator<=(const BigInt<2>& numero2) const {
  BigInt<2> aux_numero1{*this}, aux_numero2{numero2};
  BigInt<10> aux_numero1_decimal{aux_numero1},
      aux_numero2_decimal{
          aux_numero2};  // Usamos dos BigInt<10> auxiliares para comprobar si
                         // uno es menor o igual que el otro
  return aux_numero1_decimal <= aux_numero2_decimal;
}

// =============== OPERADORES ARITMÉTICOS ===============
BigInt<2> operator+(const BigInt<2>& numero1, const BigInt<2>& numero2) {
  int carry = 0;
  BigInt<2> aux_numero1{numero1}, aux_numero2{numero2},
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
    result.numero_.push_back(sum % 2);
    carry = sum / 2;
  }

  // En complemento a 2, si hay un carry final se descarta asi que no lo
  // añadimos al final, pero si los dos números son positivos entonces si se
  // tiene que añadir el carry, por lo que comprobamos si los dos números son
  // positivos mirando si el primer bit de signo de los dos números es '0
  if (numero1.sign() == 0 && numero2.sign() == 0 ||
      (aux_numero1.numero_.size() == 1 && aux_numero2.numero_.size() == 1)) {
    result.numero_.push_back(carry);
    // Al estar los números en C2, si un número empieza en 1 es que es negativo,
    // pudiendo dar error al convertirse en otra base, ya que se tomaría como un
    // número negativo Por lo que, añadimos un 0 que no cambia el valor de el
    // número y lo "vuelve postivo"
    result.numero_.push_back(0);
  }

  // Al final de cada operación se añade un 0 adicional al resultado de la suma,
  // por lo que se elimina antes de devolver el resultado invirtiendo el número,
  // quitando el 0 y volviendo a invertir el número
  std::reverse(result.numero_.begin(), result.numero_.end());
  result.numero_.pop_back();
  std::reverse(result.numero_.begin(), result.numero_.end());
  return result;
}

BigInt<2> BigInt<2>::operator-(const BigInt<2>& numero2) const {
  int carry = 0;
  BigInt<2> aux_numero1{*this}, aux_numero2{numero2}, result;

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
  // Si el número es negativo, se va a convertir en una suma, ej: 34 - (-23) =
  // 34 + 23 Complementamos a 2 para transformar el número en positivo y hacer
  // una suma Si no es negativo, es positivo por lo que hacemos una suma
  // negativa ej: 3 + (-4)
  aux_numero2.C2();
  // Restando los números
  result = aux_numero1 + aux_numero2;
  // Si los dos números son positivos en una suma binaria, se añade el bit de
  // carry, pero en una resta siempre se quita, por lo que comprobamos si los
  // dos números son positivos para quitarles el carry
  if (aux_numero1.sign() == 0 && aux_numero2.sign() == 0) {
    result.numero_.pop_back();
  }

  return result;
}

// Operador cambio de signo
BigInt<2> BigInt<2>::operator-() const {
  // Para cambiar un número binario de signo, se hace el C2. Por lo que
  // simplemente usamos el método que ya tenemos y devolvemos el número
  BigInt<2> aux{*this};
  return aux.C2();
}

// Multiplicación
BigInt<2> BigInt<2>::operator*(const BigInt<2>& numero2) const {
  // Primero comprobamos si se va a multiplicar el número por 0, para en ese
  // caso, devolver un 0
  BigInt<2> aux{"0"}, multiplicando{*this}, resultado, iterador;
  if (numero2 == aux) {
    return aux;
  }
  while (iterador < numero2) {
    resultado = resultado + multiplicando;
    iterador++;
  }
  return resultado;
}

// División
BigInt<2> operator/(const BigInt<2>& numero1, const BigInt<2>& divisor) {
  // Si se cumplen las siguientes dos condiciones, el divisor, que en este caso
  // es "numero2", es 0. Una división por 0 no es posible, por lo que lo
  // indicamos y salimos del programa
  if (divisor.numero_.size() == 1 && divisor.numero_[0] == 0) {
    throw(BigIntDivisionByZero("No es posible realizar una división por 0\n"));
  }

  // Verificar si el dividendo(numero1) es menor que el divisor(numero2), si
  // esto es así, el cociente de la división dará 0, por lo que retornamos un
  // BigInt con valor 0.
  if (numero1 < divisor) {
    return BigInt<2>{};
  }

  // realizar la división
  BigInt<2> dividendo{numero1},
      resultado{};  // Contador que después de hacer restas consecutivas, será
                    // el resultado de la división
  while (dividendo >= divisor) {
    dividendo = dividendo - divisor;
    resultado++;
  }
  return resultado;
}

// Modulo
BigInt<2> BigInt<2>::operator%(const BigInt<2>& numero2) const {
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
    return BigInt<2>{};
  }

  // realizar la división
  BigInt<2> resta{*this},
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
BigInt<2> Pow(const BigInt<2>& base, const BigInt<2>& exponente) {
  BigInt<2> resultado{1}, contador{};
  while (contador < exponente) {
    resultado = resultado * base;  // vamos haciendo la potencia multiplicando
                                   // el número por si mismo iterativamente
    contador++;
  }
  return resultado;
}

// =============== OPERADORES DE INCREMENTO / DECREMENTO ===============
BigInt<2>& BigInt<2>::operator++() {  // Pre-incremento
  BigInt<2> aux{1};
  *this = *this + aux;
  return *this;
}

BigInt<2> BigInt<2>::operator++(int) {  // Post-incremento
  BigInt<2> aux{1}, copia{*this};
  *this = *this + aux;
  return copia;  // devolvemos la copia del número antes de ser incrementado e
                 // incrementamos antes el original
}

BigInt<2>& BigInt<2>::operator--() {  // Pre-decremento
  BigInt<2> aux{1};
  *this = *this - aux;
  return *this;
}

BigInt<2> BigInt<2>::operator--(int) {  // Post-decremento
  BigInt<2> aux{1}, copia{*this};
  *this = *this - aux;
  return copia;  // devolvemos la copia del número antes de ser incrementado e
                 // incrementamos antes el original
}

// =============== CONVERSORES DE BINARIO A OTRAS BASES ===============
BigInt<2>::operator BigInt<2>() const { return *this; }

BigInt<2>::operator BigInt<8UL>() const {
  BigInt<2> aux{*this};
  std::string numero_convertido_aux{""};
  while (aux.numero_.size() % 3 != 0) {
    aux.numero_.emplace_back(0);
  }
  int valor_digito{0}, exponente{0};
  for (int i{0}; i < aux.numero_.size(); ++i) {
    valor_digito += (std::pow(2, exponente) * aux.numero_[i]);
    exponente++;
    if (exponente == 3) {  // Para pasar a octal se agrupa de 3 en 3 los bits y
                           // se resetea el exponente
      numero_convertido_aux += (std::to_string(valor_digito));
      valor_digito = 0;
      exponente = 0;
    }
  }
  std::reverse(
      numero_convertido_aux.begin(),
      numero_convertido_aux.end());  // Le damos la vuelta al string para que se
                                     // guarde al revés en el vector de bool
  BigInt<8> numero_convertido{numero_convertido_aux};
  return numero_convertido;
}

BigInt<2>::operator BigInt<10UL>() const {
  BigInt<2> aux{*this};
  long long valor_digito{0}, exponente{0};
  for (int i{0}; i < aux.numero_.size(); ++i) {
    if (i < aux.numero_.size() - 1) {
      valor_digito += (std::pow(2, exponente) * aux.numero_[i]);
      exponente++;
    } else {  // Cómo los números están en complemento a 2, para pasarlos a
              // decimal se resta la última potencia de 2
      valor_digito -= (std::pow(2, exponente) * aux.numero_[i]);
    }
  }
  std::string aux2{std::to_string(valor_digito)};
  BigInt<10> numero_convertido{aux2};
  return numero_convertido;
}

BigInt<2>::operator BigInt<16UL>() const {
  BigInt<2> aux{*this};
  std::string numero_convertido_aux{""};
  while (aux.numero_.size() % 4 != 0) {
    aux.numero_.emplace_back(0);
  }
  int valor_digito{0}, exponente{0};
  for (int i{0}; i < aux.numero_.size(); ++i) {
    valor_digito += (std::pow(2, exponente) * aux.numero_[i]);
    exponente++;
    if (exponente == 4) {  // Para pasar a hexadecimal se agrupa de 4 en 4 los
                           // bits y se resetea el exponente
      switch (valor_digito) {
        case 10:
          numero_convertido_aux.push_back('A');
          break;
        case 11:
          numero_convertido_aux.push_back('B');
          break;
        case 12:
          numero_convertido_aux.push_back('C');
          break;
        case 13:
          numero_convertido_aux.push_back('D');
          break;
        case 14:
          numero_convertido_aux.push_back('E');
          break;
        case 15:
          numero_convertido_aux.push_back('F');
          break;
        default:
          numero_convertido_aux += std::to_string(valor_digito);
          break;
      }
      valor_digito = 0;
      exponente = 0;
    }
  }
  std::reverse(
      numero_convertido_aux.begin(),
      numero_convertido_aux.end());  // Le damos la vuelta al string para que se
                                     // guarde al revés en el vector de bool
  BigInt<16> numero_convertido{numero_convertido_aux};
  return numero_convertido;
}

// Métodos de la clase Number
Number* BigInt<2>::add(const Number* numero) const {  
  BigInt<2> n = static_cast<BigInt<2>>(*numero);
  return reinterpret_cast<Number*>(new BigInt<2> {*this + n});
}

Number* BigInt<2>::subtract(const Number* numero) const { 
  BigInt<2> n = static_cast<BigInt<2>>(*numero);
  return reinterpret_cast<Number*>(new BigInt<2> {*this - n});
}

Number* BigInt<2>::multiply(const Number* numero) const { 
  BigInt<2> n = static_cast<BigInt<2>>(*numero);
  return reinterpret_cast<Number*>(new BigInt<2> {*this * n});
}

Number* BigInt<2>::divide(const Number* numero) const {
  BigInt<2> n = static_cast<BigInt<2>>(*numero);
  return reinterpret_cast<Number*>(new BigInt<2> {*this / n});
}

Number* BigInt<2>::module(const Number* numero) const { 
  BigInt<2> n = static_cast<BigInt<2>>(*numero);
  return reinterpret_cast<Number*>(new BigInt<2> {*this % n});
}

Number* BigInt<2>::pow(const Number* numero) const { 
  BigInt<2> n = static_cast<BigInt<2>>(*numero);
  return reinterpret_cast<Number*>(new BigInt<2> {Pow(*this, n)});
}

std::ostream& BigInt<2>::write(std::ostream& os) const {
  BigInt<2> numero{*this};
  for (unsigned long i{numero.numero_.size() - 1}; i != -1; --i) {
    os << numero.numero_[i];
  }
  return os;
}

std::istream& BigInt<2>::read(std::istream& is) {
  std::string aux_numero;
  is >> aux_numero;
  BigInt<2> numero_final{aux_numero};
  numero_.clear();
  *this = numero_final;
  return is;
}

// Método para obtener la base:
int BigInt<2>::GetBase() const {
  return 2;
}
