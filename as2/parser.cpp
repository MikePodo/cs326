/*
    Name: Michael Podolsky, 2001945839, CS 326 1001, Project 2
    Description: This program scans and parses a made-up language. 
        Any invalid tokens or grammatical rules will result in an error.
    Input: parser.cpp accepts a vector of tokens from the scanner.
    Output: parser.cpp parses all of the tokens to check if they adhere
        to the grammatical rules of the language. The parser will output
        either a success or failure message.
*/
//
// Created by BEN on 2/9/24.
//

#include "parser.hpp"

Parser::Parser(std::vector<Token>& tokens) : tokens_(tokens), index_(0) {
    consume(); // Initialize Parser by consuming first token
}

void Parser::match(int x) {
    if (lookahead_.getType() == x)
        consume(); // Correct type; consume
    else {
        std::cout << "[PARSER]  Expecting " << Scanner::tokenNames[x]
            << ", but found '" << lookahead_.toString()
            << "'" << std::endl; // Print error message
        exit(0); // End program
    }
}

bool Parser::check(std::vector<TokenType> types) {
    TokenType type = lookahead_.getType(); // Obtain type 
    for (const TokenType t : types)
        if (type == t) return true; // Check passes
    return false; // Check fails
}

bool Parser::check(TokenType type) {
    // Check if lookahead type is the same as type argument
    if (lookahead_.getType() == type) {
        return true; // Return success
    }
    return false; // Return failure
}

void Parser::code() {
    // code → statement code ∣ ϵ
    if (check({ TokenType::tok_duck_fr, TokenType::tok_duck_fl,
            TokenType::tok_duck_er, TokenType::tok_bit,
            TokenType::tok_clone, TokenType::tok_dub,
            TokenType::tok_pop, TokenType::tok_mul,
            TokenType::tok_div, TokenType::tok_plus,
            TokenType::tok_minus, TokenType::tok_string,
            TokenType::tok_arrow, TokenType::tok_id, 
            TokenType::tok_keyword })) {
        statement();
        code();
    } else if (lookahead_.getType() == TokenType::tok_eof) {
        match(TokenType::tok_eof);
        // Reached end of file, parsing was successful
        std::cout << "[PARSER] success!" << std::endl;
    } else {
        std::cout << "[PARSER] Something went wrong during parsing!"
            << std::endl; // No matches and no EOF: error
        exit(0); // End program
    }
}

void Parser::statement() {
    // statement → duck_opt quacks duck_opt
    if (check({ TokenType::tok_duck_fr, TokenType::tok_duck_fl,
            TokenType::tok_duck_er, TokenType::tok_bit,
            TokenType::tok_clone, TokenType::tok_dub,
            TokenType::tok_pop, TokenType::tok_mul,
            TokenType::tok_div, TokenType::tok_plus,
            TokenType::tok_minus, TokenType::tok_string,
            TokenType::tok_arrow, TokenType::tok_id,
            TokenType::tok_keyword })) {
        duck_opt();
        quacks();
        duck_opt();
    } else {
        // No match; error
        std::cout << "[PARSER] Something went wrong during parsing!"
            << std::endl;
        exit(0); // End program
    }
}

void Parser::duck() {
    // duck → duck_facing_right ∣ duck_facing_left ∣ duck_facing_eright
    if (check(TokenType::tok_duck_fr)) {
        duck_facing_right();
    } else if (check(TokenType::tok_duck_fl)) {
        duck_facing_left();
    } else if (check(TokenType::tok_duck_er)) {
        duck_facing_eright();
    } else {
        // No match; error
        std::cout << "[PARSER] Something went wrong during parsing!"
            << std::endl;
        exit(0); // End program
    }
}

void Parser::duck_opt() {
    // duck_opt → duck ∣ ϵ
    if (check({ TokenType::tok_duck_fr,
        TokenType::tok_duck_fl,
        TokenType::tok_duck_er })) {
        duck();
    }
}

void Parser::duck_facing_right() {
    // duck_facing_right → ’@<’
    // ’### ’  
    if (check(TokenType::tok_duck_fr)) {
        match(TokenType::tok_duck_fr);
    } else {
        std::cout << "[PARSER] Something went wrong during parsing!"
            << std::endl;
        exit(0); // End program
    }
}

void Parser::duck_facing_left() {
    // duck_facing_left → ’>@’
    // ’ ###’
    if (check(TokenType::tok_duck_fl)) {
        match(TokenType::tok_duck_fl);
    } else {
        // No match; error
        std::cout << "[PARSER] Something went wrong during parsing!"
            << std::endl;
        exit(0); // End program
    }
}

void Parser::duck_facing_eright() {
    // duck_facing_eright → ’@=’
    // ’### ’
    if (check(TokenType::tok_duck_er)) {
        match(TokenType::tok_duck_er);
    } else {
        // No match; error
        std::cout << "[PARSER] Something went wrong during parsing!"
            << std::endl;
        exit(0); // End program
    }
}

void Parser::quacks() {
    // quacks → quack quacks ∣ ϵ
    if (check({ TokenType::tok_bit,
            TokenType::tok_clone, TokenType::tok_dub,
            TokenType::tok_pop, TokenType::tok_mul,
            TokenType::tok_div, TokenType::tok_plus,
            TokenType::tok_minus, TokenType::tok_string,
            TokenType::tok_arrow, TokenType::tok_id, 
            TokenType::tok_keyword })) {
        quack();
        quacks();
    }
}

void Parser::quack() {
    // quack → bit ∣ clone ∣ dub ∣ pop ∣ mul ∣ div ∣ plus ∣ sub ∣ string
    // ∣ int ∣ letter
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
        if (lookahead_.getLexeme() == "LeQuack") {
            match(TokenType::tok_keyword);
        } else {
            // If keyword is hey, then it must be followed with
            // "vous" and an id
            if (lookahead_.getLexeme() == "hey") {
                match(TokenType::tok_keyword); // Consume hey
            }
            // Check if vous follows
            match(TokenType::tok_keyword); // Consume vous
            
            // Check if dub follows
            match(TokenType::tok_dub); // Consume dub
            
            // Check if id follows
            match(TokenType::tok_id); // Consume id
        }
    } else {
        // No match; error
        std::cout << "[PARSER] Something went wrong during parsing!" 
            << std::endl;
        exit(0); // End program
    }
}

void Parser::consume() {
    lookahead_ = tokens_[index_]; // Set lookahead to index
    if ((index_ + 1) < tokens_.size()) {
        // Only increment index max to the size of vector
        index_++; // Increment index
    }
}