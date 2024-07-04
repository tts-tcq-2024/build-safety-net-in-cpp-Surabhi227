#include <gtest/gtest.h>
#include "Soundex.h"

// Test case for an empty string
TEST(SoundexTest, EncodeEmptyString) {
    EXPECT_EQ(generateSoundex(""), "");
}

// Test case for a single letter
TEST(SoundexTest, EncodeSingleLetter) {
    EXPECT_EQ(generateSoundex("A"), "A000");
    EXPECT_EQ(generateSoundex("B"), "B000");
}

// Test case for no matching Soundex codes after the first letter
TEST(SoundexTest, EncodeNoMatchingCodes) {
    EXPECT_EQ(generateSoundex("Aeiou"), "A000");
}

// Test case for typical animal names
TEST(SoundexTest, EncodeAnimalNames) {
    EXPECT_EQ(generateSoundex("Cat"), "C300");
    EXPECT_EQ(generateSoundex("Dog"), "D200");
    EXPECT_EQ(generateSoundex("Elephant"), "E415");
    EXPECT_EQ(generateSoundex("Giraffe"), "G610");
    EXPECT_EQ(generateSoundex("Kangaroo"), "K526");
    EXPECT_EQ(generateSoundex("Zebra"), "Z160");
}

// Test case for names with consecutive same Soundex codes
TEST(SoundexTest, EncodeConsecutiveCodes) {
    EXPECT_EQ(generateSoundex("Emu"), "E500");
    EXPECT_EQ(generateSoundex("Hippopotamus"), "H113");
}

// Test case for names with different lengths
TEST(SoundexTest, EncodeDifferentLengths) {
    EXPECT_EQ(generateSoundex("Ant"), "A530");
    EXPECT_EQ(generateSoundex("Bee"), "B000");
    EXPECT_EQ(generateSoundex("Fox"), "F200");
}

// Test case for ignoring non-alphabet characters
TEST(SoundexTest, EncodeWithNonAlphabetCharacters) {
    EXPECT_EQ(generateSoundex("O'Possum"), "O250");
    EXPECT_EQ(generateSoundex("McCaw"), "M200");
    EXPECT_EQ(generateSoundex("St. Bernard"), "S351");
}
