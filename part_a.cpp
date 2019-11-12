#include "tokens.hpp"
#include "stdio.h"
#include <iostream>
#include <set>
#include <string>


char find_undefined_escape(char* lexeme){
    std::set <char> legal_escaping = {'r', 'n', '\\', 't', '0', 'x', '"'};
    while (*lexeme != '\0'){
        if (*lexeme == '\\'){
            lexeme++;
            //current char in the lexeme appears after '\' but not defined as legal escape
            if (*lexeme != '\0' and legal_escaping.find(*lexeme) == legal_escaping.end()){
                return *lexeme;
            }
        }
        lexeme++;
    }
    return 'r';
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
    return hexVal >= 0 && hexVal <= 127;
}

void error_handler(int token, std::string error_msg){
    if (token == UNCLOSED){
        std::cout << "Error unclosed string" << std::endl;
    }
    if (token == UNDEFINEDESCAPE){
        std::cout << "Error undefined escape sequence " << find_undefined_escape(yytext) << std::endl;
    }
    if (token == ERROR){
        std::cout << "ERROR " << yytext << std::endl;
    }
    if (token == UNDEFINEDHEX){
        std::cout << "Error undefined escape sequence x" << error_msg << std::endl;
    }
    exit(0);
}

char hex_converter(char* lexeme){
    int num1, num2;
    std::string hex_data;

    lexeme++;//first char after \x
    if (*lexeme == '\0'){
        error_handler(UNDEFINEDHEX, "");
    } else {
        num1 = convert_to_num(*lexeme);
        hex_data += *lexeme;
        lexeme++;
        //if the first char after \x is not a 0-9|A-F or if it was the end of the string
        if (num1 == -1 or *lexeme == '\0'){
            error_handler(UNDEFINEDHEX, hex_data);
        } else {
            num2 = convert_to_num(*lexeme);
            hex_data += *lexeme;
            if (num2 == -1){//if the second char after \x is not a 0-9|A-F
                error_handler(UNDEFINEDHEX, hex_data);
            } else {//after \x we have valid hex number
                if (is_printable((num1 * 16) + num2)){//maybe should change to strtol
                    return (char)((num1 * 16) + num2);
                }
                error_handler(UNDEFINEDHEX, hex_data);
            }
        }
    }
    error_handler(ERROR, "something bad");
}

void edit_string(char* lexeme, char* new_string){
    while (*lexeme != '\0'){
        if (*lexeme == '"'){
            //printing the string without "
            lexeme++;
            continue;
        }
        if (*lexeme == '\\'){
            lexeme++;
            if (*lexeme == '\0'){
                error_handler(UNCLOSED, "");
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
                    *new_string = hex_converter(lexeme);
                    lexeme += 2;
                    break;
                default:
                    lexeme[1] = '\0';
                    error_handler(UNDEFINEDESCAPE, std::string(lexeme));
            }
            new_string++;
            lexeme++;
        } else { //char does not need a special treatment
            *new_string = *lexeme;
            new_string++;
            lexeme++;
        }
    }
    *new_string = '\0';
}



void basic_print(std::string token_name, char* lexeme){
    std::cout << yylineno << " " << token_name << " " << lexeme << std::endl;
}

int main()
{
	int token;
	while(token = yylex()) {
		if (token == VOID){
			basic_print("VOID", yytext);
		}
        if (token == INT){
            basic_print("INT", yytext);
        }
        if (token == BYTE){
            basic_print("BYTE", yytext);
        }
        if (token == B){
            basic_print("B", yytext);
        }
        if (token == BOOL){
            basic_print("BOOL", yytext);
        }
        if (token == AND){
            basic_print("AND", yytext);
        }
        if (token == OR){
            basic_print("OR", yytext);
        }
        if (token == NOT){
            basic_print("NOT", yytext);
	    }
        if (token == TRUE){
            basic_print("TRUE", yytext);
        }
        if (token == FALSE){
            basic_print("FALSE", yytext);
        }
        if (token == RETURN){
            basic_print("RETURN", yytext);
        }
        if (token == IF){
            basic_print("IF", yytext);
        }
        if (token == ELSE){
            basic_print("ELSE", yytext);
        }
        if (token == WHILE){
            basic_print("WHILE", yytext);
        }
        if (token == BREAK){
            basic_print("BREAK", yytext);
        }
        if (token == CONTINUE){
            basic_print("CONTINUE", yytext);
        }
        if (token == SC){
            basic_print("SC", yytext);
        }
        if (token == COMMA){
            basic_print("COMMA", yytext);
        }
        if (token == LPAREN){
            basic_print("LPAREN", yytext);
        }
        if (token == RPAREN){
            basic_print("RPAREN", yytext);
        }
        if (token == LBRACE){
            basic_print("LBRACE", yytext);
        }
        if (token == RBRACE){
            basic_print("RBRACE", yytext);
        }
        if (token == ASSIGN){
            basic_print("ASSIGN", yytext);
        }
        if (token == RELOP){
            basic_print("RELOP", yytext);
        }
        if (token == BINOP){
            basic_print("BINOP", yytext);
        }
        if (token == COMMENT){
            char* comment = (char*)malloc(sizeof(char)*3);
            comment[0] = '/';
            comment[1] = '/';
            comment[2] = '\0';
            basic_print("COMMENT", comment);
        }
        if (token == ID){
            basic_print("ID", yytext);
        }
        if (token == NUM){
            basic_print("NUM", yytext);
        }
        if (token == STRING){
            char* new_string = (char*)malloc(sizeof(char)*1025);
            edit_string(yytext, new_string);
            basic_print("STRING", new_string);
            //basic_print("STRING", yytext);
            free(new_string);
        }
        if (token == WHITESPACE){
            //Ignoring white space
        }
        if (token == UNCLOSED or token == UNDEFINEDESCAPE or token == ERROR){
            error_handler(token, "");
        }
    }
	return 0;
}




