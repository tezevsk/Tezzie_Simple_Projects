#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

#ifdef _WIN32
const char* CLEAR_CMD = "cls";
#elif __linux__
const char* CLEAR_CMD = "clear";
#elif __APPLE__
const char* CLEAR_CMD = "clear";
#endif

std::string path;

/*
std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}*/

/*
*
*@brief Welcome user!
*
*Handles welcome screen
*/
void W_Screen() {
    std::cout << "Hello and wellcome to ConTEDIT\nPlease path file down here\n:";
    std::cin >> path;
}

void clr() {
    system(CLEAR_CMD);
}

void OpenFile() {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::string answ;
        std::cout << "Failed to open file: " << path << "\nWould you like to create it?\n(Y) yes || (N) no\n:";
        std::cin >> answ;
        clr();
        if (answ == "Y" || answ == "y") {
            file.open(path, std::fstream::out);
        } else {
            std::cout << "Write path again\n:";
            std::cin >> path;
            OpenFile();
        }
        clr();
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::cout << "---" << path << "---\n";
    std::cout << buffer.str();
}

bool WriteLn() {
    char* data;
    std::cout << "\n:";
    fgets(data, 300, stdin);
    if (data != "^E") {
        std::ofstream file(path, std::ios::app);
        if (file.is_open()) 
        {
            file << data << std::endl;
            clr();
            std::ifstream file(path);
            std::stringstream buffer;
            buffer << file.rdbuf();
            std::cout << "---" << path << "---\n";
            std::cout << buffer.str();
        }
    } else return false;
    //---
    return true;
}

int main() {
    W_Screen();
    clr();
    OpenFile();
    while (WriteLn());
    return 0;
}
