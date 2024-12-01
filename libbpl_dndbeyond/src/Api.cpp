//
// Created by Bradley Remedios on 11/20/24.
//
#include <string>
#include <memory>

#include <bpl/net/Http.h>

#include <bpl/dndbeyond/Api.h>
#include <bpl/dndbeyond/CharacterData.h>

#include "Debug.h"

namespace bpl::dndbeyond {
    CharacterDataPtr Api::GetCharacterData(const std::string& characterId) {
        bpl::net::Http http;

        if (!http.Create()) {
            ERROR_MSG("http.Create() failed");

            return {nullptr};
        }

        std::string url = "https://character-service.dndbeyond.com/character/v5/character/" + characterId;

        auto characterData = std::make_shared<CharacterData>();

        if (!http.Get(url)) {
            ERROR_MSG("http get failed for " << url);

            return {nullptr};
        }

        if (!characterData->Load(http.getPayload())) {
            ERROR_MSG("CharacterData::Load(...) failed");

            return {nullptr};
        }

        return characterData;
    } // GetCharacterData
} // bpl::dndbeyond