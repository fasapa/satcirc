// C Headers
#include <cstdlib>
#include <cstdio>
#include <cassert>

// C++ Headers
#include <iostream>
#include <vector>
#include <string>

#include "Execucao.h"
#include "Var.h"
#include "Env.h"
#include "Circuit.h"
#include "util.h"

// Parser & Lexer
#include "CircuitParser.h"
#include "CircuitScanner.h"

using std::string;
using std::cerr; using std::cout; using std::endl;
using namespace SATCirc;

void SATCirc::inicializacao(EnvCnf *ec) {
  assert(ec != NULL);

  // Componentes internos
  Cnf _and("AND", 3);
  _and.addClause(Clause(Var(-1), Var(-2), Var(3)));
  _and.addClause(Clause(Var(1), Var(-3)));
  _and.addClause(Clause(Var(2), Var(-3)));

  Cnf _or("OR", 3);
  _or.addClause(Clause(Var(1), Var(2), Var(-3)));
  _or.addClause(Clause(Var(-1), Var(3)));
  _or.addClause(Clause(Var(-2), Var(3)));

  Cnf _not("NOT", 2);
  _not.addClause(Clause(Var(-1), Var(-2)));
  _not.addClause(Clause(Var(1), Var(2)));

  ec->insert(_and.name(), _and);
  ec->insert( _or.name(),  _or);
  ec->insert(_not.name(), _not);

}

int SATCirc::compilar(EnvVar *const eV, EnvCnf *const eC, const string fin, const string fout) {
  (void)fout;

  // Abrir arquivo de input
  FILE *fi = fopen(fin.c_str(), "r");
  if(fi == NULL) {
    cerr << "Arquivo " << fin << " inexistente." << endl;
    return EXIT_FAILURE;
  }

  // Scanner e Parser
  yyscan_t sc;
  yylex_init(&sc); yyset_in(fi, sc);

  Circuit *circ = nullptr;
  yyparse(sc, &circ, eV);
  yylex_destroy(sc);

  // Construir CNF final
  Cnf outCnf(circ->name(), circ->size());

  vector<Component> comp = circ->components();
  unsigned bump = 0;

  // Para cada componente realizar substituição variáveis
  for(size_t i = 0; i < comp.size(); i += 1) {
    Component c = comp[i];
    Cnf cnf = eC->get(c.name()); // Buscar CNF da componente
    // CASO EM QUE CNF NÃO ESTÁ DISPONÍVEL

    // Input e output da componente
    vector<Var> in = c.inputs(), out = c.outputs();
    vector<Var> vars(in); vars.insert(vars.end(), out.begin(), out.end());

    // Bump valores das variáveis para incluir no CNF
    if(cnf.bump(max_var(vars).num()-cnf.maxVal()+bump, cnf.maxVal()))
      bump += 1;

    // Atualiza variáveis
    cnf.change(vars);

    // Adiciona as clausulas ao cnf final
    outCnf.addClause(cnf.clauses());
  }

  //Escreve CNF resultante.
  FILE *fo = NULL;
  if(fout == "stdout" || fout == "") fo = stdout;
  else fo = fopen(fout.c_str(), "w");

  fprintf(fo, "%s", outCnf.print().c_str());
  return EXIT_SUCCESS;
}

int SATCirc::verificar() { return EXIT_SUCCESS; }
