//
// Created by lorran on 06/02/25.
//

#ifndef SIMPLESUBCIPHER_H
#define SIMPLESUBCIPHER_H
#include <string>

class simpleSubCipher {
    const std::string SYMBOLS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    bool keyIsValid(const std::string& key) const;
    std::string translateMessage(const std::string& key, const std::string& message, const int& mode) const;
public:
    std::string encryptMessage(const std::string& key, const std::string& message);
    std::string decryptMessage(const std::string& key, const std::string& message);
    std::string generateRandomKey() const;
};

#endif //SIMPLESUBCIPHER_H
