//
// Created by lorran on 04/02/25.
//

#include "caesarCyph.h"

caesarCyph::caesarCyph(int key) : key(key) { }

std::string caesarCyph::encrypt(const std::string &text) {
    std::ostringstream result;
    for (char symbol : text) {
        if (SYMBOLS.find(symbol) != std::string::npos) {
            // it is possible to encrypt this symbol
            int symbolIndex = SYMBOLS.find(symbol);
            int encryptedIndex = symbolIndex + key;

            // Handle wrap-around
            if (encryptedIndex >= SYMBOLS.size()) {
                encryptedIndex -= SYMBOLS.size();
            } else if (encryptedIndex < 0) {
                encryptedIndex += SYMBOLS.size();
            }

            result << SYMBOLS[encryptedIndex];
        } else {
            result << symbol;
        }
    }
    return result.str();
}

std::string caesarCyph::decrypt(const std::string &text) {
    std::ostringstream result;
    for (char symbol : text) {
        size_t symbolIndex = SYMBOLS.find(symbol);
        if (symbolIndex != std::string::npos) {
            int decryptedIndex = symbolIndex - key;
            // Handle wrap-around
            if (decryptedIndex >= SYMBOLS.size()) {
                decryptedIndex -= SYMBOLS.size();
            } else if (decryptedIndex < 0) {
                decryptedIndex += SYMBOLS.size();
            }
            result << SYMBOLS[decryptedIndex];
        } else {
            result << symbol;
        }
    }
    return result.str();
}


