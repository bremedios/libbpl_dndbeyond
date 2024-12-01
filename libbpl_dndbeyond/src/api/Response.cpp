//
// Created by Bradley Remedios on 11/20/24.
//
#include <iostream>

#include <bpl/storage/Json.h>
#include <bpl/dndbeyond/api/Response.h>

#include "../Debug.h"

namespace bpl::dndbeyond::api {
    bool Response::Load(const rapidjson::Value& value) {
        if (!bpl::storage::Json::Load(value, "id", m_id)) {
            ERROR_MSG("Failed to load id");
            return false;
        }
        if (!bpl::storage::Json::Load(value, "success", m_success)) {
            ERROR_MSG("Failed to load success");
            return false;
        }
        if (!bpl::storage::Json::Load(value, "message", m_message)) {
            ERROR_MSG("Failed to load message");
            return false;
        }
        if (value.GetObject().HasMember("data")) {
            if (!m_data.Load(value.GetObject()["data"])) {
                ERROR_MSG("Failed to load data");

                return false;
            }
        }

        return true;
    } // Load
} // bpl::dndbeyond::api