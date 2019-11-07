%{ /* Declarations section */
#include "tokens.hpp"
%}

%option yylineno
%option noyywrap
digit ([0-9])
letter ([a-zA-Z])
whitespace ([\t\n ])

%%
{digit}+ return NUM;
{letter}+ return WORD;
{letter}+@{letter}+\.com return EMAIL;
{whitespace} ;
. printf("Lex doesn't know what that is!\n");

%%


