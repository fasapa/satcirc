#ifndef UTILS_H
#define UTILS_H

#include <vector>

#include "Var.h"

inline SATCirc::Var max_var(std::vector<SATCirc::Var> vv) {
  SATCirc::Var max;
  for(auto const v : vv) {
    if(v.num() > max.num()) max = v;
  }

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
