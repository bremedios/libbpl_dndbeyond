//
// Created by Bradley Remedios on 11/20/24.
//
#ifndef BPL_DNDBEYOND_CHARACTERDATA_H
#define BPL_DNDBEYOND_CHARACTERDATA_H

#include <memory>
#include <bpl/storage/Payload.h>
#include <bpl/dndbeyond/api/Response.h>
#include <bpl/dndbeyond/api/Data.h>

namespace bpl::dndbeyond {

    class CharacterData {
    public:
        CharacterData();
        ~CharacterData();

        [[nodiscard]] bool Load(const bpl::storage::Payload& payload);

        [[nodiscard]] const bpl::dndbeyond::api::Response& getApiResponse() const { return m_apiResponse; };
        [[nodiscard]] const bpl::dndbeyond::api::Data& getApiData() const { return m_apiResponse.getData(); };
        [[nodiscard]] const bpl::dndbeyond::api::Decorations& getDecorations() const { return m_apiResponse.getDecorations(); };

    private:
        bpl::dndbeyond::api::Response m_apiResponse;
    };

    typedef std::shared_ptr<CharacterData> CharacterDataPtr;

} // bpl::dndbeyond

#endif //BPL_DNDBEYOND_CHARACTERDATA_H