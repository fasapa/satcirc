// -*- mode: c++; -*-

#ifndef CNF_H
#define CNF_H

#include <vector>

#include "Var.h"

namespace SATCirc {

  // Clause is just a list of variables
  class Clause {
  private:
    std::vector<Var> _variables;

  public:
    // Constructors
    Clause() = default;                   // empty clause
    Clause(Var v);              // unit clause
    Clause(Var v, Var b);
    Clause(Var v, Var b, Var n);   // Ternary clause
    Clause(std::vector<Var> vars); // n-ary clause

    // Methods
    bool empty() const;
    std::vector<Var> variables() const;
    void addVar(Var v);
    void addVar(Var v, Var b);
    void addVar(Var v, Var b, Var n);
    void addVar(std::vector<Var> vars);
  };

  class CNF {
  private:
    // CNF is a vector of clauses.
    std::vector<Clause> _clauses;

  public:
    // Constructors
    CNF();                      // empty CNF
    CNF(std::vector<Clause> clauses);

    // Methods
    bool empty() const;
    std::vector<Clause> clauses() const;
    std::vector<Var> variables() const;
    void addClause(Clause c);
    void addClause(std::vector<Clause> c);
  };
}

#endif
