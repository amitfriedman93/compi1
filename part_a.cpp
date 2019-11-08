#include "tokens.hpp"
#include "stdio.h"
#include <iostream>
#include <set>

void edit_string(char* lexeme, char* new_string);

char find_bad_escape(char* lexeme);

int convert_to_num(char hexVal);

bool is_printable(int hexVal);

int main()
{
	int token;
	while(token = yylex()) {
		if (token == VOID){
			std::cout << yylineno << " VOID " << yytext << "\n";
		}
        if (token == INT){
            std::cout << yylineno << " INT " << yytext << "\n";
        }
        if (token == BYTE){
            std::cout << yylineno << " BYTE " << yytext << "\n";
        }
        if (token == B){
            std::cout << yylineno << " B " << yytext << "\n";
        }
        if (token == BOOL){
            std::cout << yylineno << " BOOL " << yytext << "\n";
        }
        if (token == AND){
            std::cout << yylineno << " AND " << yytext << "\n";
        }
        if (token == OR){
            std::cout << yylineno << " OR " << yytext << "\n";
        }
        if (token == NOT){
            std::cout << yylineno << " NOT " << yytext << "\n";
	    }
        if (token == TRUE){
            std::cout << yylineno << " TRUE " << yytext << "\n";
        }
        if (token == FALSE){
            std::cout << yylineno << " FALSE " << yytext << "\n";
        }
        if (token == RETURN){
            std::cout << yylineno << " RETURN " << yytext << "\n";
        }
        if (token == IF){
            std::cout << yylineno << " IF " << yytext << "\n";
        }
        if (token == ELSE){
            std::cout << yylineno << " ELSE " << yytext << "\n";
        }
        if (token == WHILE){
            std::cout << yylineno << " WHILE " << yytext << "\n";
        }
        if (token == BREAK){
            std::cout << yylineno << " BREAK " << yytext << "\n";
        }
        if (token == CONTINUE){
            std::cout << yylineno << " CONTINUE " << yytext << "\n";
        }
        if (token == SC){
            std::cout << yylineno << " SC " << yytext << "\n";
        }
        if (token == COMMA){
            std::cout << yylineno << " COMMA " << yytext << "\n";
        }
        if (token == LPAREN){
            std::cout << yylineno << " LPAREN " << yytext << "\n";
        }
        if (token == RPAREN){
            std::cout << yylineno << " RPAREN " << yytext << "\n";
        }
        if (token == LBRACE){
            std::cout << yylineno << " LBRACE " << yytext << "\n";
        }
        if (token == RBRACE){
            std::cout << yylineno << " RBRACE " << yytext << "\n";
        }
        if (token == ASSIGN){
            std::cout << yylineno << " ASSIGN " << yytext << "\n";
        }
        if (token == RELOP){
            std::cout << yylineno << " RELOP " << yytext << "\n";
        }
        if (token == BINOP){
            std::cout << yylineno << " BINOP " << yytext << "\n";
        }
        if (token == COMMENT){
            std::cout << yylineno << " COMMENT //" << "\n";
        }
        if (token == ID){
            std::cout << yylineno << " ID " << yytext << "\n";
        }
        if (token == NUM){
            std::cout << yylineno << " NUM " << yytext << "\n";
        }
        if (token == STRING){
            char* new_string = (char*)malloc(sizeof(char)*1025);
            edit_string(yytext, new_string);
            std::cout << yylineno << " STRING " << new_string << "\n";
            free(new_string);
        }
        if (token == WHITESPACE){
            //Ignoring white space
        }
        if (token == UNCLOSED){
            std::cout << "Error unclosed string\n";
            exit(0);
        }
        if (token == UNDEFINEDESCAPE){
            std::cout << "Error undefined escape sequence" << find_bad_escape(yytext) << "\n";
            exit(0);
        }
        if (token == ERROR){
            std::cout << "ERROR " << yytext << "\n";
            exit(0);
        }
    }
	return 0;
}


char find_bad_escape(char* lexeme){
    std::set <char> allowed_escaping = {'r', 'n', '\\', 't', '0', 'x', '"'};
    while (lexeme != nullptr){
        if (*lexeme == '\\'){
            lexeme++;
            if (allowed_escaping.find(*lexeme) == allowed_escaping.end()){
                return *lexeme;
            }
        }
        lexeme++;
    }
}

void edit_string(char* lexeme, char* new_string){

    while (lexeme){
        if (*lexeme == '"'){
            lexeme++;
            continue;
        }
        if (*lexeme == '\\'){
            lexeme++;
            if (lexeme == nullptr){
                std::cout << "Error unclosed string\n";
                exit(0);
            }
            switch(*lexeme){
                case '\\':
                    *new_string = '\\';
                    break;
                case 'n':
                    *new_string = '\n';
                    break;
                case 'r':
                    *new_string = '\r';
                    break;
                case 't':
                    *new_string = '\t';
                    break;
                case '"':
                    *new_string = '"';
                    break;
                case 'x':
                    lexeme++;
                    if (lexeme == nullptr){
                        std::cout << "Error undefined escape sequence x\n";
                        exit(0);
                    }
                    int num1 = convert_to_num(*lexeme);
                    if (num1 == -1){
                        std::cout << "Error undefined escape sequence x"<<*lexeme<<"\n";
                        exit(0);
                    }
                    char old = *lexeme;
                    lexeme++;
                    if (lexeme == nullptr){
                        std::cout << "Error undefined escape sequence x"<<old<<"\n";
                        exit(0);
                    }
                    int num2 = convert_to_num(*lexeme);
                    if (num2 == -1){
                        std::cout << "Error undefined escape sequence x"<<old<<*lexeme"\n";
                        exit(0);
                    }
                    if (is_printable((num1 * 16) + num2)){
                        *new_string = (char)((num1 * 16) + num2);
                    }
                    break;
                default:
                    break;
            }
            new_string++;
            lexeme++;
        }
        *new_string = *lexeme;
        new_string++;
        lexeme++;
    }
    *new_string = '\0';
}

int convert_to_num(char hexVal){
    if (hexVal >= '0' and hexVal <= '9'){
        return hexVal - '0';
    }
    if (hexVal >= 'A' and hexVal <= 'F'){
        return hexVal - 'A' + 10;
    }
    if (hexVal >= 'a' and hexVal <= 'f'){
        return hexVal - 'a' + 10;
    }
    return -1;
}

bool is_printable(int hexVal){
    return hexVal >= 20 && hexVal <= 126;
}

