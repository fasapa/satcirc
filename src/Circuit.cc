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
  _name = name; _inputs = in; _outputs = out;
}

// Methods
string      Component::name()    const { return _name;    }
vector<Var> Component::inputs()  const { return _inputs;  }
vector<Var> Component::outputs() const { return _outputs; }

void Component::addInput(Var v)  { _inputs.push_back(v);  }
void Component::addOutput(Var v) { _outputs.push_back(v); }

void Component::addInput(vector<Var> v)  { _inputs.insert(_inputs.begin(), v.begin(), v.end()); }
void Component::addOutput(vector<Var> v) { _outputs.insert(_outputs.begin(), v.begin(), v.end()); }

// Circuit
// Constructors
Circuit::Circuit(string name) { _name = name; }
Circuit::Circuit(string name, vector<Var> in, vector<Var> out, vector<Component> c) {
  _name = name; _input = in; _output = out; _components = c;
}

// Methods
bool              Circuit::empty()      const { return _components.empty(); }
string            Circuit::name()       const { return _name;               }
vector<Var>       Circuit::inputs()     const { return _input;              }
vector<Var>       Circuit::outputs()    const { return _output;             }
vector<Var>       Circuit::internal()   const { return _internal;           }
vector<Component> Circuit::components() const { return _components;         }

void Circuit::addInput(Var v)           { _input.push_back(v);      }
void Circuit::addOutput(Var v)          { _output.push_back(v);     }
void Circuit::addComponent(Component c) { _components.push_back(c); }

void Circuit::addInput(vector<Var> v)  { _input.insert(_input.end(), v.begin(), v.end());   }
void Circuit::addOutput(vector<Var> v) { _output.insert(_output.end(), v.begin(), v.end()); }
void Circuit::addComponent(vector<Component> c) {
  _components.insert(_components.end(), c.begin(), c.end());
}
