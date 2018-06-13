// -*- mode: c++; -*-

#ifndef CNF_H
#define CNF_H

#include <vector>
#include <string>

#include "Var.h"

namespace SATCirc {

  // Clause is just a list of variables
  class Clause {
  private:
    std::vector<Var> _vars;

  public:
    // Constructors
    Clause() = default;
    Clause(Var v);              // unit clause
    Clause(Var v, Var b);
    Clause(Var v, Var b, Var n);   // Ternary clause

    // Methods
    std::vector<Var> vars() const;
    void addVar(Var v);
    void addVar(Var v, Var b);
    void addVar(Var v, Var b, Var n);

    std::string print() const;
  };

  class Cnf {
  private:
    // CNF is a vector of clauses.
    std::vector<Clause> _clauses;
    std::string _name;
    std::size_t _numVar;        // Variables related to input and output
    std::size_t _totalVar;      // numVar plus internal variables

  public:
    // Constructors
    Cnf(std::string name, unsigned numVar);
    Cnf(std::string name, unsigned numVar, std::vector<Clause> clauses);

    // Methods
    // Retornar referência?
    std::vector<Clause> clauses() const;
    // Retornar referência?
    std::vector<Var> variables() const;
    void addClause(Clause c);
    void addClause(std::vector<Clause> c);
    std::string print() const;
  };
}

#endif
