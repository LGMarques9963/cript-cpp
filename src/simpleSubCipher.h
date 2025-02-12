//
// Created by lorran on 06/02/25.
//

#ifndef SIMPLESUBCIPHER_H
#define SIMPLESUBCIPHER_H
#include <string>
#include <unordered_map>
#include <vector>

class simpleSubCipher {
    const std::string SYMBOLS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    [[nodiscard]] bool keyIsValid(const std::string& key) const;
    std::unordered_map<char, std::vector<std::string>> getBlankCipherletterMapping();
    void addLettersToMapping(std::unordered_map<char, std::vector<std::string>> &letterMapping, const std::string &word, const std::string &
                             candidate);
    std::unordered_map<char, std::vector<std::string>> intersectMappings(const std::unordered_map<char, std::vector<std::string>> & pairs, const std::unordered_map<char, std::vector<std::string>> & candidate_map);

    std::unordered_map<char, std::vector<std::string>> removeSolvedLettersFromMapping(
        std::unordered_map<char, std::vector<std::string> > &letterMapping);
    [[nodiscard]] std::string translateMessage(const std::string& key, const std::string& message, const int& mode) const;
    std::string decryptWithCipherletterMapping(const std::string &message, std::unordered_map<char, std::vector<std::string>> &letterMapping);
public:

    std::string hack(const std::string &message);
    [[nodiscard]] std::string encryptMessage(const std::string& key, const std::string& message) const;
    [[nodiscard]] std::string decryptMessage(const std::string& key, const std::string& message) const;
    [[nodiscard]] std::string generateRandomKey() const;
};
void printLetterMapping(const std::unordered_map<char, std::vector<std::string>> &letterMapping);

#endif //SIMPLESUBCIPHER_H
