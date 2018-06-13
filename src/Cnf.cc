// -*- mode: c++; -*-

#include <vector>
#include <string>

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
vector<Var> Clause::vars()  const { return _vars; }

void Clause::addVar(Var v) { _vars.push_back(v); }
void Clause::addVar(Var v, Var b) { _vars.push_back(v); _vars.push_back(b); }
void Clause::addVar(Var v, Var b, Var n) { _vars.push_back(v); _vars.push_back(b); _vars.push_back(n); }

string Clause::print() const {
  string s;
  s.append("(");
  for(auto v : _vars) {s.append(to_string(v.num()) + " "); } s.pop_back();
  s.append(")");
  return s;
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
vector<Clause> Cnf::clauses() const { return _clauses; }

vector<Var> Cnf::variables() const {
  vector<Var> vars;
  for(auto c : _clauses) vars.insert(vars.end(), c.vars().begin(), c.vars().end());
  return vars;
}

void Cnf::addClause(Clause c) { _totalVar += c.vars().size(); _clauses.push_back(c); }
void Cnf::addClause(vector<Clause> cs) {
  for(auto const c : cs) _totalVar += c.vars().size();
  cs.insert(_clauses.end(), cs.begin(), cs.end());
}

string Cnf::print() const {
  string s(_name + " " + to_string(_numVar) + " ");
  for(auto const c : _clauses) s.append(c.print());
  return s;
}
