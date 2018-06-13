%{
#include <cstdlib>
#include <string>

#include "CircuitParser.h"
%}

%option 8bit reentrant bison-bridge
%option warn noyywrap nodefault
%option outfile="CircuitScanner.c" header-file="CircuitScanner.h"

DIGIT [0-9]

%%

\;                { return ';'; }
\{                { return '{'; }
\}                { return '}'; }
{DIGIT}+          { yylval->VAR = std::atoi(yytext); return VAR; }
[A-Z][a-zA-Z0-9]* { yylval->ID = new std::string(yytext); return ID; }
[ \t\n]*  { }
.        { printf("What is this: %s.\n", yytext); }
