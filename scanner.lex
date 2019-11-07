%{ /* Declarations section */
#include "tokens.hpp"
%}

%option yylineno
%option noyywrap
relop (==|!=|<|>|<=|>=)
binop ([+-*\/])
letter ([a-zA-Z])
digit ([0-9])
whitespace([ \t\n\r])
comment (^[ \t]*\/\/[^\r\n]*)
hexdigit (\x[0-9A-Fa-f]{2})
allowedstringescape ([\\\"\n])
"([\x20-\x21\x23-\x5B\x5D-\x7E]|\\[\\"nrt0]|\\x[0-9A-Fa-f]{2})*"
notstring ([^\\"\n\r])
string (^\"[^\\"\n\r]\"$)


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
{letter}({letter}|{digit})* return ID
[1-9]{digit}* return NUM;
^\"{notstring}\"$ return STRING;
WHITESPACE([ \t\n\r])




{whitespace} ;
. printf("Lex doesn't know what that is!\n");

%%


