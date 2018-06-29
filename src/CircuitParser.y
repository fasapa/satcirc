/*Bibliotecas básicas*/
%{
#include <string>
#include <vector>

#include "Env.h"
#include "Circuit.h"
#include "CircuitParser.h"
#include "CircuitScanner.h"

void circ_yyerror(yyscan_t scanner, SATCirc::Circuit **str, SATCirc::EnvVar *env, char const *msg);
%}

/*Código que será colado diretamente no código fonte gerado*/

%code requires {
    #include <vector>
    #include <string>
    #include <iostream>

    #include "Env.h"
    #include "Circuit.h"
    using namespace std;
 }

%defines "CircuitParser.h"
%output "CircuitParser.c"

%name-prefix "circ_yy"

%define parse.error verbose
%define api.pure
%lex-param {void *scanner}
%parse-param {void *scanner} {SATCirc::Circuit **circ} {SATCirc::EnvVar *env}


/*Gerando os tipos de variaveis usadas no compilador, é baseada em uma union do C*/
%union {
    std::vector<SATCirc::Var> *vars;
    SATCirc::Component *comp;
    std::vector<SATCirc::Component> *comps;
    std::string *id;
}

/*Tokens recebidos do Scanner*/
%token <id> ID
%token <id> VAR
/*Tipos intermediarios usados no BNF*/
%type <vars> variaveis
%type <comp> component
%type <comps> components

/*BNF do circuito , ele vai determinar a ordem e o que será feito quando aquele formato for encontrado*/
%%

circuito:
             ID '[' variaveis ';' variaveis ']' '{' components '}' {
                 std::string nome = *($1);
                 std::vector<SATCirc::Var> in = *($3), out = *($5);
                 std::vector<SATCirc::Component> vc = *($8);
                 *circ = new SATCirc::Circuit(nome, vc, in.size() + out.size());
             }
        ;

components:     component {
                    $$ = new std::vector<SATCirc::Component>();
                    $$->push_back(*($1));
             }
        |
                components component {
                    std::vector<SATCirc::Component> *vc = $1;
                    vc->push_back(*($2));
                    $$ = vc;
             }
        ;

component:      variaveis ID variaveis ';' {
                    $$ = new SATCirc::Component(*($2), *($1), *($3));
             }
        ;

variaveis:
                VAR           {
                    SATCirc::Var v;
                    if(env->in(*($1))) v = env->get(*($1));
                    else { v = SATCirc::Var(true); env->insert(*($1), v); }
                    $$ = new std::vector<SATCirc::Var>();
                    $$->push_back(v);
             }
        |
                variaveis VAR {
                    SATCirc::Var v;
                    if(env->in(*($2))) v = env->get(*($2));
                    else { v = SATCirc::Var(true); env->insert(*($2),v); }
                    std::vector<SATCirc::Var> *vs = $1;
                    vs->push_back(v);
                    $$ = vs;
             }
        ;

%%

void circ_yyerror(yyscan_t scanner, SATCirc::Circuit **str, SATCirc::EnvVar *env, char const *msg) {
    (void)scanner; (void)str; (void)env;
    fprintf(stderr, "Error: %s\n", msg);
}
