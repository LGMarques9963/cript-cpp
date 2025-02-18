//
// Created by lorran on 04/02/25.
//

#ifndef CAESARCYPH_H
#define CAESARCYPH_H
#include <string>
#include <sstream>


class caesarCyph {
    // The numeric key used for shifting the characters
    int key;

    // We allow letters, digits, space, punctuation - everything in one string
    const std::string SYMBOLS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz123456789 !?.";

public:
    explicit caesarCyph(int key);

    // Encrypts text by shifting symbols forward by 'key' positions
    [[nodiscard]] std::string encrypt(const std::string& text) const;

    // Decrypts text by shifting symbols backward by 'key' positions
    [[nodiscard]] std::string decrypt(const std::string& text) const;

    // Optionally, you can decrypt with an arbitrary key
    [[nodiscard]] std::string decrypt(const std::string &text, const int &key) const;

    // Brute-force approach: tries every possible key; prints out the decrypted message
    void hack(const std::string &text) const;
};



#endif //CAESARCYPH_H
