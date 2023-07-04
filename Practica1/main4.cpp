#include <iostream>
#include <regex>
#include <string>

int main() {
    std::string input;
    //std::regex pattern("^&\\s*CREATE\\s+TABLE\\s+(\\w+)\\s*\\((\\s*(?:\\w+\\s+\\w+\\s*(?:,|$))+)\\)\\s*#$");
    std::smatch matches;
    std::regex pattern("& CREATE TABLE (.*)  (.*) #");
    
    std::cout << "Introduce una cadena: ";
    std::getline(std::cin, input);

    if (std::regex_match(input, matches, pattern)) {
        std::cout << "La cadena coincide con la expresión regular." << std::endl;
        for (size_t i = 1; i < matches.size(); ++i) {
            std::cout << "Token " << i << ": " << matches[i] << std::endl;
        }
    } else {
        std::cout << "La cadena no coincide con la expresión regular." << std::endl;
    }

    return 0;
}