//
// Created by BEN on 2/8/24.
//

#ifndef scanner_hpp
#define scanner_hpp

#include "token.hpp"
#include "token_type.hpp"

class Scanner {
 public:
    static std::string tokenNames[];  // an array of strings that represent each of the tokens
    static const char eof = (char)-1; // custom end-of-file

 private:
    int length_;        // size of input buffer
    char* buffer_;      // input buffer
    int index_;         // index into input of current character
    char lookahead_;    // current character

 public:
    Scanner(int length, char* buffer);
    // Move one character; detects "end of file".
    void consume();
    // Ensure x is the next character on the input stream.
    void match(char x);
    Token nextToken();
    // Returns true if the lookahead is a letter or an underscore.
    bool isAlpha() const;
    // Returns true if the lookahead is a letter
    bool isAlphanumberic() const;
    // Returns an identifier or the keyword: 'hey', 'vous', or 'LeQuack'
    Token name();
    // Consumes a whitespace, a tab, or a line-feed.
    void whitespace();
};

#endif // scanner_hpp
