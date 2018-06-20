// -*- mode: c++; -*-

#ifndef ENV_H
#define ENV_H

#include <string>
#include <map>

#include "Var.h"
#include "Cnf.h"

namespace SATCirc {

  class EnvVar {
  private:
    // Bimap
    std::map<std::string, Var> _sv;
    std::map<Var, std::string> _vs;

  public:
    EnvVar() = default;

    void insert(std::string s, Var v);
    bool in(std::string s);
    Var get(std::string s);
    unsigned size();
    std::string get(Var v);
  };

  class EnvCnf {
  private:
    std::map<std::string, Cnf> _sc;

  public:
    EnvCnf() = default;

    void insert(std::string, Cnf c);
    bool in(std::string s);
    Cnf get(std::string s);
  };
}

#endif
