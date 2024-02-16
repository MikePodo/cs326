//
// Created by BEN on 2/8/24.
//

#include "token.hpp"
#include "scanner.hpp"

Token::Token() : type_(TokenType::tok_na), lexeme_("") { }

Token::Token(TokenType type, std::string lexeme) : type_(type), lexeme_(lexeme) { }

void Token::setType(TokenType type) {
    type_ = type;
}

void Token::setLexeme(std::string lexeme) {
    lexeme_ = lexeme;
}

TokenType Token::getType() const {
    return type_;
}

std::string Token::getLexeme() const {
    return lexeme_;
}

std::string Token::toString() const {
    return "<'" + lexeme_ + "'," + std::to_string(type_) + "," + Scanner::tokenNames[type_] + ">";
}
