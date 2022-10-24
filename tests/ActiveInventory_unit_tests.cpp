#include <gtest/gtest.h>

#include "../include/ActiveInventory.hpp"
#include "../include/PerishableItem.hpp"

namespace {

TEST(ActiveInventory, create) {
    /* Ensure default constructor works. */
    std::shared_ptr<ActiveInventory> active_inventory{new ActiveInventory};
    EXPECT_NE(active_inventory, nullptr);
}

TEST(ActiveInventory, AddItem) {
    std::shared_ptr<ActiveInventory> active_inventory{new ActiveInventory};
    EXPECT_NE(active_inventory, nullptr);

    /* Create a PerishableItem, ensure it is made, and make sure it is added right. */
    std::shared_ptr<PerishableItem> new_item{
        new PerishableItem("Apple", "Perishable", "None", "10", "0", "1.50", "0.50", "0.10", "10/22/2023")};
    EXPECT_NE(new_item, nullptr);

    active_inventory->addItem(new_item);
    /* Check that error checking catches adding an item twice. */
    EXPECT_EQ(active_inventory->addItem(new_item), -1);

    /* Create and try to add a new item with the same id as an old one. */
    std::shared_ptr<PerishableItem> newer_item{
        new PerishableItem("Orange", "Perishable", "None", "10", "0", "1.50", "0.50", "0.10", "10/22/2023")};

    EXPECT_EQ(active_inventory->addItem(newer_item), -1);

    EXPECT_EQ(active_inventory->searchByName("Apple"), new_item);
    EXPECT_EQ(active_inventory->searchById(0), new_item);
}

TEST(ActiveInventory, UpdateItem) {
    std::shared_ptr<ActiveInventory> active_inventory{new ActiveInventory};
    EXPECT_NE(active_inventory, nullptr);

    std::shared_ptr<PerishableItem> new_item{
        new PerishableItem("Apple", "Perishable", "None", "10", "0", "1.50", "0.50", "0.10", "10/22/2023")};
    EXPECT_NE(new_item, nullptr);

    active_inventory->addItem(new_item);

    std::shared_ptr<PerishableItem> newer_item{
        new PerishableItem("Tangerine", "Perishable", "None", "10", "1", "1.50", "0.50", "0.10", "10/22/2023")};
    EXPECT_NE(newer_item, nullptr);

    active_inventory->addItem(newer_item);

    /* Check updating valid fields and invalid updates. */
    EXPECT_EQ(active_inventory->updateItem("Apple", "Quantity", "15"), 0);
    EXPECT_EQ(active_inventory->updateItem("Apple", "Name", "Orange"), 0);
    EXPECT_EQ(active_inventory->updateItem("Apple", "Quantity", "15"), -1);
    EXPECT_EQ(active_inventory->updateItem("Orange", "Quantity", "-15"), -1);
    EXPECT_EQ(active_inventory->updateItem("Orange", "ID", "1"), -1);
}

TEST(ActiveInventory, RemoveItem) {
    std::shared_ptr<ActiveInventory> active_inventory{new ActiveInventory};
    EXPECT_NE(active_inventory, nullptr);

    /* Create, add, and remove an item. */
    std::shared_ptr<PerishableItem> new_item{
        new PerishableItem("Apple", "Perishable", "None", "10", "0", "1.50", "0.50", "0.10", "10/22/2023")};
    EXPECT_NE(new_item, nullptr);

    EXPECT_EQ(active_inventory->addItem(new_item), 1);
    EXPECT_EQ(active_inventory->removeItem("Apple"), 1);

    /* Try to remove the item again and then ensure the item was removed. */
    EXPECT_EQ(active_inventory->removeItem("Apple"), -1);
    EXPECT_EQ(active_inventory->searchByName("Apple"), nullptr);
    EXPECT_EQ(active_inventory->searchById(0), nullptr);
}
}  // namespace