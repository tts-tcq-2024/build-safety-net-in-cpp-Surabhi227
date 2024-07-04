#include "Soundex.h"
#include <string>
#include <cctype>
#include <unordered_map>

char encodeChar(char c) {
    static const char codes[] = {
        '0', '1', '2', '3', '0', '1', '2', '0', '0', '2', '2', '4', '5', '5', '0', '1', '2', '6', '2', '3', '0', '1', '0', '2', '0', '2'
    };

    c = std::toupper(static_cast<unsigned char>(c));
    if (c >= 'A' && c <= 'Z') {
        return codes[c - 'A'];
    }
    return '0';
}

char getFirstChar(const std::string& name) {
    if (name.empty()) return '\0';
    return std::toupper(static_cast<unsigned char>(name[0]));
}

void addCode(std::string& soundex, char code, char& prevCode) {
    if (code != '0' && code != prevCode) {
        soundex += code;
        prevCode = code;
    }
}

std::string initSoundex(const std::string& name, char firstChar) {
    std::string soundex(1, firstChar);
    char firstCode = encodeChar(name[1]);
    if (firstCode != '0') {
        soundex += firstCode;
    }
    return soundex;
}

std::string generateSoundex(const std::string& name, char firstChar) {
    std::string soundex = initSoundex(name, firstChar);
    char prevCode = soundex[1];
    for (size_t i = 2; i < name.length() && soundex.length() < 4; ++i) {
        char code = encodeChar(name[i]);
        addCode(soundex, code, prevCode);
    }

    return soundex;
}

std::string padSoundex(const std::string& soundex) {
    std::string paddedSoundex = soundex;
    paddedSoundex.resize(4, '0');
    return paddedSoundex;
}
