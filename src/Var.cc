// -*- mode: c++; -*-
#include <string>

#include "Var.h"

using std::string;
using std::to_string;
using namespace SATCirc;

// Constructors
Var::Var(int num) { _num = num; }

// Methods
int Var::sign() const { return (_num > 0) ? 1 : (-1); }
long int Var::num() const { return _num; }
string Var::print() const { return to_string(_num); }

void Var::changeSign() { _num *= (-1); }
void Var::changeNum(int num) { _num = num; }
void Var::bump(unsigned num) { (_num > 0) ? (_num += num) : (_num -= num); }
