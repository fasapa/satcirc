// -*- mode: c++; -*-

// C Headers
#include <cstdlib>
#include <cstdio>
#include <cassert>

// C++ Headers
#include <iostream>
#include <vector>
#include <string>

#include "util.h"
#include "Execucao.h"
#include "Var.h"
#include "Env.h"
#include "Circuit.h"
#include "Solver.h"

// Parser & Lexer
#include "CircuitParser.h"
#include "CircuitScanner.h"
#include "CnfParser.h"
#include "CnfScanner.h"

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

int readCircuit(const std::string fin, EnvVar *const e, Circuit **c) {

  // Abrir arquivo
  FILE *fi = fopen(fin.c_str(), "r");
  if(fi == NULL) {
    cerr << "Arquivo " << fin << " inexistente." << endl;
    return EXIT_FAILURE;
  }

  yyscan_t s;
  circ_yylex_init(&s); circ_yyset_in(fi, s);
  circ_yyparse(s, c, e);
  circ_yylex_destroy(s);

  return EXIT_SUCCESS;
}

int readCnf(const std::string fin, Cnf **c) {

  // Abrir arquivo
  FILE *fi = fopen(fin.c_str(), "r");
  if(fi == NULL) {
    cerr << "Arquivo " << fin << " inexistente." << endl;
    return EXIT_FAILURE;
  }

  yyscan_t s;
  cnf_yylex_init(&s); cnf_yyset_in(fi, s);
  cnf_yyparse(s, c);
  cnf_yylex_destroy(s);

  return EXIT_SUCCESS;
}

int
SATCirc::compilar(const string fin) {

  // Inicialização
  EnvVar eV; EnvCnf eC; inicializacao(&eC);

  // Ler circuito
  Circuit *circ = nullptr;
  if(readCircuit(fin, &eV, &circ)) return EXIT_FAILURE;

  // Construir CNF final
  Cnf outCnf(circ->name(), circ->size());

  vector<Component> comp = circ->components();
  unsigned bump = 0;

  // Para cada componente realizar substituição variáveis
  for(size_t i = 0; i < comp.size(); i += 1) {
    Component c = comp[i];

    // Verificar se a componente existe
    Cnf *cnf = nullptr;
    if(eC.in(c.name())) {
      cnf = new Cnf();
      *cnf = eC.get(c.name());
    } else {
      string cnf_file(c.name() + ".cnf");
      if(readCnf(cnf_file, &cnf)) return EXIT_FAILURE;
      eC.insert(cnf->name(), *cnf);
    }

    // Input e output da componente
    vector<Var> in = c.inputs(), out = c.outputs();
    vector<Var> vars(in); vars.insert(vars.end(), out.begin(), out.end());

    // Bump valores das variáveis para incluir no CNF
    if(cnf->bump(max_var(vars).num()-cnf->maxVal()+bump, cnf->maxVal()))
      bump += 1;

    // Atualiza variáveis
    cnf->change(vars);

    // Adiciona as clausulas ao cnf final
    outCnf.addClause(cnf->clauses());
  }

  fprintf(stdout, "%s", outCnf.print().c_str());
  return EXIT_SUCCESS;
}

int SATCirc::verificar(const string file_in, const string file_ver) {

  Circuit *circ = nullptr;
  EnvVar eV;

  // Ler circuito
  if(readCircuit(file_in, &eV, &circ)) return EXIT_FAILURE;

  // Ler cnf
  Cnf *cnf = nullptr;
  if(readCnf((circ->name() + ".cnf"), &cnf)) return EXIT_FAILURE;

  // Executar busca de solução
  Solver s(*cnf); s.solve(eV, file_ver);

  return EXIT_SUCCESS;
}
