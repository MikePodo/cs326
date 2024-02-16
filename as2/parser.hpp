//
// Created by BEN on 2/9/24.
//

#ifndef parser_hpp
#define parser_hpp

#include <iostream>
#include <vector>
#include "scanner.hpp"
#include "token.hpp"
#include "token_type.hpp"

class Parser {
 private:
    std::vector<Token> tokens_;      // from where do we get the tokens
    Token lookahead_;                // the current lookahead token
    int index_;                      // position of current token in vector

 public:
    Parser(std::vector<Token>& tokens);
    // Rules of the grammar.
    void code();
    void statement();
    void duck();
    void duck_opt();
    void duck_facing_right();
    void duck_facing_left();
    void duck_facing_eright();
    void quacks();
    void quack();

 private:
    // Consume the next token in the input.
    void match(int x);
    // Grabs the next lookahead.
    void consume();
    // Returns true if the lookahead's type is equal to type.
    bool check(TokenType type);
    // Returns true if the lookahead's type is on the types stored in the vector.
    bool check(std::vector<TokenType> types);
};

#endif // parser_hpp
