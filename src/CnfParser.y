%{
#include <string>

#include "Circuit.h"
#include "CircuitParser.h"
#include "CircuitScanner.h"

void yyerror(yyscan_t scanner, SATCirc::Circuit **str, char const *msg);
%}

%code requires {
    #include <string>
    #include <iostream>
    #include "Circuit.h"
    using namespace std;
 }


%defines "CircuitParser.h"
%output "CircuitParser.c"

%define api.value.type union
%define parse.error verbose
%define api.pure
%lex-param {void *scanner}
%parse-param {void *scanner} {SATCirc::Circuit **circ}

%token <std::string*> ID
%token <int> VAR

%%

circuito:
             ID '{' components '}' { *circ = new SATCirc::Circuit(*($1));  }
        ;

components:     component
        |       components component
        ;

component:      variaveis ID variaveis ';'
        ;

variaveis:      VAR
        |       variaveis VAR
        ;

%%

void yyerror(yyscan_t scanner, SATCirc::Circuit **str, char const *msg) {
    fprintf(stderr, "Error: %s\n", msg);
}
