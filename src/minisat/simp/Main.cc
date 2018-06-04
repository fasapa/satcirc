#include <iostream>

#include "simp/SimpSolver.h"

using namespace Minisat;

int main(int argc, char** argv) {

  SimpSolver S;
  
  // Construir porta AND
  // (~A \/ ~B \/ C)(A \/ ~C)(B \/ ~C)
  Var vA = 0, vB = 1, vC = 2;
  S.newVar(); S.newVar(); S.newVar();

  // // Adicionar clausulas
  S.addClause(~mkLit(vA), ~mkLit(vB), mkLit(vC));
  S.addClause(mkLit(vA), mkLit(vC, true));
  S.addClause(mkLit(vB), mkLit(vC, true));
  // Quero saber se existe alguma forma de C ser falso
  S.addClause(~mkLit(vC));

  // Rodar MINISAT
  Minisat::vec<Minisat::Lit> assumption;
  bool res = S.solve(assumption);
  if(res) std::cout << "SAT" << std::endl;
  else std::cout << "UNSAT" << std::endl;

  // Modelo
  for(size_t s = 0; s < (unsigned)S.model.size(); s += 1)
    std::cout << s << ": " << toInt(S.model[(int)s]) << std::endl;
  
  return 0;
}
