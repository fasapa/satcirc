# SATCirc

SATCirc is a combinatorial digital circuit varification tool.

# Building

First build MiniSat library
```shell
export MROOT=`pwd`
make libr -C minisat/simp/
ln -s minisat/simp/lib_release.a minisat.a
```
