%{
#include <cstdlib>
#include <string>

#include "Var.h"
#include "CircuitParser.h"
%}

%option 8bit reentrant bison-bridge
%option warn noyywrap nodefault
%option outfile="CircuitScanner.c" header-file="CircuitScanner.h"
%option prefix="circ_yy"

%%

\;                { return ';'; }
\{                { return '{'; }
\}                { return '}'; }
\[                { return '['; }
\]                { return ']'; }
[a-z][a-zA-Z0-9]* { yylval->id = new std::string(yytext); return VAR; }
[A-Z][a-zA-Z0-9]* { yylval->id = new std::string(yytext); return ID; }
[ \t\n]*          { }
.                 { printf("What is this: %s.\n", yytext); }
