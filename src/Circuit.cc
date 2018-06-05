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
Component::Component(string name) { this->_name = name; }
Component::Component(string name, vector<Var> in, vector<Var> out) {
  this->_name = name; this->_inputs = in; this->_outputs = out;
}

// Methods
string      Component::name()    const { return this->_name;    }
vector<Var> Component::inputs()  const { return this->_inputs;  }
vector<Var> Component::outputs() const { return this->_outputs; }

void Component::addInput(Var v)  { this->_inputs.push_back(v);  }
void Component::addOutput(Var v) { this->_outputs.push_back(v); }

void Component::addInput(vector<Var> v)
{ this->_inputs.insert(_inputs.begin(), v.begin(), v.end()); }
void Component::addOutput(vector<Var> v)
{ this->_outputs.insert(_outputs.begin(), v.begin(), v.end()); }

// Circuit
// Constructors
Circuit::Circuit(string name) { this->_name = name; }
Circuit::Circuit(string name, vector<Var> in, vector<Var> out, vector<Component> c) {
  this->_name = name; this->_input = in; this->_output = out; this->_components = c;
}

// Methods
bool              Circuit::empty()      const { return this->_components.empty(); }
string            Circuit::name()       const { return this->_name;               }
vector<Var>       Circuit::inputs()     const { return this->_input;              }
vector<Var>       Circuit::outputs()    const { return this->_output;             }
vector<Var>       Circuit::internal()   const { return this->_internal;           }
vector<Component> Circuit::components() const { return this->_components;         }

void Circuit::addInput(Var v)           { this->_input.push_back(v);      }
void Circuit::addOutput(Var v)          { this->_output.push_back(v);     }
void Circuit::addComponent(Component c) { this->_components.push_back(c); }

void Circuit::addInput(vector<Var> v)  { this->_input.insert(_input.end(), v.begin(), v.end());   }
void Circuit::addOutput(vector<Var> v) { this->_output.insert(_output.end(), v.begin(), v.end()); }
void Circuit::addComponent(vector<Component> c) {
  this->_components.insert(_components.end(), c.begin(), c.end());
}
