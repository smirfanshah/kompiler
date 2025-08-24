#include"lexer.h"
#include"token.h"
#include<iostream>
#include<string>
#include <cctype>
#include <unordered_map>
void Lexer::proceed(){
    pos++;
    if(pos<src.size()){
        currentChar= src[pos];
    }else{
        currentChar= '\0';
    }
}

void Lexer:: ignoreWhitespaces(){
    while(currentChar==' '){
        proceed();   
    }
}

char Lexer:: peek() const{
    if(pos+1<src.size()){return src[pos+1];} else{return '\0';}
}

Token Lexer::identifyToken(){

    ignoreWhitespaces(); //int
    switch (currentChar)
    {
    case '+': proceed(); return Token(TokenType::Plus_op);
    case '-': proceed(); return Token(TokenType::Minus_op);
    case '*': proceed(); return Token(TokenType::Multiply_op);
    case '/': proceed(); return Token(TokenType::Divide_op);
    case '=':
        proceed();
        switch (currentChar)
        {
        case '=': proceed(); return Token(TokenType::Equal_op);
        case '!': proceed(); return Token(TokenType::NotEqual_op);
        default : proceed(); return Token(TokenType::Assign_op);
        }
    case ',' :  proceed(); return Token(TokenType::Comma_delm);
    case '\0':  proceed(); return Token(TokenType::EndOfFile);
    case ';' :  proceed(); return Token(TokenType::Semicolon_delm);
    case ':' :  proceed(); return Token(TokenType::Colon_delm);
    case '(' :  proceed(); return Token(TokenType::OpenParen_delm);
    case ')' :  proceed(); return Token(TokenType::CloseParen_delm);
    case '{' :  proceed(); return Token(TokenType::OpenCurly_delm);
    case '}' :  proceed(); return Token(TokenType::CloseCurly_delm);
    case '\\':  proceed(); return Token(TokenType::EndOfFile);
    case '"' :  {
        proceed();
        std::string lexeme;
        while(currentChar!='"'){
            lexeme+= currentChar; 
            proceed();
        }
        return Token(TokenType::String_lit, lexeme);}

    default:
        if(isalpha(currentChar)){
            std:: string lexeme;
            while(isalnum(currentChar)){
                lexeme += currentChar;
                proceed();
            }
            if(lexeme=="if"){ proceed(); return Token(TokenType::If_Kw);}
            if(lexeme=="else"){ proceed(); return Token(TokenType::Else_kw);}
            if(lexeme=="while"){ proceed(); return Token(TokenType::While_kw);}
            if(lexeme=="for"){ proceed(); return Token(TokenType::For_kw);}
            if(lexeme=="return"){ proceed(); return Token(TokenType::Return_kw);}
            if(lexeme=="const"){ proceed(); return Token(TokenType::Const_kw);}
            if(lexeme=="fn"){ proceed(); return Token(TokenType::Function_kw);}
            return Token(TokenType:: Identifier, lexeme);

        } else if(isdigit(currentChar)){
            std::string lexeme;
            while(isdigit(currentChar)){
                lexeme+=currentChar;
                proceed();
            }
            return Token(TokenType::Int_lit, lexeme);
        }
    }
    
    return Token(TokenType::Error);
}

//Just for the evaluation and output purpose i am using the following function
const std::unordered_map<TokenType, std::string> tokenTypeToStrMap = {
    {TokenType::If_Kw, "If_Kw"},
    {TokenType::Else_kw, "Else_kw"},
    {TokenType::While_kw, "While_kw"},
    {TokenType::For_kw, "For_kw"},
    {TokenType::Return_kw, "Return_kw"},
    {TokenType::Function_kw, "Function_kw"},
    {TokenType::Const_kw, "Const_kw"},
    {TokenType::Plus_op, "Plus_op"},
    {TokenType::Minus_op, "Minus_op"},
    {TokenType::Multiply_op, "Multiply_op"},
    {TokenType::Divide_op, "Divide_op"},
    {TokenType::Assign_op, "Assign_op"},
    {TokenType::Equal_op, "Equal_op"},
    {TokenType::NotEqual_op, "NotEqual_op"},
    {TokenType::Comma_delm, "Comma_delm"},
    {TokenType::Semicolon_delm, "Semicolon_delm"},
    {TokenType::Colon_delm, "Colon_delm"},
    {TokenType::OpenParen_delm, "OpenParen_delm"},
    {TokenType::CloseParen_delm, "CloseParen_delm"},
    {TokenType::OpenCurly_delm, "OpenCurly_delm"},
    {TokenType::CloseCurly_delm, "CloseCurly_delm"},
    {TokenType::Comment, "Comment"},
    {TokenType::Int_lit, "Int_lit"},
    {TokenType::Float_lit, "Float_lit"},
    {TokenType::String_lit, "String_lit"},
    {TokenType::Identifier, "Identifier"},
    {TokenType::EndOfFile, "EndOfFile"},
    {TokenType::Error, "Error"}
};

std::string tokenTypeToString(TokenType type) {
    auto it = tokenTypeToStrMap.find(type);
    return it != tokenTypeToStrMap.end() ? it->second : "Unknown";
}


int main(){
    std::string str = "if (x = 42) return x + 1;";
    Lexer lexer(str);
    Token next = lexer.identifyToken(); 
    std::cout<<"I was here\n";
    while(next.type!=TokenType::EndOfFile){
        std::cout<<"Token:"<<tokenTypeToString(next.type);
        if(next.value.size()>0){
            std::cout<<", Value:" <<next.value<<std::endl;
        }
        else{
            std::cout<<std::endl;
        }
        next = lexer.identifyToken();

    }
    std::cout<<"but not here";

    return 0;
}