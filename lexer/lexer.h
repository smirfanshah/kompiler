#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "token.h"



class Lexer {
    std::string src;
    size_t pos = 0;
    char currentChar;
    size_t line_number =0;
public:
    Lexer(const std::string& source): src(source), currentChar(src[pos]){}
    void proceed();
    Token identifyToken();
    void reset();
    char peek() const;
    // size_t cur_pos() const;
    void ignoreWhitespaces();
    // void igoneComments();
    // void tokenize();    

};

#endif // LEXER_H