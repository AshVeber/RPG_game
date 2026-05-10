#include "inventorySystem.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

void GAME() {
    std::string input;
    std::cout << "-+-+-+-+-+-+-+-+-\n    RPG GAME\n-+-+-+-+-+-+-+-+-" << std::endl;
}
void rpgMenu() {
    std::vector<std::string> menu = {"Battle", "Monsters", "Inventory", "exit"};
    std::vector<int> nums = {1, 2, 3, 4};
    std::cout << "-------------" << std::endl;
    for(size_t i = 0; i < nums.size(); i++) {
        std::cout << " " << nums[i] << ". " << menu[i] << std::endl;
    }
    std::cout << "-------------" << std::endl;
}
std::vector<User> Monsters = {{"Godzilla", 20}, {"Shark", 5}, {"Thanos", 40}, {"Thor", 35}, {"Jinx", 10}, {"Dove", 3}};
void monsters() {
    std::sort(Monsters.begin(), Monsters.end(), [](const User& a, const User& b) {
        return a.hp > b.hp;
    });
    for(size_t i = 0; i < Monsters.size(); ++i) {
        std::cout << "Name: " << Monsters[i].name << " HP: " << Monsters[i].hp << std::endl;
    }
}

int randomMonster(std::vector<User>& Monsters) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, Monsters.size() - 1);
    return dist(gen);
}
void playBattle(std::vector<User>& Monsters) {
    int num = randomMonster(Monsters);
    std::cout << Monsters[num].name << std::endl;
}
void battle(std::vector<Item>& items, std::vector<User>& Monsters) {
    if(items.empty()) {
        std::cout << "You do not have items for battle. Check your inventory." << std::endl;
    }else{
        playBattle(Monsters);
    }
}

int main() {
    
    std::string input;
    std::vector<Item> items = loaditem();
    while(true) {
        GAME();
        rpgMenu();
        std::cout << ">> ";
        getline(std::cin, input);
        if(isNumber(input)) {
            int iinput = stoi(input);
            if(iinput == 1) {
                battle(items, Monsters);
            }else
            if(iinput == 2) {
                monsters();
            }else
            if(iinput == 3) {
                runinventory();
            }else
            if(iinput == 4) {
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
