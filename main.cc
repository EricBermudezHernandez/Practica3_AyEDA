#include "big_int.hpp"
#include "board.hpp"
#include "bigint_exceptions.hpp"
#include "number.hpp"

int main(int argc, char* argv[]) {
  std::string nombre_fichero(argv[1]);
  Board pizarra{nombre_fichero};
  pizarra.Start();
}
