//
// Created by lorran on 05/02/25.
//

#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <unordered_set>
#include <vector>

const std::string UPPERLETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string LOWERLETTERS = "abcdefghijklmnopqrstuvwxyz";

// Concatenate uppercase, lowercase, and whitespace characters
const std::string LETTERS_AND_SPACE = UPPERLETTERS + LOWERLETTERS + " \t\n";

bool isEnglish(const std::string& message, int wordPercentage = 20, int letterPercentage = 85);
std::unordered_set<std::string> loadDictionary(const std::string& path);
double getEnglishCount(const std::string &message, const std::unordered_set<std::string> &ENGLISH_WORDS);
std::string removeNonAlpha(const std::string& text);
std::vector<std::string> splitWords(const std::string &message);

#endif //UTILS_H
