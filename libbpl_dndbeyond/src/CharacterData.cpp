//
// Created by Bradley Remedios on 11/20/24.
//
#include <iostream>

#include <bpl/storage/Json.h>

#include <bpl/dndbeyond/CharacterData.h>

#include "Debug.h"

namespace bpl::dndbeyond {
    CharacterData::CharacterData() = default;

    CharacterData::~CharacterData() = default;

    bool CharacterData::Load(const bpl::storage::Payload& payload) {
        const auto jsonDoc = bpl::storage::Json::Open(payload);

        if (jsonDoc->IsNull()) {
            ERROR_MSG("Failed to load json doc");
            return false;
        }

        //  the root should always be an object
        if (!jsonDoc->IsObject()) {
            ERROR_MSG("Failed to load json doc (root not object)");

            return false;
        }

        if (!m_apiResponse.Load(jsonDoc->GetObject())) {
            ERROR_MSG("dndbeyond::ApiResponse::Load() Failed");

            return false;
        }

        return true;
    } // Load
} // bpl::dndbeyond