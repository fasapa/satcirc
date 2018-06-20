// C Headers
#include <cstdlib>

// C++ Headers
#include <iostream>
using std::cerr; using std::endl;
#include <string>
using std::string;

#include "Env.h"
#include "Execucao.h"



// #include <string>
// #include <iostream>
// #include <vector>
// #include <cstdio>

// #include "CircuitParser.h"
// #include "CircuitScanner.h"

// #include "util.h"
// #include "Var.h"
// #include "Env.h"
// #include "Cnf.h"
// #include "Circuit.h"

namespace SATCirc {
  typedef enum modo_operacao_ {
    COMPILACAO, VERIFICACAO
  } OP;
}

// Transformar um Circuit em um CNF
int main(const int argc, const char *const argv[]) {

  if(argc <= 2) {
    cerr << "Uso errado. Correto: " << argv[0] << " modo input [output]" << endl;
    exit(EXIT_FAILURE);
  }
  
  // argv[0] = nome do programa
  // argv[1] = modo de operação
  // argv[2] = arquivo de input
  // argv[3] = arquivo de output (se necessário)
  // Modo de operação: (c) compilação, (v) verificação
  string op, file_in, file_out;
  op.append(argv[1]); file_in.append(argv[2]);
  if(argc < 4) file_out += ""; else file_out += argv[3];

  // Verificar falhas nas opções da linha de comando.
  if(op != "c" && op != "v") {  // Modo desconhecido
    cerr << "Modo de operação desconhecido: (c) compilação, (v) verificação" << endl;
    exit(EXIT_FAILURE);
  } else if(file_in.empty()) {  // Arquivo input não especificado.
    cerr << "Arquivo de input não especificado." << endl;
    exit(EXIT_FAILURE);
  }

  SATCirc::OP modo;
  if(op == "c") modo = SATCirc::COMPILACAO;
  else if(op == "v") modo = SATCirc::VERIFICACAO;
  else exit(EXIT_FAILURE);      // Não deve ser possível alcançar este else

  // Inicialização
  // Ambientes de CNF e variáveis
  SATCirc::EnvVar eVar;
  SATCirc::EnvCnf eCnf; SATCirc::inicializacao(&eCnf);

  // Execução
  switch(modo) {
  case SATCirc::COMPILACAO:
    return SATCirc::compilar(&eVar, &eCnf, file_in, file_out); break;
  case SATCirc::VERIFICACAO:
    return SATCirc::verificar(); break;
  } 
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
