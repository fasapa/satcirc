// C Headers
#include <cstdlib>

// C++ Headers
#include <iostream>
using std::cerr; using std::endl;
#include <string>
using std::string;

#include "Env.h"
#include "Execucao.h"

namespace SATCirc {
  typedef enum modo_operacao_ {
    COMPILACAO, VERIFICACAO
  } OP;
}

// Transformar um Circuit em um CNF
int main(const int argc, const char *const argv[]) {

  if(argc <= 2) {
    cerr << "Uso errado. Correto: " << argv[0] << " c input (compilação)" << endl;
    cerr << " v input restricoes (verificação)" << endl;
    exit(EXIT_FAILURE);
  }
  
  // argv[0] = nome do programa
  // argv[1] = modo de operação
  // argv[2] = arquivo de input
  // argv[3] = arquivo de verificação
  // Modo de operação: (c) compilação, (v) verificação
  string op, file_in, file_ver;
  op.append(argv[1]); file_in.append(argv[2]);
  
  // Verificar falhas nas opções da linha de comando.
  if(op != "c" && op != "v") {  // Modo desconhecido
    cerr << "Modo de operação desconhecido: (c) compilação, (v) verificação" << endl;
    return EXIT_FAILURE;
  } else if(file_in.empty()) {  // Arquivo input não especificado.
    cerr << "Arquivo de input não especificado." << endl;
    return EXIT_FAILURE;
  }

  SATCirc::OP modo;
  if(op == "c") modo = SATCirc::COMPILACAO;
  else if(op == "v") modo = SATCirc::VERIFICACAO;
  else return EXIT_FAILURE;      // Não deve ser possível alcançar este else

  if(modo == SATCirc::VERIFICACAO && argc <= 3) {
    cerr << "Arquivo de verificação não especificado." << endl;
    return EXIT_FAILURE;
  } 
  
  // Execução
  switch(modo) {
  case SATCirc::COMPILACAO:
    return SATCirc::compilar(file_in); break;
  case SATCirc::VERIFICACAO:
    file_ver.append(argv[3]);
    return SATCirc::verificar(file_in, file_ver); break;
  } 
}
