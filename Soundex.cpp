#include <iostream>
#include <string>
#include <unordered_map>

std::string get_soundex_code(char c) {
    c = toupper(c);
    std::unordered_map<char, std::string> mapping = {
        {'B', "1"}, {'F', "1"}, {'P', "1"}, {'V', "1"},
        {'C', "2"}, {'G', "2"}, {'J', "2"}, {'K', "2"}, {'Q', "2"}, {'S', "2"}, {'X', "2"}, {'Z', "2"},
        {'D', "3"}, {'T', "3"},
        {'L', "4"},
        {'M', "5"}, {'N', "5"},
        {'R', "6"},
    };
    auto it = mapping.find(c);
    if (it != mapping.end()) {
        return it->second;
    }
    return "0";  // Default to '0' for non-mapped characters
}

bool check_code_state(const std::string& code, const std::string& prev_code) {
    return code != "0" && code != prev_code;
}

std::pair<std::string, std::string> process_character(char c, std::string soundex, std::string prev_code) {
    std::string code = get_soundex_code(c);
    if (check_code_state(code, prev_code)) {
        soundex += code;
        prev_code = code;
    }
    return std::make_pair(soundex, prev_code);
}

std::string encode_name(const std::string& name, std::string soundex, std::string prev_code) {
    for (size_t i = 1; i < name.size(); ++i) {
        std::tie(soundex, prev_code) = process_character(name[i], soundex, prev_code);
        if (soundex.size() == 4) {
            break;
        }
    }
    // Pad with zeros if necessary
    soundex = soundex.append(4 - soundex.size(), '0');
    return soundex;
}

std::string generate_soundex(const std::string& name) {
    if (name.empty()) {
        return "";
    }
    // Start with the first letter (capitalized)
    std::string soundex(1, toupper(name[0]));
    std::string prev_code = get_soundex_code(soundex[0]);
    return encode_name(name, soundex, prev_code);
}

int main() {
    std::string name;
    std::cout << "Enter a name: ";
    std::cin >> name;
    std::string soundex_code = generate_soundex(name);
    std::cout << "Soundex code: " << soundex_code << std::endl;
    return 0;
}
