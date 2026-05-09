#include "inventorySystem.h"
#include <iostream>
#include <fstream>
#include <vector>

void story() {
    std::cout << "" << std::endl;
}
void rpgMenu() {
    std::vector<std::string> menu = {"Battle", "You", "Invetory", "Story", "exit"};
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::cout << "-------------" << std::endl;
    for(size_t i = 0; i < nums.size(); i++) {
        std::cout << " " << nums[i] << ". " << menu[i] << std::endl;
    }
    std::cout << "-------------" << std::endl;
}

int main() {
    std::string input;
    std::cout << "-+-+-+-+-+-+-+-+-\n    RPG GAME\n-+-+-+-+-+-+-+-+-\nWelcome to RPG game." << std::endl;
    while(true) {
        rpgMenu();
        std::cout << ">> ";
        std::cin >> input;
        if(isNumber(input)) {
            int iinput = stoi(input);
            if(iinput == 1) {

            }else
            if(iinput == 2) {

            }else
            if(iinput == 3) {
                runinventory();
            }else
            if(iinput == 4) {

            }else
            if(iinput == 5) {
                break;
            }else {
                std::cout << "Enter the valid number." << std::endl;
                continue;
            }
        }else {
            std::cout << "Enter the number." << std::endl;
            continue;
        }
    }
    return 0;
}
