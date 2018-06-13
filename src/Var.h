// -*- mode: c++; -*-

#ifndef VAR_H
#define VAR_H

#include <string>

namespace SATCirc {

  // Var is a positive number with a sign.
  class Var {
  private:
    long int _num;

  public:
    // Constructors
    Var(int num);

    // Methods
    int sign() const;
    long int num() const;
    std::string print() const;
    void changeSign();
    void changeNum(int num);
    void bump(unsigned num);
  };
}

#endif
