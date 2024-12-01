//
// Created by Bradley Remedios on 11/21/24.
//
#include <bpl/storage/Json.h>
#include <bpl/dndbeyond/api/InventoryItemDefinition.h>

#include "../Debug.h"

namespace bpl::dndbeyond::api {
    bool InventoryItemDefinition::Load(const rapidjson::Value& value) {
        if (!value.IsObject()) {
            ERROR_MSG("Invalid root object");
            return false;
        }

        if (!bpl::storage::Json::Load(value, "name", m_name)) {
            ERROR_MSG("Failed to load name");

            return false;
        }

        if (!bpl::storage::Json::Load(value, "armorClass", m_armorClass)) {
            // a null value is ok if it does not provide us any armor.
            if (value.GetObject()["armorClass"].IsNull()) {
                m_armorClass = 0;
            }
            else {
                ERROR_MSG("Failed to load armor class for " << m_name);
                return false;
            }
        }

        if (m_armorClass > 0) {
            ERROR_MSG(m_name << ": AC is " << m_armorClass);
        }

        return true;
    } //Load
} // bpl::dndbeyond::api