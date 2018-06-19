// -*- mode: c++; -*-

#ifndef SOLVER_H
#define SOLVER_H

#include "Cnf.h"


namespace SATCirc {

  class Solver {

    // Methdos
    void addClause(Clause v);
    void solve();
  };



}

#endif
