%{
#include<cstdlib>
#include<string>

//Ainda nao foi implementada
#include "CnfParser.h"

%}

%option 8bit reentrant bison-bridge
%option warn noyywrap nodefault
%option outfile="CnfScanner.c" header-file="CnfScanner.h"

DIGIT [0-9]

%%
[A-Z][A-Z0-9]* 	{printf("%s ",yytext);} {yylval->ID = new std::string(yytext); return ID}
[\-]*[0-9]+			{printf("NUM ");}       {yylval->NUM = std::atoi(yytext); return NUM}
\(   			{printf("( ");}			{return '('}
\)				{printf(") ");}			{return ')'}
[ \t\n]*  		{}
.        		{printf("What is this: %s.\n", yytext);}
