//
// Created by lorran on 05/02/25.
//

#ifndef AFFINECIPHER_H
#define AFFINECIPHER_H
#include <string>


class affineCipher {
    [[nodiscard]] std::tuple<int, int> getKeyParts(int key) const;
    void checkKeys(int keyA, int keyB, int mode) const;

public:
    const std::string SYMBOLS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890 !?.";
    [[nodiscard]] int getRandomKey() const;

    std::string hack(const std::string &message) const;

    [[nodiscard]] std::string encryptMessage(int key, const std::string &message) const;
    [[nodiscard]] std::string decryptMessage(int key, const std::string &message) const;

};



#endif //AFFINECIPHER_H
