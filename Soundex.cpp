#include "Soundex.h"
#include <string>
#include <cctype>
#include <unordered_map>

char mapCharToSoundexCode(char c) {
    static const char soundexCodes[] = {
        '0', '1', '2', '3', '0', '1', '2', '0', '0', '2', '2', '4', '5', '5', '0', '1', '2', '6', '2', '3', '0', '1', '0', '2', '0', '2'
    };

    c = toupper(c);
    if (c >= 'A' && c <= 'Z') {
        return soundexCodes[c - 'A'];
    }
    return '0';
}

char getFirstChar(const std::string& name) {
    if (name.empty()) return '\0';
    return toupper(name[0]);
}

void addCodeIfNotDuplicate(std::string& soundex, char code, char& prevCode) {
    if (code != '0' && code != prevCode) {
        soundex += code;
        prevCode = code;
    }
}

std::string initializeSoundexCode(const std::string& name, char firstChar) {
    std::string soundex(1, firstChar);
    char initialCode = mapCharToSoundexCode(name[1]);
    if (initialCode != '0') {
        soundex += initialCode;
    }
    return soundex;
}

std::string processRemainingChars(const std::string& name, char firstChar) {
    std::string soundex = initializeSoundexCode(name, firstChar);
    char prevCode = soundex[1];
    for (size_t i = 2; i < name.length() && soundex.length() < 4; ++i) {
        char code = mapCharToSoundexCode(name[i]);
        addCodeIfNotDuplicate(soundex, code, prevCode);
    }

    return soundex;
}

std::string padSoundexCode(const std::string& soundex) {
    std::string paddedSoundex = soundex;
    paddedSoundex.resize(4, '0');
    return paddedSoundex;
}

std::string generateSoundex(const std::string& name) {
    if (name.empty()) return "";

    char firstChar = getFirstChar(name);
    std::string processedName = processRemainingChars(name, firstChar);
    std::string paddedSoundex = padSoundexCode(processedName);

    return paddedSoundex;
}
