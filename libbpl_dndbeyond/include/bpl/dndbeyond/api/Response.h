//
// Created by Bradley Remedios on 11/20/24.
//
#ifndef BPL_DNDBEYOND_API_RESPONSE_H
#define BPL_DNDBEYOND_API_RESPONSE_H

#include <string>

#include <rapidjson/document.h>

#include <bpl/dndbeyond/api/Decorations.h>
#include <bpl/dndbeyond/api/Data.h>

namespace bpl::dndbeyond::api {
    class Response {
    public:
        Response() = default;
        ~Response()= default;

        [[nodiscard]] bool Load(const rapidjson::Value& value);

        [[nodiscard]] int getId() const { return m_id;}
        [[nodiscard]] int getSuccess() const { return m_success;}
        [[nodiscard]] const std::string& getMessage() const { return m_message;}
        [[nodiscard]] const Data& getData() const { return m_data;}
        [[nodiscard]] const Stats& getStats() const { return m_data.getStats();}
        [[nodiscard]] const Decorations& getDecorations() const { return m_data.getDecorations();}

    private:
        int m_id=-1;
        bool m_success=false;
        std::string m_message;
        Data m_data;

    }; // Response
} // bpl::dndbeyond::api

#endif //BPL_DNDBEYOND_API_RESPONSE_H