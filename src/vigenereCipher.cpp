//
// Created by lorran on 10/02/25.
//

#include "vigenereCipher.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "utils.h"

std::string vigenereCipher::encrypt(const std::string &key, const std::string &message) const {
    return translateMessage(key, message, 1);
}

std::string vigenereCipher::decrypt(const std::string &key, const std::string &message) const {
    return translateMessage(key, message, 2);
}

std::string vigenereCipher::translateMessage(const std::string &key, const std::string &message, const int &mode) const {
    std::ostringstream result;
    int keyIndex = 0;
    std::string keyUpper = key;
    std::ranges::transform(key, keyUpper.begin(), ::toupper);

    const int symbolsSize = static_cast<int>(SYMBOLS.size());
    for (const auto symbol : message) {
        const char symbolUpper = static_cast<char>(std::toupper(static_cast<unsigned char>(symbol)));
        int index = static_cast<int>(SYMBOLS.find(symbolUpper));
        if (index != std::string::npos) {
            int shift = static_cast<int>(SYMBOLS.find(keyUpper[keyIndex]));
            if (mode == 1) {
                index += shift;
            } else {
                index -= shift;
            }
            index = (index % symbolsSize + symbolsSize) % symbolsSize; // Handle wraparound

            // Preserve the case of the original symbol
            if (std::isupper(symbol)) {
                result << SYMBOLS[index];
            } else {
                result << static_cast<char>(std::tolower(SYMBOLS[index]));
            }
            keyIndex++;
            if (keyIndex == key.size()) keyIndex = 0;
        } else {
            result << symbol;
        }
    }

    return result.str();
}

std::string vigenereCipher::hack(const std::string& message, const int& mode) {
    if (mode == 1) return dictionaryHack(message);
}

std::string vigenereCipher::dictionaryHack(const std::string &message) {
    auto englishWords = loadDictionary("/home/lorran/study/cpp/cript/src/dictionary.txt");
    for (auto word : englishWords) {
        std::string decryptedText = decrypt(word, message);
        if (isEnglish(decryptedText, 40)) {
            std::cout << "Possible decryption with key " << word << ": " << decryptedText << std::endl;
            std::cout << "Enter D for done or any other key to continue: ";
            char c;
            std::cin >> c;
            if (c == 'D' || c == 'd') {
                return decryptedText;
            }
        }
    }
    return "";
}
