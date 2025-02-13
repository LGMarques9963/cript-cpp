//
// Created by lorran on 10/02/25.
//

#ifndef VIGENERECIPHER_H
#define VIGENERECIPHER_H
#include <string>


class vigenereCipher {
    const std::string SYMBOLS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    [[nodiscard]] std::string translateMessage(const std::string &key, const std::string &message, const int &mode) const;


    std::string hack(const std::string &message, const int &mode);

public:
    std::string dictionaryHack(const std::string & message);
    [[nodiscard]] std::string encrypt(const std::string &key, const std::string &message) const;
    [[nodiscard]] std::string decrypt(const std::string &key, const std::string &message) const;
};



#endif //VIGENERECIPHER_H
