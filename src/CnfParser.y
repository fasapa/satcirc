%{
#include <string>
#include <vector>

#include "Var.h"
#include "Cnf.h"
#include "CnfParser.h"
#include "CnfScanner.h"

void cnf_yyerror(yyscan_t scanner, SATCirc::Cnf **cnf, char const *msg);
%}

%code requires {
    #include <string>
    #include <iostream>
    #include <vector>

    #include "Cnf.h"
    using namespace std;
 }

%defines "CnfParser.h"
%output "CnfParser.c"

%name-prefix "cnf_yy"

%define parse.error verbose
%define api.pure
%lex-param {void *scanner}
%parse-param {void *scanner} {SATCirc::Cnf **cnf}

%union {
    int integer;
    std::string *id;
    std::vector<SATCirc::Var> *vars;
    SATCirc::Clause *cl;
    std::vector<SATCirc::Clause> *cls;
}

%token <id> ID
%token <integer> NUM
%type <vars> variaveis;
%type <cl> clausula;
%type <cls> clausulas;

%%

cnf:
                ID NUM clausulas {
                    std::string nome = *($1);
                    std::vector<SATCirc::Clause> vc = *($3);
                    *cnf = new SATCirc::Cnf(nome, ($2), vc);
                }
                ;

clausulas:
                clausula {
                    $$ = new std::vector<SATCirc::Clause>();
                    $$->push_back(*($1));
                }
                
        |       clausulas clausula {
                   SATCirc::Clause c = *($2);
                   std::vector<SATCirc::Clause> *vc = $1;
                   vc->push_back(c);
                   $$ = vc;
                }
                ;

clausula:
                '(' variaveis ')' {
                    SATCirc::Clause *c = new SATCirc::Clause();
                    std::vector<SATCirc::Var> vc = *($2); 
                    for(size_t i = 0; i < vc.size(); i += 1) {
                        c->addVar(vc[i]);
                    }
                    $$ = c;
                }    
                ;

variaveis:
                NUM  {
                    SATCirc::Var v(($1));
                    $$ = new std::vector<SATCirc::Var>();
                    $$->push_back(v);
                }
                
        |
                variaveis NUM{
                    SATCirc::Var v(($2));
                    std::vector<SATCirc::Var> *vs = $1;
                    vs->push_back(v);
                    $$ = vs;
                }
                ;
%%

void cnf_yyerror(yyscan_t scanner, SATCirc::Cnf **cnf, char const *msg) {
    (void)scanner; (void)cnf;
    fprintf(stderr, "Error: %s\n", msg);
}
