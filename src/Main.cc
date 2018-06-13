#include <string>
#include <cstdio>
#include <iostream>
#include <climits>

#include "CircuitParser.h"
#include "CircuitScanner.h"

// #include "Var.h"
// #include "Cnf.h"
#include "Circuit.h"

using namespace std;
using namespace SATCirc;

// Transformar um Circuit em um CNF
int main(int argc, char **argv) {
  (void)argc;

  FILE *f = fopen(argv[1], "r");
  yyscan_t scanner;
  yylex_init(&scanner);
  yyset_in(f, scanner);

  char felipe[] = "felipe";

  Circuit *circ = nullptr;
  yyparse(scanner, &circ);

  cout << circ->name();
  
  yylex_destroy(scanner);
  

  // Var v1(1), v2(-2);
  // Clause c1(v1, v2);
  // Cnf t("TESTE", 2);
  // t.addClause(c1); t.addClause(c1);
  
  // cout << t.print() << endl;

  // Component AND("AND");
  // AND.addInput(v1);
  // AND.addInput(v2);
  // AND.addOutput(v2);

  // cout << AND.print() << endl;

  // Circuit lol("LOL");
  // lol.addComponent(AND);
  // lol.addComponent(AND);

  // cout << lol.print() << endl;
    
  return 0;
}













// #include "minisat/simp/SimpSolver.h"

// using namespace Minisat;

// int main(int argc, char** argv) {

//   SimpSolver S;
  
//   // Construir porta AND
//   // (~A \/ ~B \/ C)(A \/ ~C)(B \/ ~C)
//   Var vA = 0, vB = 1, vC = 2;
//   S.newVar(); S.newVar(); S.newVar();

//   // // Adicionar clausulas
//   S.addClause(~mkLit(vA), ~mkLit(vB), mkLit(vC));
//   S.addClause(mkLit(vA), mkLit(vC, true));
//   S.addClause(mkLit(vB), mkLit(vC, true));
//   // Quero saber se existe alguma forma de C ser falso
//   S.addClause(~mkLit(vC));

//   // Rodar MINISAT
//   Minisat::vec<Minisat::Lit> assumption;
//   bool res = S.solve(assumption);
//   if(res) std::cout << "SAT" << std::endl;
//   else std::cout << "UNSAT" << std::endl;

//   // Modelo
//   for(size_t s = 0; s < (unsigned)S.model.size(); s += 1)
//     std::cout << s << ": " << toInt(S.model[(int)s]) << std::endl;

//   std::cout << "vA: " << toInt(S.model[vA]) << std::endl;
  
//   return 0;
// }
