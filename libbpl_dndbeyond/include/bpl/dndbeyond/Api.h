//
// Created by Bradley Remedios on 11/20/24.
//
#ifndef BPL_DNDBEYOND_API_H
#define BPL_DNDBEYOND_API_H

#include <string>

#include <bpl/dndbeyond/CharacterData.h>

namespace bpl::dndbeyond {

    class Api {
    public:
        static CharacterDataPtr GetCharacterData(const std::string& characterId);
    };

} // bpl::dndbeyond

#endif //BPL_DNDBEYOND_API_H