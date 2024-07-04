#include <string>
#include <cctype>

class Soundex {
public:
    std::string encode(const std::string& name) const {
        if (name.empty()) return "";

        char firstChar = getFirstChar(name);
        std::string encoded = initializeSoundex(name, firstChar);

        encoded = processSoundex(name, firstChar);
        encoded = padSoundex(encoded);

        return encoded;
    }

private:
    char getSoundexCode(char c) const {
        static const char soundexCodes[] = {
            '0', '1', '2', '3', '0', '1', '2', '0', '0', '2', '2', '4', '5', '5', '0', '1', '2', '6', '2', '3', '0', '1', '0', '2', '0', '2'
        };

        c = std::toupper(static_cast<unsigned char>(c));
        if (c >= 'A' && c <= 'Z') {
            return soundexCodes[c - 'A'];
        }
        return '0';
    }

    char getFirstChar(const std::string& name) const {
        return std::toupper(static_cast<unsigned char>(name[0]));
    }

    void appendSoundexCode(std::string& soundex, char code, char& prevCode) const {
        if (code != '0' && code != prevCode) {
            soundex += code;
            prevCode = code;
        }
    }

    std::string initializeSoundex(const std::string& name, char firstChar) const {
        std::string soundex(1, firstChar);
        char secondCode = getSoundexCode(name[1]);
        if (secondCode != '0') {
            soundex += secondCode;
        }
        return soundex;
    }

    std::string processSoundex(const std::string& name, char firstChar) const {
        std::string soundex = initializeSoundex(name, firstChar);
        char prevCode = soundex.length() > 1 ? soundex[1] : '0';

        for (size_t i = 2; i < name.length() && soundex.length() < 4; ++i) {
            char code = getSoundexCode(name[i]);
            appendSoundexCode(soundex, code, prevCode);
        }

        return soundex;
    }

    std::string padSoundex(const std::string& soundex) const {
        std::string paddedSoundex = soundex;
        paddedSoundex.resize(4, '0');
        return paddedSoundex;
    }
};
