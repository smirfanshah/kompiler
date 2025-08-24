#ifndef TOKEN_H
#define TOKEN_H

#include<string>

enum class TokenType{
    // Keywords
    If_Kw,
    Else_kw,
    While_kw,
    For_kw,
    Return_kw,
    Function_kw,
    Var_kw,
    Const_kw,

    // Operators
    Plus_op,
    Minus_op,
    Multiply_op,
    Divide_op,
    Assign_op,
    Equal_op,
    NotEqual_op,

    // Delimiters
    Comma_delm,
    Semicolon_delm,
    Colon_delm,
    OpenParen_delm,
    CloseParen_delm,
    OpenCurly_delm,
    CloseCurly_delm,

    // Comment
    Comment,
    
    // Literals
    Int_lit,
    Float_lit,
    String_lit,

    // Identifiers
    Identifier,

    // End of file
    EndOfFile,

    // Error token
    Error
};

class Token{
public:
    TokenType type;
    std::string lexeme;

    Token(TokenType type, const std::string& value = "")
        : type(type), lexeme(value) {}

};
#endif // TOKEN_H