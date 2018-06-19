// -*- mode: c++; -*-

#include <vector>
#include <string>

#include "Var.h"
#include "Circuit.h"

using std::vector;
using std::string;
using namespace SATCirc;

// Components
// Constructors
Component::Component(string name) { _name = name; }
Component::Component(string name, vector<Var> in, vector<Var> out) {
  _name = name; _in = in; _out = out;
}

// Methods
string      Component::name()    const { return _name; }
vector<Var> Component::inputs()  const { return _in;   }
vector<Var> Component::outputs() const { return _out;  }
string      Component::print() const {
  string s;
  for(auto const i :_in) { s.append(i.print() + " "); }
  s.append(_name + " ");
  for(auto const o :_out) { s.append(o.print() + " "); } s.pop_back();
  return s;
}

void Component::addInput(Var v)  { _in.push_back(v);  }
void Component::addOutput(Var v) { _out.push_back(v); }

void Component::addInput(vector<Var> v)  { _in.insert(_in.begin(), v.begin(), v.end()); }
void Component::addOutput(vector<Var> v) { _out.insert(_out.begin(), v.begin(), v.end()); }

// Circuit
// Constructors
Circuit::Circuit(string name) { _name = name; }
Circuit::Circuit(string name, vector<Component> c, unsigned size) {
  _name = name; _comp = c; _vars = size;
}

// Methods
string Circuit::name() const { return _name; }
string Circuit::print() const {
  string s(_name + " { ");
  for(auto const c : _comp) s.append(c.print() + "; ");
  s.append("}");
  return s;
}

unsigned Circuit::size() const { return _vars; }
// vector<Var>       Circuit::vars()       const { return _vars; }
vector<Component> Circuit::components() const { return _comp; }

void Circuit::addComponent(Component c) { _comp.push_back(c); }
void Circuit::addComponent(vector<Component> c) { _comp.insert(_comp.end(), c.begin(), c.end()); }
