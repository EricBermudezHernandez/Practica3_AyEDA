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

class BigIntException : public std::exception { 
 public:  
  // Constructor
  BigIntException() : std::exception() {}
};

#endif