//
// Created by Bradley Remedios on 11/21/24.
//
#include <iostream>

#include <bpl/storage/Json.h>

#include <bpl/dndbeyond/api/Decorations.h>

#include "../Debug.h"

namespace bpl::dndbeyond::api {
    bool Decorations::Load(const rapidjson::Value& value) {
        if (!value.IsObject()) {
            ERROR_MSG("Invalid root object");
            return false;
        }

        if (!bpl::storage::Json::Load(value, "avatarUrl", m_avatarUrl)) {
            ERROR_MSG("Failed to load Avatar URL");
            return false;
        }

        return true;
    } // Load
} // bpl::dndbeyond::api