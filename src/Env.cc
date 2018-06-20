// -*- mode: c++; -*-

#include <string>
#include <map>

#include "Var.h"
#include "Cnf.h"
#include "Env.h"

using std::string;
using std::map;
using std::make_pair;
using namespace SATCirc;

// Variable environment
void EnvVar::insert(string s, Var v) {
  _sv.insert(make_pair(s, v));
  _vs.insert(make_pair(v, s));
}

bool EnvVar::in(string s) { return (_sv.find(s) != _sv.end()); }
Var EnvVar::get(string s) { return _sv[s]; }
string EnvVar::get(Var v) { return _vs[v]; }
unsigned EnvVar::size() { return _sv.size(); }

// Cnf environment
void EnvCnf::insert(string s, Cnf c) { _sc.insert(make_pair(s, c)); }
Cnf EnvCnf::get(string s) { return _sc[s]; }
