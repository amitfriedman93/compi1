%{ /* Declarations section */
#include "tokens.hpp"
#include "stdio.h"

%}

%option yylineno
%option noyywrap
%x string
relop (==|!=|<|>|<=|>=)
binop ([+\-*\/])
letter ([a-zA-Z])
digit ([0-9])
whitespace([ \t\n\r]+)
comment (\/\/[^\r\n]*)
hexdigit (\\x[0-9A-Fa-f]{2})
allowedstringescape ([\\"nrt0])
printable ([\x20-\x21\x23-\x5B\x5D-\x7E])
unprintable ([^\x20-\x7E])

%%
"void" return VOID;
"int" return INT;
"byte" return BYTE;
"b" return B;
"bool" return BOOL;
"and" return AND;
"or" return OR;
"not" return NOT;
"true" return TRUE;
"false" return FALSE;
"return" return RETURN;
"if" return IF;
"else" return ELSE;
"while" return WHILE;
"break" return BREAK;
"continue" return CONTINUE;
";" return SC;
"," return COMMA;
"(" return LPAREN;
")" return RPAREN;
"{" return LBRACE;
"}" return RBRACE;
"=" return ASSIGN;
{relop} return RELOP;
{binop} return BINOP;
{comment} return COMMENT;
{letter}({letter}|{digit})* return ID;
0|[1-9]{digit}* return NUM;
"\"" BEGIN(string);
<string><<EOF>> return UNCLOSED;
<string>[\r\n] return UNCLOSED;
<string>{unprintable} return UNCLOSED;
<string>({printable}|\\({printable}|\\|\"))*\" {BEGIN(0);return STRING;}
<string>({printable}|\\({printable}|\\|\"))*\\\" return UNCLOSED;
<string>. ;
{whitespace} return WHITESPACE;
. return ERROR;


%%


