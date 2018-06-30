# SATCirc

Verificador de propriedades de circuitos digitais combinatórios.

## Estrura básica do código conte
- `CircuitParser.y CircuitScanner.l`
- `CnfParser.y CnfScanner.l`
    Parser (bison) e scanner (flex) para os 
    arquivos de especificação de input de circuito e cnf,
    respectivametne.
- `Cnf.cc Cnf.h` classe Cnf.
- `Var.cc Var.h` classe variável.
- `Circuit.cc Circuit.h` classe responsável pela estrutura de dados
  do circuito.
- `Env.cc Env.h` ambiente para armazenar cnf e variável lidas dos
  arquivos de input para utilização interna.
- `Execucao.cc Execucao.h` funções de compilação e verificação.
- `Solver.cc Solver.h` classe de ligação entre o programa e SAT solvers.
- `readverify.cc readverify.h` leitura do arquivo de verificação.
- `Main.cc` entrada do programa.
- `minisat/` SAT solver utilizado.

## Compilação
### Requisitos
- OS
  Debian GNU/Linux 9, ou equivalente (ubuntu).
- Programas e bibliotecas
  Compilador C++11/C11 (ex: >= g++ 4.6), bison, flex e libz-dev (debia)

### Geração do parser e scanner.
```shell
bison *.y
flex -Cf *.l
```
### Compilação MiniSat
```shell
cd src
export MROOT=$(pwd)
make libr -C minisat/simp/
ln -s minisat/simp/lib_release.a minisat.a
```

### Compilação SATCirc
```shell
cd src
g++ -Iminisat -std=c++11 -O3 *.c *.cc minisat.a -lz -o satcirc
```
