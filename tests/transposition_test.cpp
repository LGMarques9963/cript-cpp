//
// Created by lorran on 05/02/25.
//
#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>
#include <random>
#include "../src/transpositionCipher.h"
#include "../src/utils.h"

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

TEST(TranspositionCipherTest, EncryptionDecryption) {
    const std::string original = "HELLOWORLD";
    constexpr int key = 3;

    const std::string encrypted = transpositionCipher::encrypt(key, original);
    const std::string decrypted = transpositionCipher::decrypt(key, encrypted);

    EXPECT_EQ(original, decrypted);
}

TEST(TranspositionCipherTest, EmptyString) {
    const std::string original;
    constexpr int key = 5;

    const std::string encrypted = transpositionCipher::encrypt(key, original);
    const std::string decrypted = transpositionCipher::decrypt(key, encrypted);

    EXPECT_EQ(original, decrypted);
}

TEST(TranspositionCipherTest, LongMessage) {
    const std::string original = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
    constexpr int key = 7;

    const std::string encrypted = transpositionCipher::encrypt(key, original);
    const std::string decrypted = transpositionCipher::decrypt(key, encrypted);

    EXPECT_EQ(original, decrypted);
}

TEST(TranspositionCipherTest, RandomMessages) {

    for (int i = 0; i < 20; ++i) { // Run 20 tests
        std::string message = generateRandomMessage();

        for (int key = 1; key < message.length() / 2; ++key) {
            std::string encrypted = transpositionCipher::encrypt(key, message);
            std::string decrypted = transpositionCipher::decrypt(key, encrypted);

            // Assert that the decrypted message matches the original
            ASSERT_EQ(message, decrypted) << "Mismatch with key " << key << " and message " << message;
        }
    }
}

// Main function to run tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}