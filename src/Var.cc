// -*- mode: c++; -*-

#include <cstddef>
#include <string>

#include "Var.h"

using std::size_t;
using std::string;
using namespace SATCirc;

// Constructors
Var::Var(string name) {
  this->_hasName = true; this->_hasNumber = false;
  this->_name = name; this->_number = 0;
  this->_sign = VarSign::NONE;
}

Var::Var(size_t number, VarSign sign) {
  this->_hasName = false; this->_hasNumber = true;
  this->_name = ""; this->_number = number;
  this->_sign = sign;
}

Var::Var(string name, size_t number, VarSign sign) {
  this->_hasName = this->_hasNumber = true;
  this->_name = name; this->_number = number;
  this->_sign = sign;
}

// Methods
size_t  Var::number()    { return this->_number;    }
string  Var::name()      { return this->_name;      }
bool    Var::hasName()   { return this->_hasName;   }
bool    Var::hasNumber() { return this->_hasNumber; }
VarSign Var::sign()      { return this->_sign;      }

void Var::assocNumber(size_t number, VarSign sign) {
  this->_hasNumber = true;
  this->_hasNumber = number;
  this->_sign = sign;
}

void Var::assocName(string name) {
  this->_hasName = true;
  this->_name = name;
}
