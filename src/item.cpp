#include "item.h"
#include <iostream>
#include <fstream>

// Private
std::string Item::serializeItem() {
    return std::to_string(Index) + ". " + Name + ", " + std::to_string(Time);
}

void Item::PrintItemList(std::vector<Item>& itemList) {
    if (itemList.size() == 0) {
        std::cout << "List is empty\n";
        return;
    }
    for (Item& item : itemList) {
        std::cout << item.Index << ". " << item.Name << ", " << item.Time << " minutes" << "\n";
    }
}

Item Item::de_serializeItem(const std::string& line) {
    Item item;
    size_t pos = 0;
    size_t endPos = line.find(". ");

    if (endPos != std::string::npos) {
        item.Index = std::stoi(line.substr(pos, endPos - pos));
        pos = endPos + 2;
    }

    endPos = line.find(", ", pos);
    if (endPos != std::string::npos) {
        item.Name = line.substr(pos, endPos - pos);
        pos = endPos + 2;
    }

    item.Time = std::stoi(line.substr(pos));
    return item;
}

int Item::getFileItemCount(const std::string& filename) {
    std::ifstream watchFile(filename);
    if (!watchFile.is_open()) {
        return 0;
    }

    int lineCount = 0;
    std::string dummyLine;
    while (std::getline(watchFile, dummyLine)) {
        ++lineCount;
    }

    watchFile.close();
    return lineCount;
}

void Item::writeFile(std::vector<Item>& itemList, const std::string& filename) {
    std::ofstream watchFile(filename);
    watchFile.clear();
    for (Item& item : itemList) {
        watchFile << item.serializeItem() << std::endl;
    }
    watchFile.close();
}

// Public

void Item::AddItem(std::vector<Item>& itemList, Item& item, const std::string& filename) {
    int itemCount = Item::getFileItemCount(filename);
    item.Index = itemCount + 1;
    item.Time = 0;
    itemList.push_back(item);
}

void Item::LoadItemList(std::vector<Item>& itemList, const std::string& filename) {
    std::ifstream watchFile(filename);
    if (!watchFile.is_open()) {
        watchFile.close();
        std::ofstream watchFile(filename);
    }

    int itemCount = Item::getFileItemCount(filename);
    std::string line;
    Item item;
    std::vector<Item> NewItemList;

    for (int i = 0; i < itemCount; i++) {
        std::getline(watchFile, line);
        item = Item::de_serializeItem(line);
        NewItemList.push_back(item);
    }

    itemList = NewItemList;
    watchFile.close();
}

void Item::ReorderItemList(std::vector<Item>& itemList) {
    for (int i = 0; i < itemList.size(); i++) {
        itemList[i].Index = i+1;
    }
}

void Item::UpdateFile(std::vector<Item>& itemList, const std::string& filename) {
    writeFile(itemList, filename);
}
