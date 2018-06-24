// -*- mode: c++; -*-

#ifndef UTILS_H
#define UTILS_H

#include <vector>

#include "Var.h"

inline SATCirc::Var max_var(std::vector<SATCirc::Var> vv) {
  SATCirc::Var max = vv[0];

  for(size_t i = 1; i < vv.size(); i += 1)
    if(vv[i].num() > max.num()) max = vv[i];

  return max;
}


// // Grab new number
// class NumberGen {
// private:
//   NumberGen(){};

//   unsigned _number = 0;

// public:
//   static NumberGen& getInstance() {
//     static NumberGen instance;
//     return instance;
//   }

//   NumberGen(NumberGen const&)      = delete;
//   void operator=(NumberGen const&) = delete;

//   unsigned getNumber() { _number += 1; return _number; }
// };

#endif
