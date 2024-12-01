//
// Created by Bradley Remedios on 11/21/24.
//
#include <bpl/storage/Json.h>

#include <bpl/dndbeyond/api/InventoryItem.h>

#include "../Debug.h"

namespace bpl::dndbeyond::api {
    bool InventoryItem::Load(const rapidjson::Value& value) {
        if (!value.IsObject()) {
            ERROR_MSG("Invalid root object");
            return false;
        }

        if (!bpl::storage::Json::Load(value, "equipped", m_equipped)) {
            ERROR_MSG("Failed to load level");

            return false;
        }

        if (!bpl::storage::Json::Load(value, "quantity", m_quantity)) {
            ERROR_MSG("Failed to load level");

            return false;
        }

        DEBUG_MSG("About to load definition");
        if (!value.GetObject().HasMember("definition")) {
            ERROR_MSG("No definition for InventoryItem, cannot process");

            return false;
        }

        if (!m_definition.Load(value.GetObject()["definition"])) {
            ERROR_MSG("Failed to load definition");

            return false;
        }

        return true;
    } //Load
} // bpl::dndbeyond::api