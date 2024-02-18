/*
    Name: Michael Podolsky, 2001945839, CS 326 1001, Project 2
    Description: This program scans and parses a made-up language. 
        Any invalid tokens or grammatical rules will result in an error.
    Input: token.cpp is a class that stores a token. The initializer 
        accepts a type and a lexeme.
    Output: token.cpp's Token class contains methods for returning the
        token's type, lexeme, and a method that prints the Token in the
        format of <'lexeme', type enum, token_name>
*/
//
// Created by BEN on 2/8/24.
//

#include "token.hpp"
#include "scanner.hpp"

Token::Token() : type_(TokenType::tok_na), lexeme_("") { }

Token::Token(TokenType type, std::string lexeme) : 
    type_(type), lexeme_(lexeme) { 
    // Initializer sets type and lexeme to corresponding arguments
}

void Token::setType(TokenType type) {
    type_ = type; // Set token type
}

void Token::setLexeme(std::string lexeme) {
    lexeme_ = lexeme; // Set token lexeme
}

TokenType Token::getType() const {
    return type_; // Return token type
}

std::string Token::getLexeme() const {
    return lexeme_; // Return token lexeme
}

std::string Token::toString() const {
    // Return formatted string to represent token
    return "<'" + lexeme_ + "'," + std::to_string(type_) + ","
    + Scanner::tokenNames[type_] + ">";
}
