#include "tokens.hpp"
#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>


std::pair<int, std::string> calc_op(std::string binop, std::string num1, std::string num2){
    int n1 = std::stoi(num1);
    int n2 = std::stoi(num2);
    int res = 0;
    if (binop == "+"){
        res = n1 + n2;
    }
    if (binop == "-"){
        res = n1 - n2;
    }
    if (binop == "*"){
        res = n1 * n2;
    }
    if (binop == "/"){
        res = n1 / n2;
    }
    return std::pair<int, std::string>(NUM, std::to_string(res));
}

void error_handler(int token){
    if (token == VOID){
        std::cout << "Error: VOID" << std::endl;
    }
    if (token == INT){
        std::cout << "Error: INT" << std::endl;
    }
    if (token == BYTE){
        std::cout << "Error: BYTE" << std::endl;
    }
    if (token == B){
        std::cout << "Error: B" << std::endl;
    }
    if (token == BOOL){
        std::cout << "Error: BOOL" << std::endl;
    }
    if (token == AND){
        std::cout << "Error: AND" << std::endl;
    }
    if (token == OR){
        std::cout << "Error: OR" << std::endl;
    }
    if (token == NOT){
        std::cout << "Error: NOT" << std::endl;
    }
    if (token == TRUE){
        std::cout << "Error: TRUE" << std::endl;
    }
    if (token == FALSE){
        std::cout << "Error: FALSE" << std::endl;
    }
    if (token == RETURN){
        std::cout << "Error: RETURN" << std::endl;
    }
    if (token == IF){
        std::cout << "Error: IF" << std::endl;
    }
    if (token == ELSE){
        std::cout << "Error: ELSE" << std::endl;
    }
    if (token == WHILE){
        std::cout << "Error: WHILE" << std::endl;
    }
    if (token == BREAK){
        std::cout << "Error: BREAK" << std::endl;
    }
    if (token == CONTINUE){
        std::cout << "Error: CONTINUE" << std::endl;
    }
    if (token == SC){
        std::cout << "Error: SC" << std::endl;
    }
    if (token == COMMA){
        std::cout << "Error: COMMA" << std::endl;
    }
    if (token == LPAREN){
        std::cout << "Error: LPAREN" << std::endl;
    }
    if (token == RPAREN){
        std::cout << "Error: RPAREN" << std::endl;
    }
    if (token == LBRACE){
        std::cout << "Error: LBRACE" << std::endl;
    }
    if (token == RBRACE){
        std::cout << "Error: RBRACE" << std::endl;
    }
    if (token == ASSIGN){
        std::cout << "Error: ASSIGN" << std::endl;
    }
    if (token == RELOP){
        std::cout << "Error: RELOP" << std::endl;
    }
    if (token == COMMENT){
        std::cout << "Error: COMMENT" << std::endl;
    }
    if (token == ID){
        std::cout << "Error: ID" << std::endl;
    }
    if (token == STRING){
        std::cout << "Error: STRING" << std::endl;
    }
    if (token == ERROR){
        std::cout << "Error " << yytext << std::endl;
    }
    if (token == ILLEGALEXP){
        std::cout << "Error: Bad Expression" << std::endl;
    }
    exit(0);
}


bool apply_action_if_binop(std::vector<std::pair<int , std::string>> &input,
                  std::vector<std::pair<int, std::string>>::iterator &it){
    if ((*it).first == BINOP){
        if ((it+1 != input.end() && it+2 != input.end()) &&
            (*(it + 1)).first == NUM && (*(it + 2)).first == NUM){
            *it = calc_op((*it).second, (*(it + 1)).second, (*(it + 2)).second);
            input.erase(it + 1, it + 3);
            return true;
        }
        error_handler(ILLEGALEXP);
    }
    return false;
}

void calculate(std::vector<std::pair<int , std::string>> input){
    std::vector<std::pair<int, std::string>>::iterator it = input.end();
    for (--it; it!= input.begin(); --it){
        apply_action_if_binop(input, it);
    }
    bool wasBinop = apply_action_if_binop(input, it);
    if(!wasBinop){
        error_handler(ILLEGALEXP);
    }
    if (input.size() != 1){
        error_handler(ILLEGALEXP);
    }
    //if we got here than there should be only one element (the result) in the vector.
    std::cout << input.front().second<< std::endl;
}


int main()
{
	int token;
    std::vector<std::pair<int , std::string>> input;
	while(token = yylex()) {
        if (token == BINOP || token == NUM) {
            input.push_back(std::pair<int, std::string>(token, yytext));
        }
        else if (token == WHITESPACE){
            continue;
        }
        else {
            error_handler(token);
        }
	}
    if (input.size() == 1 && input.front().first == NUM){
        std::cout << input.front().second<< std::endl;
        return 0;
    }
    // TODO what if input size = 0?
    calculate(input);
	return 0;
}