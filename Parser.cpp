//
// Created by Ali Kooshesh on 10/4/23.
// Completed by Ethan Edwards on 10/15/23.
//

#include "Parser.hpp"

std::map<std::string, std::vector<std::string>> Parser::parseJSONObject() {
    Token currToken = tokenizer.getToken(); // Initial token (This MUST be an open brace)
    Token nextToken, prevToken; // Used for peeks (mostly just to catch trailing commas)
    bool isPeeking = false;
    if (currToken.toString() != "{"){ // Throw a tantrum if we didn't get what we wanted
        std::cerr << errorMessages[E_EXPECTED_OPEN_BRACE] << currToken.toString() << std::endl;
        exit(E_EXPECTED_OPEN_BRACE);
    }

    std::queue<Token> greatExpectations; // FIFO queue of expected tokens
    greatExpectations.emplace("ffff");

    prevToken = currToken;
    currToken = tokenizer.getToken();

    while (!currToken.eof()){
        if (greatExpectations.front().isQuotedString()){
            greatExpectations.pop();
            if (currToken.isQuotedString()){
                std::tuple<std::string, std::vector<std::string>> tmp = parseKeyValuePair(currToken); // Because imagine something just WORKING
                for (std::tuple<std::string, std::vector<std::string>> i : jsonObject){
                    if (std::get<0>(i) == std::get<0>(tmp)){
                        std::cerr << errorMessages[E_DUPLICATE_KEYS] << std::get<0>(i) << std::endl;
                        exit(E_DUPLICATE_KEYS);
                    }
                }
                jsonObject.emplace(std::get<0>(tmp), std::get<1>(tmp));
                greatExpectations.emplace(',');
            }
            else{
                std::cerr << errorMessages[E_EXPECTED_KEY] << currToken.toString() << std::endl;
                exit(E_EXPECTED_KEY);
            }
        }
        else if (greatExpectations.front().isComma() || greatExpectations.front().isCloseBrace()){
            greatExpectations.pop();
            bool tantrum1 = false, tantrum2 = false;
            if (currToken.isComma()){ // Comma outside of square brackets, we should be expecting a new k/v pair
                isPeeking = true;
                nextToken = tokenizer.getToken();
                if (nextToken.isCloseBrace()){
                    std::cerr << errorMessages[E_COMMA_AFTER_LAST_ITEM] << prevToken.toString() << std::endl;
                    exit(E_COMMA_AFTER_LAST_ITEM);
                }
                greatExpectations.emplace("ffff");
            } else {tantrum1 = true;}

            if (currToken.isCloseBrace()){ // Closed brace, we should be expecting an EOF
                greatExpectations.emplace();
                greatExpectations.front().flagEOF();
            } else {tantrum2 = true;}

            if (!currToken.isComma() && !currToken.isCloseBrace()){
                // Tantrum time!
                if (tantrum1){
                    std::cerr << errorMessages[E_EXPECTED_COMMA] << currToken.toString() << std::endl;
                    exit(E_EXPECTED_COMMA);
                }
                if (tantrum2){
                    std::cerr << errorMessages[E_EXPECTED_CLOSE_BRACE] << currToken.toString() << std::endl;
                    exit(E_EXPECTED_CLOSE_BRACE);
                }
            }
        } else if (greatExpectations.front().eof()){ // This should hopefully never see the light of day, but it's here just in case
            if (!currToken.eof()){
                std::cerr << errorMessages[E_EXPECTED_EOF] << currToken.toString() << std::endl;
                exit(E_EXPECTED_EOF);
            }
        }

        prevToken = currToken;
        if (isPeeking){ // Get the token for the next loop
            currToken = nextToken;
            isPeeking = false;
        } else{currToken = tokenizer.getToken();}
    }

    return jsonObject;
}

std::tuple<std::string, std::vector<std::string>> Parser::parseKeyValuePair(Token keyT){
    std::string key = keyT.toString();
    std::vector<std::string> values;

    // Wheeeeee
    Token currToken = tokenizer.getToken();
    if (!currToken.isColon()){
        std::cerr << errorMessages[E_EXPECTED_COLON] << currToken.toString() << std::endl;
        exit(E_EXPECTED_COLON);
    }

    Token prevPrevToken = currToken;
    currToken = tokenizer.getToken();
    if (!currToken.isOpenSquareBracket()){
        std::cerr << errorMessages[E_EXPECTED_OPEN_BRACKET] << currToken.toString() << std::endl;
        exit(E_EXPECTED_OPEN_BRACKET);
    }

    Token prevToken = currToken;
    currToken = tokenizer.getToken();
    while (true){
        if (!prevToken.isQuotedString() && !prevToken.isComma() && !prevToken.isOpenSquareBracket()){
            std::cerr << errorMessages[E_EXPECTED_CLOSE_BRACKET] << prevToken.toString() << std::endl;
            exit(E_EXPECTED_CLOSE_BRACKET);
        }
        if (currToken.isComma()){
            if (!prevToken.isQuotedString()){
                std::cerr << errorMessages[E_EXPECTED_VALUE] << prevToken.toString() << std::endl;
                exit(E_EXPECTED_VALUE);
            }
        }
        if (currToken.isCloseSquareBracket()){
            if (prevToken.isComma()){
                std::cerr << errorMessages[E_COMMA_AFTER_LAST_ITEM] << prevPrevToken.toString() << std::endl;
                exit(E_COMMA_AFTER_LAST_ITEM);
            }
            break;
        }
        if (currToken.isQuotedString()){
            bool foundDupe = false;
            for (std::string i : values){
                if (i == currToken.toString()){
                    foundDupe = true;
                }
            }
            if (!foundDupe){values.push_back(currToken.toString());}
        }
        prevPrevToken = prevToken;
        prevToken = currToken;
        currToken = tokenizer.getToken();
    }

    return std::tuple<std::string, std::vector<std::string>> {key, values};
}
