//
// Created by lorran on 04/02/25.
//

#ifndef TRANSPOSITIONCIPHER_H
#define TRANSPOSITIONCIPHER_H
#include <string>
#include "utils.h"


class transpositionCipher {

public:
    static std::string encrypt(const int& key, const std::string& text);
    static std::string decrypt(const int& key, const std::string& text);
    static std::string hack(const std::string &text);
};



#endif //TRANSPOSITIONCIPHER_H
