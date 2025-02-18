//
// Created by lorran on 04/02/25.
//

#include "caesarCyph.h"

#include <iostream>

#include "utils.h"

// Constructor: store the key
caesarCyph::caesarCyph(const int key) : key(key) { }

/*
 * Encrypts the given text using the Caesar Cipher shift.
 *
 * 1. If the current character (symbol) is in SYMBOLS,
 *    we find its index in the SYMBOLS string.
 * 2. We add 'key' to this index for the new position,
 *    handling wrap-around if the new index exceeds size().
 * 3. Otherwise (symbol is not in SYMBOLS), we leave it as is.
 */
std::string caesarCyph::encrypt(const std::string &text) const {
    std::ostringstream result;
    for (const char symbol : text) {
        // If the symbol is recognized in SYMBOLS, shift it forward by 'key' positions
        if (SYMBOLS.find(symbol) != std::string::npos) {
            int symbolIndex = SYMBOLS.find(symbol);
            int encryptedIndex = symbolIndex + key;

            // Handle wrap-around if index exceeds symbol list length
            if (encryptedIndex >= static_cast<int>(SYMBOLS.size())) {
                encryptedIndex -= SYMBOLS.size();
            } else if (encryptedIndex < 0) {
                encryptedIndex += SYMBOLS.size();
            }

            result << SYMBOLS[encryptedIndex];
        } else {
            // If the symbol is not recognized, add it as is
            result << symbol;
        }
    }
    return result.str();
}

/*
 * Decrypts the given text using the Caesar Cipher shift.
 *
 * 1. If symbol is in SYMBOLS, we subtract 'key' to find its original position.
 * 2. Wrap-around if the index is negative or beyond the end.
 * 3. If symbol isn't in SYMBOLS, we leave it as is.
 */
std::string caesarCyph::decrypt(const std::string &text) const {
    return decrypt(text, key);
}

/*
 * Overloaded decrypt that takes an explicit key, so we can try different shifts
 * (useful for brute forcing or "hacking").
 */
std::string caesarCyph::decrypt(const std::string &text, const int& key) const {
    std::ostringstream result;
    for (const char symbol : text) {
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
            // Unrecognized symbol remains unchanged
            result << symbol;
        }
    }
    return result.str();
}

// Brute force: try every possible 'key' in SYMBOLS
void caesarCyph::hack(const std::string &text) const {
    for (int key = 0; key < SYMBOLS.size(); key++) {
        std::string decrypted = decrypt(text, key);
        std::cout << "Key: " << key << " - " << decrypted << std::endl;
    }
}
