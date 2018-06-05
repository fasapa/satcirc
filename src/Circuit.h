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
    std::vector<Var> _inputs, _outputs;
    // CNF?

  public:
    Component(std::string name);
    Component(std::string name, std::vector<Var> in, std::vector<Var> out);

    std::string name() const;
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
    std::vector<Var> _input, _output, _internal;
    std::vector<Component> _components;

  public:
    // Constructors
    Circuit(std::string name);                   // empty circuit
    Circuit(std::string name, std::vector<Var> in, std::vector<Var> out, std::vector<Component> c);

    // Methods
    bool empty() const;
    std::string name() const;
    std::vector<Var> inputs() const;
    std::vector<Var> outputs() const;
    std::vector<Var> internal() const;
    std::vector<Component> components() const;

    void addInput(Var v);
    void addInput(std::vector<Var> v);
    void addOutput(Var v);
    void addOutput(std::vector<Var> v);
    // void addInternal(Var v);
    // void addInternal(std::vector<Var> v);

    void addComponent(Component c);
    void addComponent(std::vector<Component> c);
  };
}

#endif
