// -*- mode: c++; -*-

#include <cstddef>
#include <string>

#include "Var.h"

using std::size_t;
using std::string;
using namespace SATCirc;

// Constructors
Var::Var(string name) {
  _hasName = true; _hasNumber = false;
  _name = name; _number = 0;
  _sign = VarSign::NONE;
}

Var::Var(size_t number, VarSign sign) {
  _hasName = false; _hasNumber = true;
  _name = ""; _number = number;
  _sign = sign;
}

Var::Var(string name, size_t number, VarSign sign) {
  _hasName = _hasNumber = true;
  _name = name; _number = number;
  _sign = sign;
}

// Methods
size_t  Var::number()    const { return _number;    }
string  Var::name()      const { return _name;      }
bool    Var::hasName()   const { return _hasName;   }
bool    Var::hasNumber() const { return _hasNumber; }
VarSign Var::sign()      const { return _sign;      }

void Var::assocNumber(size_t number, VarSign sign) {
  _hasNumber = true;
  _hasNumber = number;
  _sign = sign;
}

void Var::assocName(string name) {
  _hasName = true;
  _name = name;
}
