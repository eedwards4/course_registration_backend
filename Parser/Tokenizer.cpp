// Created by Ali Kooshesh on 9/26/23.
// Completed by Ethan Edwards on 10/15/23.
//
#include <iostream>
#include "Tokenizer.hpp"
#include "../constants.hpp"

Tokenizer::Tokenizer(std::string inputFileName) {
    inputStream.open(inputFileName, std::ios::in);
}

// Public
Token Tokenizer::getToken() {
    char c;
    inputStream >> c;
    currToken = Token(c);

    if (inputStream.eof()){ // Check for EOF
        currToken = Token();
        currToken.flagEOF();
        return currToken;
    }

    if (currToken.symbol() == '"'){ // Check for quoted strings
        ungetToken();
        currToken = readQuotedString();
    }

    if (currToken.toString() == "Unknown token!"){ // Check for bad tokens. THIS HAS TO COME AFTER SPECIAL CHECKS, OR IT WILL THROW AN EXCEPTION
        std::cerr << errorMessages[E_BAD_TOKEN] << c << std::endl;
        exit(E_BAD_TOKEN);
    }

    return currToken;
}

void Tokenizer::ungetToken() {
    lastToken = currToken;
    _hasUngottenToken = true;
}

// Private
bool Tokenizer::isASymbol(char c) {
    if (c == ':' || c == ','){return true;}
    return false;
}

std::string Tokenizer::readQuotedString() {
    char inChar;
    std::string outStr;
    inChar = lastToken.symbol();
    _hasUngottenToken = false;

    if (inChar != '"'){ // Return empty string if the first character is not '"'
        return outStr;
    }

    noskipws(inputStream); // Make sure we capture spaces within the string
    inputStream >> inChar;

    while (inChar != '"'){
        if (inputStream.eof()){ // Throw an exception if we hit the end of the file without a closing quote
            std::cerr << errorMessages[E_BAD_TOKEN] << inChar << std::endl;
            exit(E_BAD_TOKEN);
        }
        outStr.push_back(inChar);
        inputStream >> inChar;
    }

    skipws(inputStream); // Set the flag back to normal, so that the tokenizer behaves like a tokenizer
    return outStr;
}
