// -*- mode: c++; -*-
#include <string>

#include "Var.h"

using std::string;
using std::to_string;
using namespace SATCirc;

static long int value = 1;

// Constructors
Var::Var() { _num = 0; }
Var::Var(bool sign) { if(sign) _num = value; else _num = value*(-1); value += 1; }
Var::Var(int num) { _num = num; }

// Methods
int Var::sign() const { return (_num > 0) ? 1 : (-1); }
unsigned Var::num() const { if(_num > 0) return _num; else return _num*(-1); }
string Var::print() const { return to_string(_num); }

void Var::changeSign() { _num *= (-1); }
void Var::changeNum(int num) { if(_num > 0) _num = num; else _num = num*(-1); }
void Var::bump(unsigned num) { (_num > 0) ? (_num += num) : (_num -= num); }

bool Var::operator<(const Var &v) const {
  return v.num() < _num;
}
