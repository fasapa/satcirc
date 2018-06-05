// -*- mode: c++; -*-

#include <vector>

#include "Var.h"
#include "Cnf.h"

using std::vector;
using namespace SATCirc;

// Clause
// Constructors
Clause::Clause(Var v) {
  this->_variables.push_back(v);
}

Clause::Clause(Var v, Var b) {
  this->_variables.push_back(v);
  this->_variables.push_back(b);
}

Clause::Clause(Var v, Var b, Var n) {
  this->_variables.push_back(v);
  this->_variables.push_back(b);
  this->_variables.push_back(n);
}

Clause::Clause(vector<Var> vars) {
  this->_variables.insert(_variables.end(), vars.begin(), vars.end());
}

// Methods
bool        Clause::empty()     const { return this->_variables.empty(); }
vector<Var> Clause::variables() const { return this->_variables;         }

void Clause::addVar(Var v) { this->_variables.push_back(v); }

void Clause::addVar(Var v, Var b) {
  this->_variables.push_back(v);
  this->_variables.push_back(b);
}

void Clause::addVar(Var v, Var b, Var n) {
  this->_variables.push_back(v);
  this->_variables.push_back(b);
  this->_variables.push_back(n);
}

void Clause::addVar(vector<Var> vars) {
  this->_variables.insert(_variables.end(), vars.begin(), vars.end());
}
