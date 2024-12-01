//
// Created by Bradley Remedios on 11/20/24.
//
#ifndef BPL_DNDBEYOND_API_CLASS_H
#define BPL_DNDBEYOND_API_CLASS_H

#include <rapidjson/document.h>

namespace bpl::dndbeyond::api {
    class Class {
    public:
        Class() = default;
        ~Class() = default;

        [[nodiscard]] bool Load(const rapidjson::Value& value);
        [[nodiscard]] int getLevel() const {return m_level;}

    private:
        int m_level = 0;
    }; // Class
} // bpl::dndbeyond::api

#endif //BPL_DNDBEYOND_API_CLASS_H