//
// Created by lorran on 05/02/25.
//

#include "affineCipher.h"

#include <cassert>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

#include "utils.h"

std::tuple<int, int> affineCipher::getKeyParts(const int key) const {
    // Assert that SYMBOLS.size() fits within an int
    assert(SYMBOLS.size() <= static_cast<size_t>(std::numeric_limits<int>::max()));

    int keyA = key / static_cast<int>(SYMBOLS.size());
    int keyB = key % static_cast<int>(SYMBOLS.size());
    return std::make_tuple(keyA, keyB);
}

void affineCipher::checkKeys(const int keyA, const int keyB, const int mode) const {
    // Assert that SYMBOLS.size() fits within an int
    assert(SYMBOLS.size() <= static_cast<size_t>(std::numeric_limits<int>::max()));

    if (mode == 1) {
        if (keyA < 0 || keyB < 0 || keyB > static_cast<int>(SYMBOLS.size()) - 1) {
            throw std::invalid_argument("Invalid keys for encryption.");
        }
    } if (mode == 2) {
        if (keyA < 0 || keyB < 0 || keyB > static_cast<int>(SYMBOLS.size()) - 1) {
            throw std::invalid_argument("Invalid keys for decryption.");
        }
    }

    if (gcd(keyA, static_cast<int>(SYMBOLS.size())) != 1) {
        throw std::invalid_argument("Key A and the size of the symbol set must be coprime.");
    }
}

std::string affineCipher::encryptMessage(const int key, const std::string &message) const {
    auto [keyA, keyB] = getKeyParts(key);
    checkKeys(keyA, keyB, 1);

    std::ostringstream result;
    for (const char symbol : message) {
        if (SYMBOLS.find(symbol) != std::string::npos) {
            const int symbolIndex = static_cast<int>(SYMBOLS.find(symbol));
            result << SYMBOLS[(symbolIndex * keyA + keyB) % SYMBOLS.size()];
        } else {
            result << symbol;
        }
    }
    return result.str();
}

std::string affineCipher::decryptMessage(const int key, const std::string &message) const {
    auto [keyA, keyB] = getKeyParts(key);
    checkKeys(keyA, keyB, 2);

    const int modInverse = findModInverse(keyA, static_cast<int>(SYMBOLS.size()));
    std::ostringstream result;
    for (const char symbol : message) {
        if (SYMBOLS.find(symbol) != std::string::npos) {
            const int symbolIndex = static_cast<int>(SYMBOLS.find(symbol));
            // Calculate decrypted index and adjust for negative values
            int decryptedIndex = modInverse * (symbolIndex - keyB);
            decryptedIndex %= static_cast<int>(SYMBOLS.size());
            if (decryptedIndex < 0) {
                decryptedIndex += static_cast<int>(SYMBOLS.size());
            }
            result << SYMBOLS[decryptedIndex];
        } else {
            result << symbol;
        }
    }
    return result.str();
}

int affineCipher::getRandomKey() const {
    // Assert that SYMBOLS.size() fits within an int
    assert(SYMBOLS.size() <= static_cast<size_t>(std::numeric_limits<int>::max()));

    int keyA = 0;
    int keyB = 0;
    while (true) {
        keyA = 2 + rand() % static_cast<int>(SYMBOLS.size());
        keyB = 2 + rand() % static_cast<int>(SYMBOLS.size());
        std::cout << "Key A: " << keyA << " Key B: " << keyB << std::endl;
        if (gcd(keyA, static_cast<int>(SYMBOLS.size())) == 1) {
            break;
        }
    }
    return keyA * static_cast<int>(SYMBOLS.size()) + keyB;
}
