// -*- mode: c++; -*-

#ifndef SOLVER_H
#define SOLVER_H

#include <string>

#include "Env.h"
#include "Cnf.h"

// Minisat
#include "minisat/simp/SimpSolver.h"

namespace SATCirc {

  class Solver {
  private:
    Minisat::SimpSolver *_S;
    Cnf _cnf;

  public:
    Solver(Cnf cnf);

    // Methdos
    void solve(EnvVar e, std::string restr);
  };

}

#endif
