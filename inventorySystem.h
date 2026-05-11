#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct Item {
    std::string name;
    int quantity;
    int power;
    int autonomy;
    bool consumable;
};
inline bool isNumber(const std::string& s) {
    if(s.empty()) {
        return 0;
    }
    for(char const &c : s) {
        if(!(isdigit(c))) {
            return 0;
        }
    }
    return 1;
}
inline void Menu() {
    std::cout << "--------------" << std::endl;
    std::vector<std::string> menu = {"Show item", "Item shop", "Remove item", "To the Battle"};
    std::vector<int> nums = {1, 2, 3, 4};

    for(size_t i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << ". " << menu[i] << std::endl;
    }
    std::cout << "--------------" << std::endl;
}
inline void showitem(const std::vector<Item>& items) {
    std::cout << "-*-*-*-*-*-*-*-" << std::endl;
    for(size_t i = 0; i < items.size(); ++i) {
        if(items[i].autonomy == 0) {
            std::cout << i+1 << ") Item:" << items[i].name << " Quantity:" << items[i].quantity << " Power:" << items[i].power << " Autonomy:" << items[i].autonomy << " |used| " << std::endl;
        }else {
            std::cout << i+1 << ") Item:" << items[i].name << " Quantity:" << items[i].quantity << " Power:" << items[i].power << " Autonomy:" << items[i].autonomy << " |    | " << std::endl;
        }
    }
    std::cout << "*-*-*-*-*-*-*-*" << std::endl;
}
inline std::vector<Item> shopitems = {{"Axe", 10, 3, 3}, {"Pickaxe", 5, 4, 4}, {"Hoe", 11, 1, 1}, {"Sword", 20, 5, 5}, {"Shovel", 31, 2, 2}};
inline void itemshop() {
    std::cout << "---------------\n   ITEM SHOP\n---------------" << std::endl;
    for(size_t i = 0; i < shopitems.size(); ++i) {
        std::cout << i+1 << ") Name: " << shopitems[i].name << " | Quantity: " << shopitems[i].quantity << " | Power: " << shopitems[i].power << " | Autonomy: " << shopitems[i].autonomy << std::endl;
    }
}
inline void saveitem(std::vector<Item>& items) {
    std::ofstream file("items.txt");
    for(const Item& item : items) {
        file << item.name << "|" << item.power << "|" << item.quantity << "|" << item.consumable << std::endl;
    }
}
inline std::vector<Item> loaditem() {
    std::vector<Item> items;
    std::ifstream file("items.txt");
    std::string line;

    while(getline(file, line)) {
        Item item;
        size_t p1 = line.find("|");
        size_t p2 = line.find("|", p1 + 1);
        size_t p3 = line.find("|", p2 + 1);
        if(p1 != std::string::npos && p2 != std::string::npos && p3 != std::string::npos) {
            item.name = line.substr(0, p1);
            item.quantity = stoi(line.substr(p1 + 1, p2 - p1 - 1));
            item.power = stoi(line.substr(p2 + 1, p3 - p2 - 1));
            item.consumable = line.substr(p3 + 2) == "1";
        }
        items.push_back(item);
    }
    return items;
}
inline void additem(std::vector<Item>& items, std::vector<Item>& shopitems) {
    std::string input;
    while(true) {
        itemshop();
        std::cout << "What item do you want to add? (Press 'x' to exit)" << std::endl;
        std::cout << ">> ";
        std::getline(std::cin, input);
        if(input.empty()) {
            std::cout << "Enter the number please." << std::endl;
            continue;
        }else {
            if(isNumber(input)) {
                int iinput = stoi(input);
                int i = iinput - 1;
                if(iinput >= 1 && iinput <= (int)shopitems.size()) {
                    if(shopitems[i].quantity <= 0) {
                        std::cout << "This item is out of stock." << std::endl;
                        continue;
                    }else {
                        shopitems[i].quantity -= 1;
                        bool found = false;
                        for(Item& item : items) {
                            if(item.name == shopitems[i].name) {
                                item.quantity += 1;
                                found = true;
                                break;
                            }
                        }
                        if(!found) {
                            Item newitem = shopitems[i];
                            newitem.quantity = 1;
                            items.push_back(newitem);  
                        }
                        saveitem(items);
                        std::cout << "Item added." << std::endl;
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
inline void saveshop(std::vector<Item>& shopitems) {
    std::ofstream file("shop_items.txt");
    for(const Item& shop_item : shopitems) {
        file << shop_item.name << "|" << shop_item.quantity << "|" << shop_item.power << "|" << std::endl;
    }
}
inline std::vector<Item> loadshop() {
    std::vector<Item> shopitems;
    std::ifstream file("shop_items.txt");
    std::string line;

    while(getline(file, line)) {
        Item shopitem;
        size_t p1 = line.find("|");
        size_t p2 = line.find("|", p1 + 1);
        size_t p3 = line.find("|", p2 + 1);
        if(p1 != std::string::npos && p2 != std::string::npos && p3 != std::string::npos) {
            shopitem.name = line.substr(0, p1);
            shopitem.quantity = stoi(line.substr(p1 + 1, p2 - p1 - 1));
            shopitem.power = stoi(line.substr(p2 + 1, p3 - p2 - 1));
            shopitem.consumable = line.substr(p3 + 2) == "1";
        }
        shopitems.push_back(shopitem);
    }
    return shopitems;
}
inline void removeitem(std::vector<Item>& items) {
    if(items.empty()) {
        std::cout << "You do not have items to remove" << std::endl;
    }else {
        std::string input;
        while(true) {
            showitem(items);
            std::cout << "What item do you want to remove? (Press 'x' to exit)\n>> ";
            std::getline(std::cin, input);
            if(input.empty()) {
                std::cout << "Enter the number please." << std::endl;
                continue;
            }else {
                if(isNumber(input)) {
                    int iinput = stoi(input);
                    int index = iinput - 1;
                    if(iinput >= 1 && iinput <= (int)items.size()) {
                        items[index].quantity -= 1;
                        if(items[index].quantity <= 0) {
                            items.erase(items.begin() + index);
                            saveitem(items);
                        }else {
                            saveitem(items); 
                        }
                        std::cout << "Item removed" << std::endl;
                        break;
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
inline void runinventory() {
    std::cout << "===============\n   INVENTORY\n===============" << std::endl;
    std::vector<Item> items = loaditem();
    std::string input;
    while(true) {
        Menu();
        std::cout << ">> ";
        std::getline(std::cin, input);
        if(input.empty()) {
            std::cout << "Enter the number please." << std::endl;
            continue;
        }else {
            if(isNumber(input)) {
                int iinput = stoi(input);
                if(iinput == 1) {
                    if(!(items.empty())) {
                        showitem(items);
                    }else{
                        std::cout << "You do not have items." << std::endl;
                    }
                }else
                if(iinput == 2) {
                    additem(items, shopitems);
                }else
                if(iinput == 3) {
                    removeitem(items);
                }else
                if(iinput == 4) {
                    break;
                }else {
                    std::cout << "Enter the valid number." << std::endl;
                    continue;
                }
            }else {
                std::cout << "That's not a number." << std::endl;
                continue;
            }
        }
    }
}

struct User {
    std::string name;
    int hp;
};
