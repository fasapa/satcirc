// -*- mode: c++; -*-

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <vector>
#include <string>

#include "Var.h"

namespace SATCirc {

  class Component {
  private:
    std::string _name;
    std::vector<Var> _in, _out;

  public:
    Component(std::string name);
    Component(std::string name, std::vector<Var> in, std::vector<Var> out);

    std::string name() const;
    std::string print() const;
    std::vector<Var> inputs() const;
    std::vector<Var> outputs() const;

    void addInput(Var v);
    void addInput(std::vector<Var> v);
    void addOutput(Var v);
    void addOutput(std::vector<Var> v);
  };

  class Circuit {
  private:
    std::string _name;
    // std::vector<Var> _vars;
    std::vector<Component> _comp;

  public:
    // Constructors
    Circuit(std::string name);
    Circuit(std::string name, std::vector<Component> c);

    // Methods
    std::string name() const;
    std::string print() const;
    // std::vector<Var> vars() const;
    std::vector<Component> components() const;

    void addComponent(Component c);
    void addComponent(std::vector<Component> c);
  };
}

#endif
