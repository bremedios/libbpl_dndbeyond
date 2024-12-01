//
// Created by Bradley Remedios on 11/21/24.
//
#ifndef BPL_DNDBEYOND_API_INVENTORY_H
#define BPL_DNDBEYOND_API_INVENTORY_H

#include <list>

#include <rapidjson/document.h>

#include <bpl/dndbeyond/api/InventoryItem.h>

namespace bpl::dndbeyond::api {

    class Inventory {
    public:
        Inventory() = default;
        ~Inventory() = default;

        [[nodiscard]] bool Load(const rapidjson::Value& value);
        [[nodiscard]] const std::list<InventoryItem>& getItems() const { return m_items;}
    private:
        std::list<InventoryItem> m_items;
    };

} // bpl::dndbeyond::api

#endif //BPL_DNDBEYOND_API_INVENTORY_H