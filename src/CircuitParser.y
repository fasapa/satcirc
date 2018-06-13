%{
#include <string>
#include <vector>

#include "Circuit.h"
#include "CircuitParser.h"
#include "CircuitScanner.h"

void yyerror(yyscan_t scanner, SATCirc::Circuit **str, char const *msg);
%}

%code requires {
    #include <vector>
    #include <string>
    #include <iostream>
    #include "Circuit.h"
    using namespace std;
 }


%defines "CircuitParser.h"
%output "CircuitParser.c"

%define parse.error verbose
%define api.pure
%lex-param {void *scanner}
%parse-param {void *scanner} {SATCirc::Circuit **circ}

%union {
    SATCirc::Var *var;
    std::vector<SATCirc::Var> *vars;
    SATCirc::Component *comp;
    std::vector<SATCirc::Component> *comps;
    std::string *id;
}

%token <id> ID
%token <var> VAR
%type <vars> variaveis
%type <comp> component
%type <comps> components

%%

circuito:
             ID '{' components '}' {
                 std::string nome = *($1);
                 std::vector<SATCirc::Component> vc = *($3);
                 *circ = new SATCirc::Circuit(nome, vc);
             }
        ;

components:     component {
                    SATCirc::Component c = *($1);
                    $$ = new std::vector<SATCirc::Component>();
                    $$->push_back(c);
             }
        |
                components component {
                    SATCirc::Component c = *($2);
                    std::vector<SATCirc::Component> *vc = $1;
                    vc->push_back(c);
                    $$ = vc;
             }
        ;

component:      variaveis ID variaveis ';' {
                    std::string nome = *($2);
                    std::vector<SATCirc::Var> in, out;
                    in = *($1); out = *($3);
                    $$ = new SATCirc::Component(nome, in, out);
             }
        ;

variaveis:
                VAR           {
                    SATCirc::Var v = *($1);
                    $$ = new std::vector<SATCirc::Var>();
                    $$->push_back(v);
             }
        |
                variaveis VAR {
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
