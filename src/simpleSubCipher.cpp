//
// Created by lorran on 06/02/25.
//

#include "simpleSubCipher.h"

#include <iostream>
#include <random>
#include <algorithm>
#include <unordered_map>
#include "utils.h"

std::string simpleSubCipher::encryptMessage(const std::string& key, const std::string& message) const {
    if (!keyIsValid(key)) {
        std::cerr << "Invalid key." << std::endl;
        return "";
    }
    return translateMessage(key, message, 1);
}

std::string simpleSubCipher::decryptMessage(const std::string& key, const std::string& message) const {
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

std::unordered_map<char, std::vector<std::string>> simpleSubCipher::getBlankCipherletterMapping() {
    // Returns a dictionary value that is a blank cipherletter mapping
    std::unordered_map<char, std::vector<std::string>> cipherletterMapping;
    for (char symbol : SYMBOLS) {
        cipherletterMapping[symbol] = std::vector<std::string>();
    }
    return cipherletterMapping;
}


std::string simpleSubCipher::hack(const std::string& message) {
    std::unordered_map<char, std::vector<std::string>> intersectedMap = getBlankCipherletterMapping();
    std::string messageUpper = message;
    std::ranges::transform(message, messageUpper.begin(), ::toupper);
    std::cout << messageUpper << std::endl;
    std::string cleanedMessage = removeNonAlpha(messageUpper);
    std::vector<std::string> cipherwordList = splitWords(cleanedMessage);
    auto allPatterns = allWordsPatterns();
    for (const auto& word : cipherwordList) {
        // Get a new cipherletter mapping for each ciphertext word
        auto candidateMap = getBlankCipherletterMapping();
        auto wordPattern = getWordPattern(word);
        if (!allPatterns.contains(wordPattern)) continue; // Skip words not in the dictionary
        for (const auto& candidate : allPatterns.at(wordPattern)) {
            addLettersToMapping(candidateMap, word, candidate);
        }
        intersectedMap = intersectMappings(intersectedMap, candidateMap);

    }
    std::unordered_map<char, std::vector<std::string>> hackedLetterMapping = removeSolvedLettersFromMapping(intersectedMap);
    std::string hackedMessage = decryptWithCipherletterMapping(message, hackedLetterMapping);
    return hackedMessage;
}

void simpleSubCipher::addLettersToMapping(std::unordered_map<char, std::vector<std::string>> &letterMapping, const std::string &word, const std::string &candidate) {
    /*
     * The letterMapping parameter takes a dictionary value that stores a cipherletter mapping, which is copied by the functino.
     * The word parameter is the ciphertext word for which the mapping is being determined.
     * The candidate parameter is a possible English word that the ciphertext word could decrypt to.
     *
     * This function adds the letters in the candidate as potential decryption letters for the ciphertext word.
     */
    for (int i=0; i<word.size();i++) {
      char cipherLetter = word[i];

      std::string candidateLetter(1,candidate[i]);

      auto &vec = letterMapping[cipherLetter];
        if (std::find(vec.begin(), vec.end(), candidateLetter) == vec.end()) {
              vec.push_back(candidateLetter);
        }
    }
}

std::unordered_map<char, std::vector<std::string> > simpleSubCipher::intersectMappings(const std::unordered_map<char, std::vector<std::string> > &mapA, const std::unordered_map<char, std::vector<std::string> > &mapB) {
    // To intersect two maps, create a blank map and then add onlye the potential decryption letters if they exist in BOTH maps:
    std::unordered_map<char, std::vector<std::string>> intersectedMap = getBlankCipherletterMapping();
    for (char letter : SYMBOLS) {
        if (mapA.at(letter).empty()) intersectedMap[letter] = mapB.at(letter);
        else if (mapB.at(letter).empty()) intersectedMap[letter] = mapA.at(letter);
        for (const auto& mappedLetter : mapA.at(letter)) {
            if (std::ranges::find(mapB.at(letter), mappedLetter) != mapB.at(letter).end()) {
                intersectedMap[letter].push_back(mappedLetter);
            }
        }
    }
    return intersectedMap;
}

std::unordered_map<char, std::vector<std::string>> simpleSubCipher::removeSolvedLettersFromMapping(
    std::unordered_map<char, std::vector<std::string> > &letterMapping) {
    /*
     * Cipherletters in the mapping that map to only one letter are "solved" and can be removed from the other letters.
     * For example, if 'A' maps to potential letters ['M','N'], and 'B' maps to ['N'], then we know 'B' must map to 'N'.
     * So we remove 'N' from the list of potential letters for 'A'.
     */
    bool loopAgain = true;
    while (loopAgain) {
        loopAgain = false;

        // solvedLetters will be a list of letters that have one and only one possible mapping in letterMapping
        std::vector<std::string> solvedLetters;
        for (const auto& [cipherletter, candidates] : letterMapping) {
            if (candidates.size() == 1) {
                solvedLetters.push_back(candidates[0]);
            }
        }

        // If a letter is solved, then it cannot possible be a potential decryption letter for a different ciphertext letter
        for (const auto& cipherLetter : SYMBOLS) {

            // Access the candidate vector for this cipherLetter.
            std::vector<std::string> &candidates = letterMapping[cipherLetter];
            for (const auto& solved : solvedLetters) {
                if (candidates.size() != 1 && std::ranges::find(candidates, solved) != candidates.end()) {
                        if (auto newEnd = std::ranges::remove(candidates, solved).begin(); newEnd != candidates.end()) {
                            candidates.erase(newEnd, candidates.end());
                            letterMapping[cipherLetter].size() == 1 ? loopAgain = true : loopAgain = false;
                        }
                    }


            }
        }
    }
    return letterMapping;
}

std::string simpleSubCipher::decryptWithCipherletterMapping(const std::string &message, std::unordered_map<char, std::vector<std::string> > &letterMapping) {
    // Return a string of the ciphertext decrypted with the letter mapping, with any ambiguous letters replaced with an underscore

    // First create a simple sub key from the letterMapping
    std::string key(SYMBOLS.size(), 'x');

    // Local copy to be able to modify the message
    std::string modifiedCiphertext = message;
    for (const auto &cipherLetter : SYMBOLS) {
        auto it = letterMapping.find(cipherLetter);
        if (it != letterMapping.end() && it->second.size() == 1) {
            // There's only one candidate for this letter, so add it to the key
            std::string candidateLetter = it->second[0];

            // Find the index of the candidate letter in the SYMBOLS string
            size_t keyIndex = SYMBOLS.find(candidateLetter);
            if (keyIndex != std::string::npos) {
                key[keyIndex] = cipherLetter;
            }
        } else {
            // If there's ambiguity for this letter, replace the letter in the message with an underscore
            for (char &c : modifiedCiphertext) {
                if (c == static_cast<char>(std::tolower(cipherLetter)) || c == static_cast<char>(std::toupper(cipherLetter))) {
                    c = '_';
                }
            }
        }
    }
    return decryptMessage(key, modifiedCiphertext);
}


void printLetterMapping(const std::unordered_map<char, std::vector<std::string>> &letterMapping) {
    for (const auto &entry : letterMapping) {
        std::cout << entry.first << " : ";
        for (const auto &candidate : entry.second) {
            std::cout << candidate << " ";
        }
        std::cout << std::endl;
    }
}
