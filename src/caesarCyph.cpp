//
// Created by lorran on 04/02/25.
//

#include "caesarCyph.h"

#include <iostream>

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

std::string caesarCyph::decrypt(const std::string &text){
    std::ostringstream result;
    for (char symbol : text) {
        size_t symbolIndex = SYMBOLS.find(symbol);
        if (symbolIndex != std::string::npos) {
            // Cast symbolIndex to signed int for correct arithmetic
            int decryptedIndex = static_cast<int>(symbolIndex) - key;
            if (decryptedIndex < 0) {
                decryptedIndex += static_cast<int>(SYMBOLS.size());
            }
            // Handle wrap-around
            if (decryptedIndex >= SYMBOLS.size()) {
                decryptedIndex -= static_cast<int>(SYMBOLS.size());
            }

            result << SYMBOLS[decryptedIndex];
        } else {
            result << symbol;
        }
    }
    return result.str();
}

std::string caesarCyph::decrypt(const std::string &text, const int& key) {
    std::ostringstream result;
    for (char symbol : text) {
        size_t symbolIndex = SYMBOLS.find(symbol);
        if (symbolIndex != std::string::npos) {
            // Cast symbolIndex to signed int for correct arithmetic
            int decryptedIndex = static_cast<int>(symbolIndex) - key;
            if (decryptedIndex < 0) {
                decryptedIndex += static_cast<int>(SYMBOLS.size());
            }
            // Handle wrap-around
            if (decryptedIndex >= SYMBOLS.size()) {
                decryptedIndex -= static_cast<int>(SYMBOLS.size());
            }
            result << SYMBOLS[decryptedIndex];
        } else {
            result << symbol;
        }
    }
    return result.str();
}

void caesarCyph::hack(const std::string &text) {
    // Loop through all possible keys
    std::string decrypted = "";
    for (int key = 0; key < SYMBOLS.size(); key++) {
        decrypted = decrypt(text, key);
        std::cout << "Key: " << key << " - " << decrypted << std::endl;
    }
}
