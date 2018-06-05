// -*- mode: c++; -*-

#ifndef VAR_H
#define VAR_H

#include <cstddef>
#include <string>

namespace SATCirc {

  // Variable sign
  enum class VarSign { PLUS, MINUS, NONE };

  // Every Var have a number and a name associated
  class Var {
  private:
    std::size_t _number;
    std::string _name;
    VarSign _sign;
    bool _hasNumber;
    bool _hasName;

  public:
    // Constructors
    Var(std::string name);                                    // Var without number
    Var(std::size_t number, VarSign sing = VarSign::PLUS);    // Var without name
    Var(std::string name, std::size_t number, VarSign sign = VarSign::PLUS);

    // Methods
    std::size_t number();
    std::string name();
    VarSign sign();
    bool hasName();
    bool hasNumber();
    void assocNumber(std::size_t number, VarSign sign = VarSign::PLUS);
    void assocName(std::string name);
  };
}

#endif
