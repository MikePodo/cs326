//
// Created by BEN on 2/9/24.
//

#include "parser.hpp"

Parser::Parser(std::vector<Token>& tokens) : tokens_(tokens), index_(0) {
    consume();
}

void Parser::match(int x) {
    if (lookahead_.getType() == x)
        consume();
    else {
        std::cerr << "[PARSER]  Expecting " << Scanner::tokenNames[x] << ", but found '" << lookahead_.toString()
                  << "'" << std::endl;
        exit(0);
    }
}

bool Parser::check(std::vector<TokenType> types) {
    TokenType type = lookahead_.getType();
    for (const TokenType t : types)
        if (type == t) return true;
    return false;
}

bool Parser::check(TokenType type) {
    if (lookahead_.getType() == type) { // Check if lookahead type is the same as type argument
        return true;
    }
    return false;
}

void Parser::code() {
    if (check({ TokenType::tok_duck_fr, TokenType::tok_duck_fl,
            TokenType::tok_duck_er, TokenType::tok_bit,
            TokenType::tok_clone, TokenType::tok_dub,
            TokenType::tok_pop, TokenType::tok_mul,
            TokenType::tok_div, TokenType::tok_plus,
            TokenType::tok_minus, TokenType::tok_string,
            TokenType::tok_arrow, TokenType::tok_id, TokenType::tok_keyword })) {
        statement();
        code();
    } else if (lookahead_.getType() == TokenType::tok_eof) {
        match(TokenType::tok_eof);
        std::cout << "[PARSER] Success!" << std::endl; // Reached end of file, parsing was successful
    } else {
        std::cerr << "[PARSER] Something went wrong during parsing!" << std::endl; // No matches and no EOF: error
        exit(0);
    }
}

void Parser::statement() {
    if (check({ TokenType::tok_duck_fr, TokenType::tok_duck_fl,
            TokenType::tok_duck_er, TokenType::tok_bit,
            TokenType::tok_clone, TokenType::tok_dub,
            TokenType::tok_pop, TokenType::tok_mul,
            TokenType::tok_div, TokenType::tok_plus,
            TokenType::tok_minus, TokenType::tok_string,
            TokenType::tok_arrow, TokenType::tok_id, TokenType::tok_keyword })) {
        duck_opt();
        quacks();
        duck_opt();
    } else {
        std::cerr << "[PARSER] Something went wrong during parsing!" << std::endl;
        exit(0);
    }
}

void Parser::duck() {
    if (check(TokenType::tok_duck_fr)) {
        duck_facing_right();
    } else if (check(TokenType::tok_duck_fl)) {
        duck_facing_left();
    } else if (check(TokenType::tok_duck_er)) {
        duck_facing_eright();
    } else {
        std::cerr << "[PARSER] Something went wrong during parsing!" << std::endl;
        exit(0);
    }
}

void Parser::duck_opt() {
    if (check({ TokenType::tok_duck_fr, TokenType::tok_duck_fl, TokenType::tok_duck_er })) {
        duck();
    }
}

void Parser::duck_facing_right() {
    if (check(TokenType::tok_duck_fr)) {
        match(TokenType::tok_duck_fr);
    } else {
        std::cerr << "[PARSER] Something went wrong during parsing!" << std::endl;
        exit(0);
    }
}

void Parser::duck_facing_left() {
    if (check(TokenType::tok_duck_fl)) {
        match(TokenType::tok_duck_fl);
    } else {
        std::cerr << "[PARSER] Something went wrong during parsing!" << std::endl;
        exit(0);
    }
}

void Parser::duck_facing_eright() {
    if (check(TokenType::tok_duck_er)) {
        match(TokenType::tok_duck_er);
    } else {
        std::cerr << "[PARSER] Something went wrong during parsing!" << std::endl;
        exit(0);
    }
}

void Parser::quacks() {
    if (check({ TokenType::tok_bit,
            TokenType::tok_clone, TokenType::tok_dub,
            TokenType::tok_pop, TokenType::tok_mul,
            TokenType::tok_div, TokenType::tok_plus,
            TokenType::tok_minus, TokenType::tok_string,
            TokenType::tok_arrow, TokenType::tok_id, TokenType::tok_keyword })) {
        quack();
        quacks();
    }
}

void Parser::quack() {
    if (check(TokenType::tok_bit)) {
        match(TokenType::tok_bit);
    } else if (check(TokenType::tok_clone)) {
        match(TokenType::tok_clone);
    } else if (check(TokenType::tok_dub)) {
        match(TokenType::tok_dub);
    } else if (check(TokenType::tok_pop)) {
        match(TokenType::tok_pop);
    } else if (check(TokenType::tok_mul)) {
        match(TokenType::tok_mul);
    } else if (check(TokenType::tok_div)) {
        match(TokenType::tok_div);
    } else if (check(TokenType::tok_plus)) {
        match(TokenType::tok_plus);
    } else if (check(TokenType::tok_minus)) {
        match(TokenType::tok_minus);
    } else if (check(TokenType::tok_string)) {
        match(TokenType::tok_string);
    } else if (check(TokenType::tok_arrow)) {
        match(TokenType::tok_arrow);
    } else if (check(TokenType::tok_id)) {
        match(TokenType::tok_id);
    } else if (check(TokenType::tok_keyword)) {
        match(TokenType::tok_keyword);
    } else {
        std::cerr << "[PARSER] Something went wrong during parsing!" << std::endl;
        exit(0);
    }
}

void Parser::consume() {
    lookahead_ = tokens_[index_]; // Set lookahead to index
    index_++; // Increment index
}
