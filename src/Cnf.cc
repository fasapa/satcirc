// -*- mode: c++; -*-
#include <iostream>
#include <vector>
#include <string>

#include "util.h"
#include "Var.h"
#include "Cnf.h"

using std::string;
using std::to_string;
using std::vector;
using namespace SATCirc;

// Clause
// Constructors
Clause::Clause(Var v) { _vars.push_back(v); }
Clause::Clause(Var v, Var b) { _vars.push_back(v); _vars.push_back(b); }
Clause::Clause(Var v, Var b, Var n) { _vars.push_back(v); _vars.push_back(b); _vars.push_back(n); }

// Methods
vector<Var> Clause::vars() const { return _vars; }

void Clause::addVar(Var v) { _vars.push_back(v); }
void Clause::addVar(Var v, Var b) { _vars.push_back(v); _vars.push_back(b); }
void Clause::addVar(Var v, Var b, Var n) { _vars.push_back(v); _vars.push_back(b); _vars.push_back(n); }

string Clause::print() const {
  string s;
  s.append("(");
  for(auto v : _vars) {s.append(v.print() + " "); } s.pop_back();
  s.append(")");
  return s;
}

void Clause::change(vector<Var> nv) {
  Var max = max_var(nv);
  for(size_t i = 0; i < _vars.size(); i += 1) {
    if(_vars[i].num() <= max.num())
      _vars[i].changeNum(nv[_vars[i].num()-1].num());
  }
}

bool Clause::bump(unsigned b, unsigned min) {
  bool bumped = false;

  for(size_t i = 0; i < _vars.size(); i += 1) {
    if(_vars[i].num() > min) {
      bumped = true;
      _vars[i].changeNum(_vars[i].num() + b);
    }
  }

  return bumped;
}

// CNF
// Constructors
Cnf::Cnf(string name, unsigned numVar) {
  _name = name; _numVar = numVar; _totalVar = 0;
}

Cnf::Cnf(string name, unsigned numVar, vector<Clause> clauses) {
  _name = name; _numVar = numVar; _totalVar = 0; _clauses = clauses;
  // Count all variables from clauses
  for(auto const c : _clauses) _totalVar += c.vars().size();
}

// Methods
std::string Cnf::name() const { return _name; }

vector<Clause> Cnf::clauses() const { return _clauses; }

vector<Var> Cnf::variables() const {
  vector<Var> vars;

  // Itera em todas as clausulas coletando as variáveis (pode conter repetição)
  for(size_t i = 0; i < _clauses.size(); i += 1) {
    vector<Var> cv = _clauses[i].vars();

    for(size_t j = 0; j < cv.size(); j += 1) {
      vars.push_back(cv[j]);
    }
  }

  return vars;
}

void Cnf::addClause(Clause c) { _totalVar += c.vars().size(); _clauses.push_back(c); }
void Cnf::addClause(vector<Clause> cs) {
  for(auto const c : cs) { _clauses.push_back(c); }
}

string Cnf::print() const {
  string s(_name + " " + to_string(_numVar) + " ");
  for(auto const c : _clauses) s.append(c.print());
  return s;
}

void Cnf::change(vector<Var> v) {
  for(size_t i = 0; i < _clauses.size(); i += 1) {
    _clauses[i].change(v);
  }
}

bool Cnf::bump(unsigned b, unsigned min) {
  unsigned bumped = 0;

  for(size_t i = 0; i < _clauses.size(); i += 1) {
    if(_clauses[i].bump(b, min)) bumped += 1;
  }

  return (bumped > 0);
}

unsigned Cnf::maxVal() const { return _numVar; }
