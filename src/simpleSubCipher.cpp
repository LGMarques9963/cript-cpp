//
// Created by lorran on 06/02/25.
//

#include "simpleSubCipher.h"

#include <iostream>
#include <random>
#include <algorithm>
std::string simpleSubCipher::encryptMessage(const std::string& key, const std::string& message) {
    if (!keyIsValid(key)) {
        std::cerr << "Invalid key." << std::endl;
        return "";
    }
    return translateMessage(key, message, 1);
}

std::string simpleSubCipher::decryptMessage(const std::string& key, const std::string& message) {
    if (!keyIsValid(key)) {
        std::cerr << "Invalid key." << std::endl;
        return "";
    }
    return translateMessage(key, message, 2);
}

std::string simpleSubCipher::translateMessage(const std::string &key, const std::string &message, const int &mode) const {
    std::string translated;
    std::string charsA = SYMBOLS;
    std::string charsB = key;

    if (mode == 2) std::swap(charsA, charsB); // Swap the symbols if decrypting

    for (char symbol : message) {
        char symbolUpper = static_cast<char>(std::toupper(static_cast<unsigned char>(symbol)));
        size_t index = charsA.find(symbolUpper);
        if (index != std::string::npos) {
            char translatedChar = charsB[index];

            // Preserve the case of the original symbol
            if (std::isupper(static_cast<unsigned char>(symbol)))
                translated.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(translatedChar))));
            else
                translated.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(translatedChar))));
        } else {
            // Symbol is not in the symbol set, add it as is
            translated.push_back(symbol);
        }
    }
    return translated;
}

std::string simpleSubCipher::generateRandomKey() const {
    std::string key = SYMBOLS;
    std::random_device rd;
    std::mt19937 g(rd());
    std::ranges::shuffle(key, g);
    return key;
}

bool simpleSubCipher::keyIsValid(const std::string &key) const {
    if (key.size() != SYMBOLS.size()) {
        return false;
    }
    std::string temp = key;
    std::ranges::sort(temp);
    return temp == SYMBOLS;
}
