%{
#include<cstdlib>
#include<string>

//Ainda nao foi implementada
#include "CnfParser.h"
%}

%option 8bit reentrant bison-bridge
%option warn noyywrap nodefault
%option outfile="CnfScanner.c" header-file="CnfScanner.h"
%option prefix="cnf_yy"

%%
\(                { return '('; }
\)	              { return ')'; }
\-?[0-9]+		  { yylval->integer = std::atol(yytext); return NUM; }
[A-Z][a-zA-Z0-9]* { yylval->id = new std::string(yytext); return ID; }
[ \t\n]*  		  { }       
.        		  { printf("What is this: %s.\n", yytext);}
