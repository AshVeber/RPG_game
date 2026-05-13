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
    std::vector<std::string> menu = {"BATTLE", "MONSTERS", "INVENTORY", "EXIT"};
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
void playBattle(std::vector<User>& Monsters, std::vector<Item>& items) {
    int num = randomMonster(Monsters);
    std::string input;
    if(Monsters[num].hp == 0) {
        randomMonster(Monsters);
    }
    if(items.empty()) {
        std::cout << "You do not have items for battle. Check your inventory." << std::endl;
    }else {
        while(true) {
            if(items.empty() && Monsters[num].hp > 0) {
                std::cout << "You lose." << std::endl;
                break;
            }
            std::cout << "Your enemy is: " << Monsters[num].name << " | HP: " << Monsters[num].hp << std::endl;
            showitem(items);
            std::cout << "Choose the item to beat the enemy (Press x to exit).\n>> ";
            std::getline(std::cin, input);
            if(input.empty()){
                std::cout << "Enter the number please." << std::endl;
                continue;
            }else {
                if(isNumber(input)) {
                    int index = stoi(input) - 1;
                    if(index >= 0 && index < (int)items.size()) {
                        items[index].autonomy -= 1;       
                        Monsters[num].hp -= items[index].power;                        
                        if(Monsters[num].hp < 0) {Monsters[num].hp = 0;}
                        if(items[index].autonomy == 0) {
                            if(items[index].quantity == 1) {
                                items.erase(items.begin() + index);
                            }else {
                               items[index].quantity -= 1;
                               items[index].autonomy = items[index].maxAutonomy;
                            }
                        } 
                        saveitem(items);
                        std::cout << "Ha!" << std::endl;
                        if(Monsters[num].hp > 0) {
                            continue;
                        }else{
                            Monsters.erase(Monsters.begin() + num);
                            std::cout << "You won!" << std::endl;
                            break;
                        }                
                    }else {
                        std::cout << "Enter the valid number." << std::endl;
                        continue;
                    }
                }else
                if(input == "x" || input == "X") {
                    break;
                }else {
                    std::cout << "That's not a number." << std::endl;
                    continue;
                }
            }
        }
    }
}
void playRPG() {
    GAME();
    std::vector<Item> items = loaditem();
    std::string input;
    while(true) {
        rpgMenu();
        std::cout << ">> ";
        getline(std::cin, input);
        if(isNumber(input)) {
            int iinput = stoi(input);
            if(iinput == 1) {
                if(Monsters.empty()) {
                    std::cout << "You beat all monsters." << std::endl;
                }else {
                    std::vector<Item> items = loaditem();
                    playBattle( Monsters, items);
                }   
            }else
            if(iinput == 2) {
                if(Monsters.empty()) {
                    std::cout << "Empty." << std::endl;
                }else {
                    monsters();
                }
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
}

int main() {
    playRPG();
    
    return 0;
}
