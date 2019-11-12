#include "tokens.hpp"
#include "stdio.h"
#include <iostream>
#include <set>
#include <string>

/**
 * The function gets a lexeme and in the output param returns the illegal escape char.
 * @param lexeme - the string to find the invalid escape in.
 * @param illegalEscaping - an output param for the illegal escape char.
 * @return - true if an illegal escape has been found, and false if we encountered an error.
 */
bool find_undefined_escape(std::string lexeme, char &illegalEscaping){
    std::set<char> legalEscaping = {'r', 'n', '\\', 't', '0', 'x', '"'};
    for(auto it = lexeme.begin(); it != lexeme.end(); ++it){
        if(*it == '\\' && ++it != lexeme.end() && legalEscaping.find(*it) == legalEscaping.end()){
            illegalEscaping = *it;
            return true;
        }
    }
    //if we've got here, it means the final char in the lexeme is '\', therefore it is unclosed string.
    return false;
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

void error_handler(int token, std::string errorMsg){
    if (token == UNCLOSED){
        std::cout << "Error unclosed string" << std::endl;
    }
    if (token == UNDEFINEDESCAPE){
        std::cout << "Error undefined escape sequence" << find_undefined_escape(yytext) << std::endl;
    }
    if (token == ERROR){
        std::cout << "ERROR " << yytext << std::endl;
    }
    if (token == UNDEFINEDHEX){
        std::cout << "Error undefined escape sequence x" << errorMsg << std::endl;
    }
    exit(0);
}

char hex_converter(std::string lexeme){
    int num1, num2;
    std::string hexData;

    lexeme++;//first char after \x
    if (*lexeme == '\0'){
        error_handler(UNDEFINEDHEX, "");
    } else {
        num1 = convert_to_num(*lexeme);
        hexData += *lexeme;
        lexeme++;
        //if the first char after \x is not a 0-9|A-F or if it was the end of the string
        if (num1 == -1 or *lexeme == '\0'){
            error_handler(UNDEFINEDHEX, hexData);
        } else {
            num2 = convert_to_num(*lexeme);
            hexData += *lexeme;
            if (num2 == -1){//if the second char after \x is not a 0-9|A-F
                error_handler(UNDEFINEDHEX, hexData);
            } else {//after \x we have valid hex number
                if (is_printable((num1 * 16) + num2)){//maybe should change to strtol
                    return (char)((num1 * 16) + num2);
                }
                error_handler(UNDEFINEDHEX, hexData);
            }
        }
    }
    error_handler(ERROR, "something bad");
}

/**
 * Gets a string lexeme, and edits it so that special escape sequences will be printed as needed.
 * @param lexemeToEdit - the input lexeme.
 * @returns the edited string
 */
std::string edit_string(std::string lexemeToEdit){

    for (auto it = lexemeToEdit.begin(); it != lexemeToEdit.end(); ++it){
        if (*it == '"'){
            lexemeToEdit.erase(it);
        }
        else if (*it == '\\'){
            it = lexemeToEdit.erase(it);
            if (it != lexemeToEdit.end()){
                switch(*it){
                    case '\\':
                        *it = '\\';
                        break;
                    case 'n':
                        *it = '\n';
                        break;
                    case 'r':
                        *it = '\r';
                        break;
                    case 't':
                        *it = '\t';
                        break;
                    case '"':
                        *it = '"';
                        break;
                    case 'x':
                        *it = hex_converter(lexeme);
                        lexeme += 2;
                        break;
                    default:
                        error_handler(UNDEFINEDESCAPE, "");
                }
            } else {
                error_handler(UNCLOSED, "");
            }
        }
    }

    return lexemeToEdit;
}

void basic_print(const std::string &token_name, const std::string &lexeme){
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
            basic_print("COMMENT", "//");
        }
        if (token == ID){
            basic_print("ID", yytext);
        }
        if (token == NUM){
            basic_print("NUM", yytext);
        }
        if (token == STRING){
            std::string editedStr = edit_string(yytext);
            basic_print("STRING", editedStr);
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




