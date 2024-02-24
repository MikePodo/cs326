/*
    Name: Michael Podolsky, 2001945839, CS 326 1001, Project 2
    Description: This program scans and parses a made-up language. 
        Any invalid tokens or grammatical rules will result in an error.
    Input: scanner.cpp accepts a buffer of all the characters in the 
        provided code file.
    Output: scanner.cpp checks that all tokens and characters are valid 
    within the language. It ultimately builds a vector of tokens that 
    gets stored in main.cpp (which calls the scanner)
*/
//
// Created by BEN on 2/8/24.
//

#include <iostream>

#include "scanner.hpp"

std::string Scanner::tokenNames[] = {
    "n/a", "<EOF>", "BIT", "CLONE", "DUB", "POP", "MUL", "DIV", "PLUS",
    "MINUS", "STRING", "RHEAD", "LHEAD", "EHEAD", "BODY", "DUCK_FR",
    "DUCK_FL", "DUCK_ER", "LEG", "ARROW", "KEYWORD", "ID", "COMMENT",
    "DUCK_ERL", "INT"
};

Scanner::Scanner(int length, char* buffer) : length_(length),
    buffer_(buffer), index_(0) {
    lookahead_ = buffer_[index_];
}

void Scanner::consume() {
    index_++; // Move one character
    lookahead_ = buffer_[index_]; // Set lookahead to next position
}

Token Scanner::nextToken() {
    TokenType tokenType = TokenType::tok_na; // Will hold token type
    std::string token = ""; // Will hold lexeme

    // Loop through until EOF
    while (lookahead_ != eof && lookahead_ != '\0') {
        // std::cout << "lookahead: " << lookahead_ << std::endl;
        switch (lookahead_) {
            case ' ': // Space
            case '\n': // Newline
            case '\r': // Newline
            case '\t': // Tab
                whitespace(); // Consume whitespace
                continue;
            case '.':
                consume(); // Consume period

                if (lookahead_ == ' ') {
                    match(' '); // Consume space
                    match('o'); // Consume 'o'
                    match(' '); // Consume space
                    match('O'); // Consume 'O'
                    match(' '); // Consume space
                    break;
                }

                // Not a comment, must be bit
                match('/'); // Ensure '/' follows
                tokenType = TokenType::tok_bit;
                token = "./";
                break;
            case '(':
                while (lookahead_ != ')') {
                    consume(); // Consume comment characters
                }
                consume(); // Reached end of comment
                tokenType = TokenType::tok_comment;
                token = "";
                break;
            case ',':
                consume(); // Consume comma
                match('/'); // Ensure '/' follows
                tokenType = TokenType::tok_clone;
                token = ",/";
                break;
            case '/':
                consume(); // Consume slash
                match('/'); // Ensure '/' follows
                tokenType = TokenType::tok_div;
                token = "//";
                break;
            case '!':
                consume(); // Consume exclamation point
                tokenType = TokenType::tok_dub;
                token = "!";
                break;
            case '?':
                consume(); // Consume question mark
                tokenType = TokenType::tok_pop;
                token = "?";
                break;
            case '+':
                consume(); // Consume plus
                tokenType = TokenType::tok_plus;
                token = "+";
                break;
            case '*':
                consume(); // Consume star
                tokenType = TokenType::tok_mul;
                token = "*";
                break;
            case '-':
                consume(); // Consume hyphen
                if (lookahead_ == '>') {
                    // arrow
                    consume();
                    tokenType = TokenType::tok_arrow;
                    token = "->";
                } else {
                    // minus
                    consume();
                    tokenType = TokenType::tok_minus;
                    token = "-";
                }
                break;
            case '%':
                consume(); // Consume percent
                tokenType = TokenType::tok_string;
                token = "%";
                break;
            case '#':
                consume(); // Consume pound
                match('#'); // Ensure "#" follows
                match('#'); // Ensure "#" follows
                tokenType = TokenType::tok_body;
                token = "###";
                break;

            case '`':
                consume(); // Consume leg
                tokenType = TokenType::tok_leg;
                token = "`";
                break;
            case '@':
                consume(); // Consume 'at'
                if (lookahead_ == '<') {
                    // head fr
                    consume();
                    tokenType = TokenType::tok_rhead;
                    token = "@<";
                } else if (lookahead_ == '=') {
                    // head er
                    consume();
                    tokenType = TokenType::tok_ehead;
                    token = "@=";
                }
                break;
            case '=':
                consume(); // Consume =
                match('@'); // Ensure '@' follows
                tokenType = TokenType::tok_ehead;
                token = "=@";
                break;
            case '>':
                consume(); // Consume >
                match('@'); // Ensure "@" follows
                tokenType = TokenType::tok_lhead;
                token = ">@";
                break;
            default:
                if (isAlphanumberic()) {
                    // Check for id or keyword
                    return name();
                } else {
                    std::cout << "[SCANNER] unknown character found '"
                        << lookahead_ << "'" << std::endl; // invalid
                     // no matches; invalid
                    exit(0);
                }
        }

        if (tokenType != TokenType::tok_na) { // Token was created
            return Token(tokenType, token); // Return created token
        }
    }

    return Token(TokenType::tok_eof, "<EOF>"); // Return EOF
}

void Scanner::match(char x) {
    if (lookahead_ != x) {
        std::cout << "[SCANNER] unknown character found '"
            << lookahead_ << "'" << std::endl; // invalid
        exit(0);
    }
    consume(); // If valid, consume the character
}

bool Scanner::isAlpha() const {
    if (lookahead_ >= 'a' && lookahead_ <= 'z' || lookahead_ >= 'A'
        && lookahead_ <= 'Z' || lookahead_ == '_') {
        return true; // Lookahead is a letter or underscore
    }
    return false; // Lookahead is not a letter
}

bool Scanner::isAlphanumberic() const {
    if (lookahead_ >= 'a' && lookahead_ <= 'z' || 
        lookahead_ >= 'A' && lookahead_ <= 'Z' || 
        lookahead_ >= '0' && lookahead_ <= '9') {
        return true; // Lookahead isalphanumeric
    }
    return false; // Lookahead is not alphanumeric
}

Token Scanner::name() {
    std::string stringValue = "";

    if (lookahead_ >= '0' && lookahead_ <= '9') { // is Int
        while (lookahead_ >= '0' && lookahead_ <= '9') { 
            // Build string with all valid numbers
            stringValue += lookahead_;
            consume();
        }
        return Token(TokenType::tok_int, stringValue);
    }

    // Otherwise it is a string (non-numeric)
    while (isAlpha()) { // Build string with all valid characters
        stringValue += lookahead_;
        consume();
    }

    if (stringValue == "hey"
        || stringValue == "vous"
        || stringValue == "LeQuack") {
        // Is a keyword, create keyword token
        return Token(TokenType::tok_keyword, stringValue);
    } else {
        // Is a regular identifier
        return Token(TokenType::tok_id, stringValue);
    }
}

void Scanner::whitespace() {
    consume(); // Consume whitespace but do nothing with it
}