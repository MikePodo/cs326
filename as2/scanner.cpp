//
// Created by BEN on 2/8/24.
//

#include <iostream>

#include "scanner.hpp"

std::string Scanner::tokenNames[] = {
    "n/a", "<EOF>", "BIT", "CLONE", "DUB", "POP", "MUL", "DIV", "PLUS", "MINUS",
    "STRING", "RHEAD", "LHEAD", "EHEAD", "BODY", "DUCK_FR", "DUCK_FL", "DUCK_ER",
    "LEG", "ARROW", "KEYWORD", "ID"
};

Scanner::Scanner(int length, char* buffer) : length_(length), buffer_(buffer), index_(0) {
    lookahead_ = buffer_[index_];
}

void Scanner::consume() {
    index_++; // Move one character
    lookahead_ = buffer_[index_]; // Set lookahead to next position
}

Token Scanner::nextToken() {
    TokenType tokenType; // Will hold token type
    std::string token = ""; // Will hold lexeme

    while (lookahead_ != eof && lookahead_ != '\0') { // Loop through until EOF
        switch (lookahead_) {
            case ' ': // Space
            case '\n': // Newline
            case '\r': // Newline
            case '\t': // Tab
                whitespace(); // Consume whitespace
                continue;
            case '.':
                consume(); // Consume period
                match('/'); // Ensure '/' follows
                tokenType = TokenType::tok_bit;
                token = "./";
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
            case '>':
                consume(); // Consume >
                match('@'); // Ensure "@" follows
                tokenType = TokenType::tok_lhead;
                token = ">@";
                break;

            default:
                if (isLetter()) {
                    // Check for id or keyword
                    return name();
                } else {
                    std::cerr << "[SCANNER] Invalid token!" << std::endl; // no matches; invalid
                    exit(0);
                }
        }

        if (token != "") { // Token was created
            return Token(tokenType, token); // Return created token
        }
    }

    return Token(TokenType::tok_eof, "EOF"); // Return EOF
}

void Scanner::match(char x) {
    if (lookahead_ != x) {
        std::cerr << "[SCANNER] Invalid token!" << std::endl; // invalid
        exit(0);
    }
    consume();
}

bool Scanner::isAlpha() const {
    if (lookahead_ >= 'a' && lookahead_ <= 'z' || lookahead_ >= 'A' && lookahead_ <= 'Z' || lookahead_ == '_') {
        return true; // Lookahead is a letter or underscore
    }
    return false; // Lookahead is not a letter
}

bool Scanner::isLetter() const {
    if (lookahead_ >= 'a' && lookahead_ <= 'z' || lookahead_ >= 'A' && lookahead_ <= 'Z') {
        return true; // Lookahead is a letter
    }
    return false; // Lookahead is not a letter
}

Token Scanner::name() {
    std::string stringValue = "";
    while (isAlpha()) { // Build string with all valid characters
        stringValue += lookahead_;
        consume();
    }

    if (stringValue == "hey" || stringValue == "vous" || stringValue == "LeQuack") {
        // Is a keyword, create keyword token
        return Token(TokenType::tok_keyword, stringValue);
    } else {
        // Is a regular identifier
        return Token(TokenType::tok_id, stringValue);
    }
}

void Scanner::whitespace() {
    consume();
}