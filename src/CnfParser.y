%{
#include <string>

void yyerror(yyscan_t scanner, SATCirc::Circuit **str, char const *msg);
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

%define api.value.type union
%define parse.error verbose
%define api.pure
%lex-param {void *scanner}
%parse-param {void *scanner} {SATCirc::Cnf **cnf}



%union {
    int *intenger;
    std::string *st;
    std::vector<SATCirc::Var> *vars;
    SATCirc::Clause *c;
    std::vector<SATCirc::Clause> *cs;

}


%token <st> ID
%token <intenger> NUM
%type <vars> entrada;
%type <c> clausula;
%type <cs> clausulas;



%%
cnf:
    ID NUM clausulas    {
        std::string nome = *($1);
        int n = ($2);
        std::vector<SATCirc::Clause> vc = *($3);
        *cnf = new SATCirc::Cnf(nome, n, vc);
    }
    ;

clausulas:
        clausula   {
                SATCirc::Clause c = *($1);
                $$ = new std::vector<SATCirc::Clause>();
                $$->push_back(c);
        }

    |   clausulas clausula{
                SATCirc::Clause c = *($2);
                std::vector<SATCirc::Clause> *vc = $1;
                vc->push_back(c);
                $$ = vc;
        }
    ;

clausula:
    '(' entrada ')'    {
                        SATCirc::Clause c = new SATCirc::Clause();
                        std::vector<SATCirc::Var> *vc = $2; 

                        for (std::vector<SATCirc::Var>::iterator it = vc->begin(); it != vc->end(); it++) 
                                c.addVar(*it);
                        
                    }    
    ;

entrada:
     NUM    {
        SATCirc::Var v = *($1);
        $$ = new std::vector<SATCirc::Var>();
        $$->push_back(v);
     }

    |
        entrada NUM{
            SATCirc::Var v = *($2);
            std::vector<SATCirc::Var> *vs = $1;
            vs->push_back(v);
            $$ = vs;
        }
    ;

%%

void yyerror(yyscan_t scanner, SATCirc::Circuit **str, char const *msg) {
    fprintf(stderr, "Error: %s\n", msg);
}
