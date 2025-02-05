//
// Created by lorran on 04/02/25.
//

#ifndef TRANSPOSITIONCIPHER_H
#define TRANSPOSITIONCIPHER_H
#include <string>


class transpositionCipher {

public:
    std::string encrypt(const int& key, const std::string& text);
    std::string decrypt(const int& key, const std::string& text);
};



#endif //TRANSPOSITIONCIPHER_H
