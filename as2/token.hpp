//
// Created by BEN on 2/8/24.
//

#ifndef token_hpp
#define token_hpp

#include <string>
#include "token_type.hpp"

class Token {
 private:
    TokenType type_;  // the type of this token
    std::string lexeme_;  // the sequence of characters that represent something in the language

 public:
    Token();
    Token(TokenType type, std::string lexeme);
    void setType(TokenType type);
    void setLexeme(std::string lexeme);
    TokenType getType() const;
    std::string getLexeme() const;
    std::string toString() const;
};

#endif // token_hpp
