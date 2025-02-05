//
// Created by lorran on 05/02/25.
//

#include "utils.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <vector>

// A helper function to trim whitespace from both ends of a string.
std::string trim(const std::string &s) {
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start))
        ++start;

    auto end = s.end();
    do {
        --end;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

std::unordered_set<std::string> loadDictionary(const std::string &path) {
    std::unordered_set<std::string> englishWords;  // Use unordered_set for fast lookups
    std::ifstream dictionaryFile(path); // Open the file

    if (!dictionaryFile) {
        std::cerr << "Error: Unable to open " << path << std::endl;
        return englishWords; // Return empty set if file couldn't be opened
    }

    std::string word;
    while (std::getline(dictionaryFile, word)) {
        word = trim(word); // Remove leading/trailing whitespace
        std::transform(word.begin(), word.end(), word.begin(), ::toupper);
        englishWords.insert(word); // Store words in the set
    }

    dictionaryFile.close(); // Close the file
    return englishWords; // Return the dictionary as an unordered_set
}

const std::unordered_set<std::string> ENGLISH_WORDS = loadDictionary("/home/lorran/study/cpp/cript/src/dictionary.txt");

// Function to remove non-letter characters
std::string removeNonAlpha(const std::string &message) {
    std::string cleanedMessage;
    for (char ch : message) {
        if (std::isalpha(ch) || std::isspace(ch)) {
            cleanedMessage += ch;
        }
    }
    return cleanedMessage;
}

// Function to split a string into words
std::vector<std::string> splitWords(const std::string &message) {
    std::vector<std::string> words;
    std::stringstream ss(message);
    std::string word;

    while (ss >> word) {
        words.push_back(word);
    }

    return words;
}

// Function to check English word percentage
double getEnglishCount(const std::string &message, const std::unordered_set<std::string> &ENGLISH_WORDS) {
    std::string upperMessage = message;

    // Convert message to uppercase
    std::transform(upperMessage.begin(), upperMessage.end(), upperMessage.begin(), ::toupper);

    // Remove non-letter characters
    upperMessage = removeNonAlpha(upperMessage);

    // Split message into words
    std::vector<std::string> possibleWords = splitWords(upperMessage);
    if (possibleWords.empty()) {
        return 0.0; // No words at all, return 0.0
    }

    int matches = 0;
    for (const std::string &word : possibleWords) {
        if (ENGLISH_WORDS.find(word) != ENGLISH_WORDS.end()) {
            matches++;
        }
    }

    return static_cast<double>(matches) / static_cast<double>(possibleWords.size());
}

bool isEnglish(const std::string& message, const int wordPercentage, const int letterPercentage) {
    // By default, 20% of the words in the message must be English
    // and 85% of the characters in the message must be letters or spaces
    const bool wordsMatch = getEnglishCount(message, ENGLISH_WORDS) * 100 >= wordPercentage;
    const double numLetters = static_cast<double>(removeNonAlpha(message).size());
    const double messageLettersPercentage = numLetters / static_cast<double>(message.size()) * 100;
    const bool lettersMatch = messageLettersPercentage >= letterPercentage;
    return wordsMatch && lettersMatch;
}