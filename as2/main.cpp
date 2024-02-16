#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#include "scanner.hpp"
#include "parser.hpp"
#include "token.hpp"

using namespace std;

Token createDuck(const Token& head, const Token& body) {
    switch (head.getType()) {
        case TokenType::tok_rhead:return { TokenType::tok_duck_fr, "@<\n###" };
        case TokenType::tok_ehead:return { TokenType::tok_duck_er, "@=\n###" };
        case TokenType::tok_lhead:return { TokenType::tok_duck_fl, ">@\n   ###" };
        default:return { TokenType::tok_na, "" };
    }
}

int find(const vector<Token>& tokens, Token& tok) {
    for (int i = 0; i < tokens.size(); ++i)
        if (tokens[i].getType() == tok.getType())
            return i;
    return -1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Invalid command-line arguments!" << endl;
        exit(0);
    }
    // Open file to read
    ifstream infile(argv[1]);
    if (!infile) {
        cerr << "Could not open file '" << argv[1] << "'" << endl;
        exit(0);
    }
    // Compute the number of bytes needed to allocate memory
    // for the stream buffer.
    infile.seekg(0, std::ifstream::end);
    size_t length = infile.tellg();
    infile.seekg(0, std::ifstream::beg);
    char* buffer = new char[int(length) + 1];
    infile.read(buffer, int(length));
    if (!infile) {
        cerr << "Could not read file '" << argv[1] << "'" << endl;
        exit(0);
    }
    // Buffer contains the entire input so null-terminate it.
    infile.close();
    buffer[length] = '\0';
    // Create a scanner that feeds off the input buffer.
    Scanner scanner(int(length), buffer);
    cout << "Scanning the file..." << endl;
    vector<Token> tokens;
    
    cout << "Scanning done!" << endl << endl;
    cout << "List of tokens:" << endl;
    Token currentToken = scanner.nextToken(); // Get first token
    do {
        tokens.push_back(currentToken); // Append token
        cout << currentToken.toString() << endl; // Print token
        currentToken = scanner.nextToken(); // Move to next token
    } while (currentToken.getType() != TokenType::tok_eof);
    tokens.push_back(currentToken); // Add EOF token
    cout << currentToken.toString() << endl; // Print EOF token
    
    cout << endl << "Rewriting some tokens..." << endl << endl;
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i].getType() == TokenType::tok_rhead || tokens[i].getType() == TokenType::tok_lhead || tokens[i].getType() == TokenType::tok_ehead) {
            // Found a head, now need to find the nearest body
            for (int j = i + 1; j < tokens.size(); j++) {
                // Loop through remaining tokens to find a body
                if (tokens[j].getType() == TokenType::tok_body) { // Found body
                    Token fullDuck = createDuck(tokens[i], tokens[j]);
                    // Insert fullDuck at head position, remove existing head and body
                    tokens[i] = fullDuck;
                    tokens.erase(tokens.begin() + j);
                    break;
                }
            }
        }
    }
 
    cout << "List of new tokens:" << endl;
    for (int i = 0; i < tokens.size(); i++) {
        cout << tokens[i].toString() << endl;
    }

    // Create a parser that feeds off the scanner.
    cout << "\nParsing file..." << endl;
    Parser parser(tokens);
    
    parser.code();
    return 0;
}
