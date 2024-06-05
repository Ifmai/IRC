#include <iostream>
#include <sstream>
#include <string>

int main() {
    // Input string
    std::string input = "PASS :ANANIYEDIM";
    std::cout << input << " " << std::endl;
/* 
    // Create a string stream from the input string
    std::istringstream iss(input);

    // Variables to hold the tokens
    std::string token;
    std::string pass;

    // Tokenize the input string
    while (iss >> token) {
        if (token == "PASS") {
            // Read the next token which is the password
            iss >> pass;
            break; // Exit the loop after finding the password
        }
    }

    // Output the result
    if (!pass.empty()) {
        std::cout << "Password found: " << pass << std::endl;
		if(iss >> pass){
            if(pass.empty())
                std::cout << "boş amk found: " << std::endl;
            else
                std::cout << "girmedi amk found: " << std::endl;
        }
    } else {
        std::cout << "Password not found." << std::endl;
    }

    return 0;
 */}
