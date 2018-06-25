// -*- mode: c++; -*-

#ifndef SOLVER_H
#define SOLVER_H

#include <string>

#include "Env.h"
#include "Cnf.h"

// Minisat
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wparentheses"
#pragma GCC diagnostic ignored "-Wliteral-suffix"
#pragma GCC diagnostic ignored "-Wpedantic"
#include "minisat/simp/SimpSolver.h"
#pragma GCC diagnostic pop

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
