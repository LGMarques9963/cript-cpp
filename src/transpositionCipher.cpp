//
// Created by lorran on 04/02/25.
//

#include "transpositionCipher.h"
#include "utils.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>

std::string transpositionCipher::encrypt(const int &key, const std::string &text) {
    std::pmr::vector<std::string> cipherText(key);

    for (int column = 0; column < key; ++column) {
        int currentIndex = column;
        while (currentIndex < text.size()) {
            cipherText[column] += text[currentIndex];
            currentIndex += key;
        }
    }
    std::string result;
    for (const auto &column : cipherText) {
        result += column;
    }
    return result;
}

std::string transpositionCipher::decrypt(const int &key, const std::string &text) {
    int numOfColumns = static_cast<int>(std::ceil(static_cast<double>(text.size()) / key));
    int numOfRows = key;
    int numOfShadedBoxes = (numOfColumns * numOfRows) - static_cast<int>(text.size());

    std::vector<std::string> plainText(numOfColumns);

    int column = 0, row = 0;

    for (char symbol : text) {
        plainText[column] += symbol;
        column += 1;

        if (column == numOfColumns || (column == numOfColumns - 1 && row >= numOfRows - numOfShadedBoxes)) {
            column = 0;
            row += 1;
        }
    }

    std::string result;
    for (const auto& col : plainText) {
        result += col;
    }
    return result;
}

std::string transpositionCipher::hack(const std::string &text) {
    std::cout << "Hacking transposition cipher ..." << std::endl;

    // Brute-force by trying all possible keys
    for (int key = 1; key < text.size(); ++key) {
        //std::cout << "Trying key " << key << " ... " << std::endl;
        if (std::string result = decrypt(key, text); isEnglish(result)) {
            std::cout << "Success! Possible Decrypted message with key " << key << ": " << result << std::endl;
            /*std::cout << "Press D to decrypt the message, or any other key to try other keys: " << std::endl;
            char choice;
            std::cin >> choice;
            if (choice == 'D' || choice == 'd') {
                return result;
            }*/
            return result;
        }
    }
    return "Failed to decrypt the message.";
}