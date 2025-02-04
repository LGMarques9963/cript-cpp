#include <iostream>

#include "caesarCyph.h"

int main() {
    std::cout << "Encrypting and decrypting a message using Caesar cipher." << std::endl;
    caesarCyph cyph(13);
    std::string text = "This is my secret message.";
    std::string encrypted = cyph.encrypt(text);
    std::string decrypted = cyph.decrypt(encrypted);
    std::cout << "Original: " << text << std::endl;
    std::cout << "Encrypted: " << encrypted << std::endl;
    std::cout << "Decrypted: " << decrypted << std::endl;
    return 0;
}