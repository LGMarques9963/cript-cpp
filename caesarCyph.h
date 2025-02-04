//
// Created by lorran on 04/02/25.
//

#ifndef CAESARCYPH_H
#define CAESARCYPH_H
#include <string>
#include <sstream>


class caesarCyph {
    int key;
    const std::string SYMBOLS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz123456789 !?.";

public:
    caesarCyph(int key);
    std::string encrypt(const std::string& text);
    std::string decrypt(const std::string& text);

};



#endif //CAESARCYPH_H
