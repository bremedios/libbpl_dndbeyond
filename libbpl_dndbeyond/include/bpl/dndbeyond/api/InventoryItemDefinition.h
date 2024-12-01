//
// Created by Bradley Remedios on 11/21/24.
//
#ifndef BPL_DNDBEYOND_API_INVENTORYITEMDEFINITION_H
#define BPL_DNDBEYOND_API_INVENTORYITEMDEFINITION_H

#include <string>
#include <rapidjson/document.h>

namespace bpl::dndbeyond::api {
    class InventoryItemDefinition {
    public:
        InventoryItemDefinition() = default;
        ~InventoryItemDefinition() = default;

        [[nodiscard]] bool Load(const rapidjson::Value& value);

        [[nodiscard]] const std::string& getName() const { return m_name; }
        [[nodiscard]] int getArmorClass() const  {return m_armorClass; }
    private:
        std::string m_name;
        int     m_armorClass = 0;
    }; // InventoryItem
} // bpl::dndbeyond::api

#endif //BPL_DNDBEYOND_API_INVENTORYITEMDEFINITION_H