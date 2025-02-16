//
// Created by lorran on 05/02/25.
//

#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

const std::string UPPERLETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string LOWERLETTERS = "abcdefghijklmnopqrstuvwxyz";
const std::string ETAOIN = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

// Concatenate uppercase, lowercase, and whitespace characters
const std::string LETTERS_AND_SPACE = UPPERLETTERS + LOWERLETTERS + " \t\n";

bool isEnglish(const std::string& message, int wordPercentage = 20, int letterPercentage = 85);
std::unordered_set<std::string> loadDictionary(const std::string& path);
double getEnglishCount(const std::string &message, const std::unordered_set<std::string> &ENGLISH_WORDS);
std::string removeNonAlpha(const std::string& text);
std::vector<std::string> splitWords(const std::string &message);
int gcd(int a, int b);
int findModInverse(int a, int m);
std::string getWordPattern(const std::string& word);
std::unordered_map<std::string, std::vector<std::string>> getWordPatterns(const std::unordered_set<std::string>& wordList);
std::unordered_map<std::string, std::vector<std::string>> allWordsPatterns();
std::unordered_map<char, int> getLetterCount(std::string message);
std::string getFrequencyOrder(const std::string& message);
int englishFrequencyMatchScore(const std::string& message);
#endif //UTILS_H
