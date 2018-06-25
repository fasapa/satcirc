// -*- mode: c++; -*-x

#ifndef EXECUCAO_H
#define EXECUCAO_H

#include <string>

#include "Env.h"
#include "Cnf.h"
#include "Circuit.h"

namespace SATCirc {
  void inicializacao(EnvCnf *ec);
  int compilar(const std::string in);
  int verificar(const std::string in, const std::string ver);
}

#endif
