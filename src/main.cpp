#include <iostream>

#include "caesarCyph.h"
#include "transpositionCipher.h"
#include "affineCipher.h"

int main() {
    std::cout << "Encrypting and decrypting a message using Caesar cipher." << std::endl;
    caesarCyph cyph(13);
    std::string text = "This is my secret message.";
    std::string encrypted = cyph.encrypt(text);
    std::string decrypted = cyph.decrypt(encrypted);
    std::cout << "Original: " << text << "|" << std::endl;
    std::cout << "Encrypted: " << encrypted << "|" << std::endl;
    std::cout << "Decrypted: " << decrypted << "|" << std::endl;
    std::cout << "Hacking the encrypted message: " << std::endl;
    cyph.hack(encrypted);


    std::cout << std::endl << "Encrypting and decrypting a message using Transposition cipher." << std::endl;
    text = "Common sense is not so common.";
    encrypted = transpositionCipher::encrypt(8, text);
    decrypted = transpositionCipher::decrypt(8, encrypted);
    std::cout << "Original: " << text << "|" << std::endl;
    std::cout << "Encrypted: " << encrypted << "|" << std::endl;
    std::cout << "Decrypted: " << decrypted << "|" << std::endl;
    std::cout << "Hacking the encrypted message: " << std::endl;
    transpositionCipher::hack(encrypted);

    std::cout << std::endl << "Encrypting and decrypting a message using Affine cipher." << std::endl;
    text = "A computer would deserve to be called intelligent "
            "if it could deceive a human into believing that it was human. "
            "-Alan Turing";
    const affineCipher affine;
    constexpr int key = 2894;
    encrypted = affine.encryptMessage(key, text);
    decrypted = affine.decryptMessage(key, encrypted);
    std::cout << "Original: " << text << "|" << std::endl;
    std::cout << "Encrypted: " << encrypted << "|" << std::endl;
    std::cout << "Decrypted: " << decrypted << "|" << std::endl;
    std::cout << "Hacking the encrypted message: " << std::endl;
    std::string hacked = affine.hack(encrypted);
    std::cout << "Hacked message: " << hacked << std::endl;
    return 0;
}