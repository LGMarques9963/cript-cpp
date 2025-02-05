//
// Created by lorran on 05/02/25.
//
#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>
#include <random>
#include "../src/caesarCyph.h"

// Function to generate a random message
std::string generateRandomMessage() {
    const std::string baseMessage = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int repeatCount = rand() % 37 + 4; // Random repetition between 4 and 40
    std::string message;

    for (int i = 0; i < repeatCount; i++) {
        message += baseMessage;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(message.begin(), message.end(), g);

    return message;
}

TEST(CaesarCipherTest, EncryptionDecryption) {
    const std::string original = "HELLOWORLD";
    constexpr int key = 3;
    caesarCyph cipher(key);

    const std::string encrypted = cipher.encrypt(original);
    const std::string decrypted = cipher.decrypt(encrypted);

    EXPECT_EQ(original, decrypted);
}

TEST(CaesarCipherTest, EmptyString) {
    const std::string original;
    constexpr int key = 5;
    caesarCyph cipher(key);

    const std::string encrypted = cipher.encrypt(original);
    const std::string decrypted = cipher.decrypt(encrypted);

    EXPECT_EQ(original, decrypted);
}

TEST(CaesarCipherTest, LongMessage) {
    const std::string original = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
    constexpr int key = 7;
    caesarCyph cipher(key);
    const std::string encrypted = cipher.encrypt(original);
    const std::string decrypted = cipher.decrypt(encrypted);

    EXPECT_EQ(original, decrypted);
}

TEST(CaesarCipherTest, RandomMessages) {
    caesarCyph cipher(13);
    for (int i = 0; i < 100; i++) {
        std::string message = generateRandomMessage();
        std::string encrypted = cipher.encrypt(message);
        std::string decrypted = cipher.decrypt(encrypted);
        EXPECT_EQ(message, decrypted);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}