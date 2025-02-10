#include <iostream>

#include "caesarCyph.h"
#include "transpositionCipher.h"
#include "affineCipher.h"
#include "simpleSubCipher.h"

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
    const std::string hacked = affine.hack(encrypted);
    std::cout << "Hacked message: " << hacked << std::endl;

    std::cout << std::endl << "Encrypting and decrypting a message using Simple Substitution Cipher" << std::endl;
    simpleSubCipher simpleSub;
    text = "If a man is offered a fact which goes against his "
            "instincts, he will scrutinize it closely, and unless the evidence "
            "is overwhelming, he will refuse to believe it. If, on the other "
            "hand, he is offered something which affords a reason for acting "
            "in accordance to his instincts, he will accept it even on the "
            "slightest evidence. The origin of myths is explained in this way. "
            " -Bertrand Russell";
    //text = "HELLO WORLD!";

    std::string keySimpleSub = "LFWOAYUISVKMNXPBDCRJTQEGHZ";
    encrypted = simpleSub.encryptMessage(keySimpleSub, text);
    decrypted = simpleSub.decryptMessage(keySimpleSub, encrypted);
    std::cout << "Original: " << text << "|" << std::endl;
    std::cout << "Encrypted: " << encrypted << "|" << std::endl;
    std::cout << "Decrypted: " << decrypted << "|" << std::endl;
    std::cout << "Hacking the encrypted message: " << std::endl;
    std::string hackedSimpleSub = simpleSub.hack(encrypted);
    std::cout << "Hacked message: " << hackedSimpleSub << std::endl;
    return 0;
}
