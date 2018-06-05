# SATCirc

SATCirc is a combinatorial digital circuit verification tool.

# Basic defualt gates
* `a b AND c`: (¬a ∨ ¬b ∨  c)∧( a ∨ ¬c)∧( b ∨ ¬c)
* `a b  OR c`: ( a ∨  b ∨ ¬c)∧(¬a ∨  c)∧(¬b ∨  c)
* `a   NOT c`: (¬a ∨ ¬c)∧(a ∨ c)

# Building

First build MiniSat library
```shell
cd src
export MROOT=$(pwd)
make libr -C minisat/simp/
ln -s minisat/simp/lib_release.a minisat.a
```
