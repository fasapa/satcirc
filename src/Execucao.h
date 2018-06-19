#ifndef EXECUCAO_H
#define EXECUCAO_H

#include <string>

#include "Env.h"
#include "Circuit.h"

namespace SATCirc {

  void inicializacao(EnvCnf *ec);
  int compilar(EnvVar *const eV, EnvCnf *const eC, const std::string in, const std::string out);
  int verificar();
}

#endif
