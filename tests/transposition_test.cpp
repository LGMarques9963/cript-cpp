//
// Created by lorran on 05/02/25.
//
#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>
#include <random>
#include "../src/transpositionCipher.h"  // Include your cipher implementation

// Function to generate a random message
std::string generateRandomMessage() {
    std::string baseMessage = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int repeatCount = rand() % 37 + 4; // Random repetition between 4 and 40
    std::string message = "";

    for (int i = 0; i < repeatCount; i++) {
        message += baseMessage;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(message.begin(), message.end(), g);

    return message;
}

TEST(TranspositionCipherTest, EncryptionDecryption) {
    std::string original = "HELLOWORLD";
    int key = 3;
    transpositionCipher cipher;

    std::string encrypted = cipher.encrypt(key, original);
    std::string decrypted = cipher.decrypt(key, encrypted);

    EXPECT_EQ(original, decrypted);
}

TEST(TranspositionCipherTest, EmptyString) {
    std::string original = "";
    int key = 5;
    transpositionCipher cipher;

    std::string encrypted = cipher.encrypt(key, original);
    std::string decrypted = cipher.decrypt(key, encrypted);

    EXPECT_EQ(original, decrypted);
}

TEST(TranspositionCipherTest, LongMessage) {
    transpositionCipher cipher;
    std::string original = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int key = 7;

    std::string encrypted = cipher.encrypt(key, original);
    std::string decrypted = cipher.decrypt(key, encrypted);

    EXPECT_EQ(original, decrypted);
}

TEST(TranspositionCipherTest, RandomMessages) {
    srand(42); // Set a fixed seed for reproducibility
    transpositionCipher cipher;

    for (int i = 0; i < 20; ++i) { // Run 20 tests
        std::string message = generateRandomMessage();

        std::cout << "Test #" << (i + 1) << ": \"" << message.substr(0, 50) << "...\"" << std::endl;

        for (size_t key = 1; key < message.length() / 2; ++key) {
            std::string encrypted = cipher.encrypt(key, message);
            std::string decrypted = cipher.decrypt(key, encrypted);

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