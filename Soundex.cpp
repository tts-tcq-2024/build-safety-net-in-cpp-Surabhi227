#include "Soundex.h"
#include <string>
#include <cctype>
#include <unordered_map>
 
char getSoundexCode(char c) {
    static const char soundexCodes[] = {
        '0', '1', '2', '3', '0', '1', '2', '0', '0', '2', '2', '4', '5', '5', '0', '1', '2', '6', '2', '3', '0', '1', '0', '2', '0', '2'
    };
 
    c = toupper(c);
    if (c >= 'A' && c <= 'Z') {
        return soundexCodes[c - 'A'];
    }
    return '0';
}
 
char fetch_firstchar(const std::string& name) {
    if (name.empty()) return '\0';
    return toupper(name[0]);
}
 
void appendSoundex(std::string& soundex, char code, char& prevCode) {
    if (code != '0' && code != prevCode) {
        soundex += code;
        prevCode = code;
    }
}
 
std::string initializeSoundex(const std::string& name, char firstChar) {
    std::string soundex(1, firstChar);
    char secondex = getSoundexCode(name[1]);
    if (secondex != '0') {
        soundex += secondex;
    }
    return soundex;
}
 
std::string processSoundex(const std::string& name, char firstChar) {
   std::string soundex = initializeSoundex(name, firstChar);
    char prevCode = soundex[1];
    for (size_t i = 2; i < name.length() && soundex.length() < 4; ++i) 
    {
        char code = getSoundexCode(name[i]);
        appendSoundex(soundex, code, prevCode);
    }
 
    return soundex;
}
 
std::string paddingSoundex(const std::string& soundex) {
    std::string paddedSoundex = soundex;
    paddedSoundex.resize(4, '0');
    return paddedSoundex;
}
 
std::string generateSoundex(const std::string& name) {
    if (name.empty()) return "";
 
    char firstChar = fetch_firstchar(name);
    std::string processedName = processSoundex(name, firstChar);
    std::string paddedSoundex = paddingSoundex(processedName);
 
    return paddedSoundex;
}
