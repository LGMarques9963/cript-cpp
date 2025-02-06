//
// Created by lorran on 05/02/25.
//
#include <gtest/gtest.h>
#include "../src/utils.h"
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <cstdio>

// --- Test the gcd function ---
TEST(UtilsTest, GcdFunction) {
    EXPECT_EQ(gcd(45, 66), 3);
    EXPECT_EQ(gcd(10, 5), 5);
    EXPECT_EQ(gcd(17, 5), 1);
    EXPECT_EQ(gcd(0, 5), 5);
    EXPECT_EQ(gcd(5, 0), 5);
}

// --- Test the findModInverse function ---
TEST(UtilsTest, FindModInverseFunction) {
    // For a = 3, m = 26, the modular inverse is 9 because 3*9 % 26 == 27 % 26 == 1.
    EXPECT_EQ(findModInverse(3, 26), 9);
    // For a = 2 and m = 4, since gcd(2,4) != 1, no mod inverse exists; our function should return -1.
    EXPECT_EQ(findModInverse(2, 4), -1);
}

// --- Test removeNonAlpha ---
TEST(UtilsTest, RemoveNonAlpha) {
    std::string input = "Hello, World! 123";
    // Expect that punctuation and digits are removed, but letters and spaces are kept.
    std::string expected = "Hello World ";
    EXPECT_EQ(removeNonAlpha(input), expected);
}

// --- Test splitWords ---
TEST(UtilsTest, SplitWords) {
    std::string input = "Hello   world this is a test";
    std::vector<std::string> expected = {"Hello", "world", "this", "is", "a", "test"};
    std::vector<std::string> result = splitWords(input);
    EXPECT_EQ(result, expected);
}

// --- Test getEnglishCount using a small custom dictionary ---
TEST(UtilsTest, GetEnglishCount) {
    // Create a small dictionary with a few words.
    std::unordered_set<std::string> testDict = {"HELLO", "WORLD", "THIS", "IS", "A", "TEST"};
    std::string message = "Hello, world! This is a test.";
    // After converting to uppercase, removing non-alpha, and splitting, we expect 6 words (all in testDict).
    EXPECT_DOUBLE_EQ(getEnglishCount(message, testDict), 1.0);
}

// --- Test isEnglish ---
TEST(UtilsTest, IsEnglish) {
    // A clear English sentence should return true.
    std::string englishMessage = "This is a simple test message.";
    EXPECT_TRUE(isEnglish(englishMessage));

    // Gibberish should return false.
    std::string gibberishMessage = "asdkfjaskldf jalskdfj alskdjflkasdjf";
    EXPECT_FALSE(isEnglish(gibberishMessage));
}

// --- Test loadDictionary ---
TEST(UtilsTest, LoadDictionary) {
    // Create a temporary dictionary file.
    std::string tempFilename = "temp_dictionary.txt";
    {
        std::ofstream outfile(tempFilename);
        outfile << "HELLO\nWORLD\nTEST\n";
    }

    std::unordered_set<std::string> dict = loadDictionary(tempFilename);
    EXPECT_EQ(dict.size(), 3);
    EXPECT_NE(dict.find("HELLO"), dict.end());
    EXPECT_NE(dict.find("WORLD"), dict.end());
    EXPECT_NE(dict.find("TEST"), dict.end());

    // Remove the temporary file.
    std::remove(tempFilename.c_str());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}