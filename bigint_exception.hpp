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

#endif
