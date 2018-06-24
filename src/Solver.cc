// -*- mode: c++; -*-
#include <iostream>
#include <vector>

#include "util.h"
#include "Var.h"
#include "Cnf.h"
#include "Env.h"
#include "Circuit.h"
#include "Solver.h"
#include "readverify.h"

// MiniSat
#include "minisat/simp/SimpSolver.h"

using std::vector; using namespace std;
using namespace SATCirc;

Solver::Solver(Cnf cnf) { _cnf = cnf; }

Minisat::SimpSolver *initSolver(const unsigned num_var) {
  Minisat::SimpSolver *s = new Minisat::SimpSolver();
  // Contagem variáveis necessárias
  for(size_t i = 0; i < num_var; i += 1) s->newVar();
  return s;
}

void clauseToVecLit(Clause cl, Minisat::vec<Minisat::Lit> *vl) {
  vector<Var> vars = cl.vars();
  for(size_t j = 0; j < vars.size(); j += 1) {
    if(vars[j].sign() > 0)
      vl->push(Minisat::mkLit(vars[j].num(), false));
    else
      vl->push(Minisat::mkLit(vars[j].num(), true));
  }
}

void modelToVecLit(Minisat::vec<Minisat::lbool> model, Minisat::vec<Minisat::Lit> *vl,
                   unsigned max_var) {
  for(size_t i = 1; i <= max_var; i += 1) {
    int res = Minisat::toInt(model[(int)i]);
    if(res == 1)
      vl->push(Minisat::mkLit(i));
    else if(res == 0)
      vl->push(~Minisat::mkLit(i));
  }
}

void Solver::solve(EnvVar env, string restr) {

  _S = initSolver(max_var(_cnf.variables()).num() + 1);

  // Restrições do sistema
  vector<Clause> cls = _cnf.clauses();
  for(size_t i = 0; i < cls.size(); i += 1) {
    // cout << "CLS: " << cls[i].print() << endl;

    Minisat::vec<Minisat::Lit> l;
    clauseToVecLit(cls[i], &l);

    _S->addClause_(l);
  }

  // Restrições usuario
  vector< vector<string> > clv = readVerify(restr);

  // Clausula
  if(clv[0].size() != 0) {
    for(size_t i = 0; i < clv.size(); i += 1) {
      vector<string> cl = clv[i];
      Minisat::vec<Minisat::Lit> ll;

      // Variável
      for(size_t j = 0; j < cl.size(); j += 1) {
        string varStr = cl[j];
        if(varStr[0] == '-') {
          varStr.erase(0,1);
          Var v = env.get(varStr);
          ll.push(~Minisat::mkLit(v.num()));
        } else {
          Var v = env.get(varStr);
          ll.push(Minisat::mkLit(v.num()));
        }
      }

      _S->addClause(ll);
    }
  }

  // Rodar Minisat
  Minisat::vec<Minisat::Lit> ass;
  bool res = _S->solve(ass);

  if(res) {
    cout << "SAT" << endl;

    // Imprimir modelo
    for(size_t i = 1; i <= _cnf.maxVal(); i += 1) {
      int res = Minisat::toInt(_S->model[(int)i]);
      res = (res - 1)*(-1);
      cout << env.get(Var((int)i)) + "(" << res << ") ";
    }

    cout << endl;
  } else
    cout << "UNSAT" << endl;

  delete _S;
}
