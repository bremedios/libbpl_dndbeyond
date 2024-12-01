//
// Created by Bradley Remedios on 11/21/24.
//
#ifndef BPL_DNDBEYOND_API_INVENTORYITEM_H
#define BPL_DNDBEYOND_API_INVENTORYITEM_H

#include <rapidjson/document.h>

#include <bpl/dndbeyond/api/InventoryItemDefinition.h>

namespace bpl::dndbeyond::api {
    class InventoryItem {
    public:
        InventoryItem() = default;
        ~InventoryItem() = default;

        [[nodiscard]] bool Load(const rapidjson::Value& value);

        [[nodiscard]] bool isEquipped() const { return m_equipped; }
        [[nodiscard]] int getQuantity() const  {return m_quantity; }
        [[nodiscard]] int getArmorClass() const {return m_definition.getArmorClass();}
        [[nodiscard]] const std::string& getName() const {return m_definition.getName();}

    private:
        bool    m_equipped=false;
        int     m_quantity = 0;

        InventoryItemDefinition m_definition;
    }; // InventoryItem
} // bpl::dndbeyond::api

#endif //BPL_DNDBEYOND_API_INVENTORYITEM_H