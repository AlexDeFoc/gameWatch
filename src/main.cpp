#include <thread>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>

#include "item.h"

using namespace std::chrono_literals;

inline std::string filename = "WatchItems.txt";

int main() {
    std::vector<Item> itemList;

    std::string userInput = "";

    const std::vector<std::string> MainMenuOptions = {
        "List (l)",
        "Add (a)",
        "Remove (r)",
        "Start (s)",
        "Reset (0)",
    };


    while (true) {
        // Print main menu options
        for (const std::string& opt : MainMenuOptions) {
            std::cout << opt << "\n";
        }
        std::cout << "--> ";
        std::cin >> userInput;
        std::cout << "\n";

        // Check opts
        if (userInput == "l") {
            Item::LoadItemList(itemList, filename);
            Item::PrintItemList(itemList);
            std::cout << std::endl;
        }
        else if (userInput == "a") {
            std::cout << "--> ";
            std::cin.get();
            std::getline(std::cin, userInput);
            std::cout << "\n";

            Item NewItem;
            NewItem.Name = userInput;
            Item::AddItem(itemList, NewItem, filename);
            Item::UpdateFile(itemList, filename);
        }
        else if (userInput == "r") {
            Item::LoadItemList(itemList, filename);
            if (itemList.size() == 0) {
                std::cout << "No items to remove\n" << std::endl;
                continue;
            }

            std::cout << "--> ";
            std::cin >> userInput;
            std::cout << "\n";

            itemList.erase(itemList.begin() + (std::stoi(userInput) - 1));
            Item::ReorderItemList(itemList);
            Item::UpdateFile(itemList, filename);
        }
        else if (userInput == "s") {
            if (itemList.size() == 0) {
                std::cout << "No items to start\n" << std::endl;
                continue;
            }

            std::cout << "--> ";
            std::cin >> userInput;
            std::cout << "\n";

            int itemIndex = std::stoi(userInput) - 1;

            std::thread([&itemList, itemIndex]() {
                while (true) {
                    std::this_thread::sleep_for(std::chrono::minutes(1min));
                    itemList[itemIndex].Time += 1;
                    std::cout << "1 minute passed\n Current time on "
                        << itemList[itemIndex].Name << " is: "
                        << itemList[itemIndex].Time << std::endl;
                    Item::UpdateFile(itemList, filename);
                }
            }).detach();
        }
        else if (userInput == "0") {
            if (itemList.size() == 0) {
                std::cout << "No items to reset\n" << std::endl;
                continue;
            }

            std::cout << "--> ";
            std::cin >> userInput;
            std::cout << "\n";

            itemList[std::stoi(userInput) - 1].Time = 0;
            Item::UpdateFile(itemList, filename);
        }
    }

    return 0;
}
