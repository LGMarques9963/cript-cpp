//
// Created by lorran on 05/02/25.
//

#include "utils.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
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

int gcd(int a, int b) {
    // Return the greatest common divisor of a and b using Euclid's algorithm
    while (a != 0) {
        const int temp = a;
        a = b % a;
        b = temp;
    }
    return b;
}

int findModInverse(int a, int m) {
    // Returns the modular inverse of a % m, which is the number x such that (a * x) % m == 1
    if (gcd(a, m) != 1) {
        return -1; // No mod inverse if a & m aren't coprime
    }

    // Calculate using the Extended Euclidean Algorithm
    int u1 = 1, u2 = 0, u3 = a;
    int v1 = 0, v2 = 1, v3 = m;

    while (v3 != 0) {
        int q = u3 / v3;

        // Compute the new values
        int temp_v1 = u1 - q * v1;
        int temp_v2 = u2 - q * v2;
        int temp_v3 = u3 - q * v3;

        // Shift the variables:
        u1 = v1;
        u2 = v2;
        u3 = v3;
        v1 = temp_v1;
        v2 = temp_v2;
        v3 = temp_v3;
    }

    // Ensure the result is positive
    int modInverse = u1 % m;
    if (modInverse < 0)
        modInverse += m;

    return modInverse;

}

std::string getWordPattern(const std::string& word) {
    // Returns a string of the pattern form of the given word.
    // e.g. 0.1.2.3.4.1.2.3.5.6 for 'DUSTBUSTER'
    std::string upperMessage = word;
    std::ranges::transform(upperMessage, upperMessage.begin(), ::toupper);
    int nextNum = 0;
    std::unordered_map<char, std::string> letterToNum;
    std::string pattern;

    for (auto letter : upperMessage) {
        if (!letterToNum.contains(letter)) {
            letterToNum[letter] = std::to_string(nextNum);
            nextNum++;
        }
        pattern += letterToNum[letter];
    }
    // std::cout << pattern << std::endl;
    return pattern;
}

std::unordered_map<std::string, std::vector<std::string>> getWordPatterns(const std::unordered_set<std::string>& wordList) {
    // Returns a dictionary where the keys are word patterns and the values are lists of words that match the pattern.
    std::unordered_map<std::string, std::vector<std::string>> patternWords;
    for (const auto& word : wordList) {
        std::string pattern = getWordPattern(word);
        patternWords[pattern].push_back(word);
    }
    return patternWords;
}

std::unordered_map<std::string, std::vector<std::string>> allWordsPatterns() {
    std::unordered_map<std::string, std::vector<std::string> > allPatterns = getWordPatterns(ENGLISH_WORDS);
    return allPatterns;
}

std::unordered_map<char, int> getLetterCount(std::string message) {
    std::unordered_map<char, int> letterCount;
    std::string upperMessage = message;
    std::ranges::transform(upperMessage, upperMessage.begin(), ::toupper);
    for (char letter : upperMessage) {
        if (std::isalpha(letter)) {
            letterCount[letter]++;
        }
    }
    for (char letter : UPPERLETTERS) {
        if (!letterCount.contains(letter)) {
            letterCount[letter] = 0;
        }
    }
    return letterCount;
}

std::string getFrequencyOrder(const std::string &message) {
    auto letterToFreq = getLetterCount(message);
    std::unordered_map<int, std::vector<char>> freqToLetter;
    for (auto letter : UPPERLETTERS) {
        freqToLetter[letterToFreq[letter]].push_back(letter);
    }

    // Create a new mapping from frequency to the joined string.
    std::unordered_map<int, std::string> freqToLetterStr;
    std::string freqOrder;
    for (auto &[fst, snd] : freqToLetter) {
        // pair.first is the frequency, pair.second is a vector<char>
        auto &vec = snd;

        // Sort the vector in descending order by ETAOIN order:
        std::ranges::sort(vec, [](char a, char b) {
            return ETAOIN.find(a) > ETAOIN.find(b);
        });

        // Join the vector into a string.
        std::string joined(vec.begin(), vec.end());

        // Store it in the new map.
        freqToLetterStr[fst] = joined;

        // Convert the mapping into a vector of pairs.
        std::vector<std::pair<int, std::string>> freqPairs;
        for (const auto &pair : freqToLetterStr) {
            freqPairs.emplace_back(pair);
        }

        // Sort the vector by frequency (the key, i.e. pair.first) in descending order.
        std::sort(freqPairs.begin(), freqPairs.end(), [](const auto &a, const auto &b) {
            return a.first > b.first;
        });

        // Now, build the final frequency order string by concatenating the values.
        freqOrder = "";
        for (const auto &p : freqPairs) {
            freqOrder += p.second;
        }


    }
    std::cout << "Frequency Order: " << freqOrder << std::endl;
    return freqOrder;
}

int englishFrequencyMatchScore(const std::string &message) {
    std::string frequencyOrder = getFrequencyOrder(message);
    int matchScore = 0;
    std::string etaoinFirstSix = ETAOIN.substr(0, 6);
    std::string frequencyOrderFirstSix = frequencyOrder.substr(0, 6);
    std::string etaoinLastSix = ETAOIN.substr(ETAOIN.size() - 6, 6);
    std::string freqOrderLastSix = frequencyOrder.substr(frequencyOrder.size() - 6, 6);
    for (char commonLetter : etaoinFirstSix) {
        if (frequencyOrderFirstSix.find(commonLetter) != std::string::npos) {
            matchScore++;
        }
    }

    for (char uncommonLetter : etaoinLastSix) {
        if (freqOrderLastSix.find(uncommonLetter) != std::string::npos) {
            matchScore++;
        }
    }

    return matchScore;
}
