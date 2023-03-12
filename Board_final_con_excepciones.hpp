#ifndef BOARD_H
#define BOARD_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "big_int.hpp"
#include "number.hpp"

class Board {
 public:
  // Constructor
  Board(const std::string& fichero);
  // Método que empieza a leer todas las líneas del fichero, omitiendo la
  // primera
  void Start();

 private:
  std::map<std::string, Number*> variables_;
  std::ifstream fichero_;
};


Board::Board(const std::string& fichero) {
  fichero_.open(fichero.c_str(), std::ios::in);
}

// Método que empieza a leer todas las líneas del fichero y las procesa,
// metiendo los valores y evaluando las expresiones en RPN

void Board::Start() {
  Number* operando_1{NULL}; 
  Number* operando_2{NULL};  // Se definen los operandos para las operaciones y el
                  // resultado
  std::stack<Number*>
      pila;  // Se crea una pila para guardar los operandos y resultados
  std::ofstream
      archivo_salida;  // Este archivo no se usa, por lo que se puede eliminar
  std::string linea, palabra, identificador;  // Se definen variables para
                                              // procesar las líneas del fichero
  size_t base; // variable que nos va a servir para guardar la base
  std::istringstream
      linea_stream;  // Se crea un flujo de entrada para procesar las líneas
  std::ofstream fichero_salida;   // Se crea un archivo de salida para guardar
                                  // los resultados
  fichero_salida.open("fichero_salida.txt",
                      std::ios::out);  // Se abre el archivo de salida
  while (!fichero_.eof()) {  // Se itera sobre las líneas del fichero
    
    std::getline(fichero_, linea);
    linea_stream.str(linea);  // Se establece la línea actual como entrada para el flujo
    linea_stream >> palabra;  // Se lee el identificador de la variable
    identificador = palabra;  // Se guarda la primera palabra como identificador
                              // de la variable
    linea_stream >> palabra;  // Se lee la siguiente palabra, esto sería el "igual" (=)
    if (palabra == "=") { // Si encontramos un igual, es por que la línea será la declaración de un "Number*"
      // Después de esto, va la base así que la guardamos 
      linea_stream >> palabra;
      // Eliminamos la coma (',') que está al final de la base ej: "2," y lo almacenamos en la variable "base" de tipo size_t
      palabra.erase((palabra.size() - 1), 1);
      base = std::stoul(palabra);
      // Excepción de si la base es incorrecta 
        try {
          if (base != 2 && base != 8 && base != 10 && base != 16) throw(BigIntBaseNotImplemented("La base " + std::to_string(base) + " no está implementaada\n"));
        } catch(BigIntBaseNotImplemented excepcion) {
          Number* numero_base_no_implementada = Number::create(10, "0");
          pila.push(numero_base_no_implementada);
          std::cerr << excepcion.what() << '\n';
        }
    }
    while (linea_stream >> palabra) {  // Se itera sobre las palabras restantes de la línea
      if (variables_.find(palabra) != variables_.end()) {  // Si la palabra es una variable ya definida, se
                                                          // apila su valor en la pila
        pila.push(variables_[palabra]);
      } else if (palabra == "+") {  // Si la palabra es un operador de suma, se
                                    // sacan dos elementos de la pila, se suman,
                                    // y se apila el resultado
        try {
          operando_2 = pila.top();
        } catch(BigIntBadDigit excepcion) {
          Number* numero_base_no_implementada = Number::create(10, "0");
          pila.push(numero_base_no_implementada);
          std::cerr << excepcion.what() << '\n';
        }
        pila.pop();
        try {
          operando_1 = pila.top();
        } catch(BigIntBadDigit excepcion) {
          Number* numero_base_no_implementada = Number::create(10, "0");
          pila.push(numero_base_no_implementada);
          std::cerr << excepcion.what() << '\n';
        };
        pila.pop();
        Number* resultado = Number::create(operando_1->GetBase() , "0");  
        resultado = operando_1->add(operando_2);
        pila.push(resultado);
      } else if (palabra == "-") {  // Lo mismo para los otros operadores aritméticos
        operando_2 = pila.top();
        pila.pop();
        operando_1 = pila.top();
        pila.pop();
        Number* resultado = Number::create(operando_1->GetBase() , "0");
        resultado = operando_1->subtract(operando_2);
        pila.push(resultado);
      } else if (palabra == "*") {
        operando_2 = pila.top();
        pila.pop();
        operando_1 = pila.top();
        pila.pop();
        Number* resultado = Number::create(operando_1->GetBase() , "0");
        resultado = operando_1->multiply(operando_2);
        pila.push(resultado);
      } else if (palabra == "/") {
        operando_2 = pila.top();
        pila.pop();
        operando_1 = pila.top();
        pila.pop();
        Number* resultado = Number::create(operando_1->GetBase() , "0");
        try {
          resultado = operando_1->divide(operando_2);
        } catch(BigIntDivisionByZero excepcion) {
          std::cerr << excepcion.what() << '\n';
        }
        pila.push(resultado);
      } else if (palabra == "%") {
        operando_2 = pila.top();
        pila.pop();
        operando_1 = pila.top();
        pila.pop();
        Number* resultado = Number::create(operando_1->GetBase() , "0");
        try {
          resultado = operando_1->module(operando_2);
        } catch(BigIntDivisionByZero excepcion) {
          std::cerr << excepcion.what() << '\n';
        }
        pila.push(resultado);
      } else if (palabra == "^") {
        operando_2 = pila.top();
        pila.pop();
        operando_1 = pila.top();
        pila.pop();
        Number* resultado = Number::create(operando_1->GetBase() , "0");
        resultado = operando_1->pow(operando_2);
        pila.push(resultado);
      } else {
        // Excepción de si hay algún dígito erróneo
        if (base == 2 || base == 8 || base == 10 || base == 16) {
          Number* numero = Number::create(base, palabra);
          pila.push(numero);
        }
      }
    }
    variables_.insert(std::make_pair(identificador, pila.top()));
    pila.pop();
    linea_stream.clear();
  }
  // Generamos el fichero salida iterarando en el Board para guardar los valores
  auto it = variables_.begin();
  while (it != variables_.end()) {
    fichero_salida << it->first << " = " << it->second->GetBase() << ", " <<*it->second << '\n';
    it++;
  }
}

#endif
