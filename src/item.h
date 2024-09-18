#include <string>
#include <vector>

#ifndef ITEM_H
#define ITEM_H

class Item {
public:
    int Index;
    std::string Name;
    int Time;

    std::string serializeItem();

    static Item de_serializeItem(const std::string& line);
    static int getFileItemCount(const std::string& filename);
    static void writeFile(std::vector<Item>& itemList, const std::string& filename);
    static void AddItem(std::vector<Item>& itemList, Item& item, const std::string& filename);
    static void LoadItemList(std::vector<Item>& itemList, const std::string& filename);
    static void PrintItemList(std::vector<Item>& itemList);
    static void ReorderItemList(std::vector<Item>& itemList);
    static void UpdateFile(std::vector<Item>& itemList, const std::string& filename);
};

#endif
