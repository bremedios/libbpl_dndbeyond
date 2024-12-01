//
// Created by Bradley Remedios on 11/21/24.
//

#include <bpl/dndbeyond/api/Inventory.h>

#include "../Debug.h"

namespace bpl::dndbeyond::api {
    bool Inventory::Load(const rapidjson::Value& value) {
        if (!value.IsArray()) {
            ERROR_MSG("Invalid root object");

            return false;
        }

        for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
            InventoryItem item;

            if (!item.Load(value[i])) {
                ERROR_MSG("Failed to load InventoryItem(" << i << ")");

                return false;
            }

            m_items.emplace_back(item);
        }

        return true;
    } // Load
} // bpl::dndbeyond::api