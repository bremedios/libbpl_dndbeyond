//
// Created by Bradley Remedios on 11/20/24.
//
#include <iostream>

#include <bpl/storage/Json.h>
#include <bpl/dndbeyond/api/Class.h>

#include "../Debug.h"

namespace bpl::dndbeyond::api {
    bool Class::Load(const rapidjson::Value& value) {
        if (!value.IsObject()) {
            ERROR_MSG("Invalid root object");
            return false;
        }

        if (!bpl::storage::Json::Load(value, "level", m_level)) {
            ERROR_MSG("Failed to load level");
            return false;
        }

        return true;
    } // Load
} // bpl::dndbeyond::api