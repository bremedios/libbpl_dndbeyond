//
// Created by Bradley Remedios on 11/20/24.
//
#ifndef BPL_DNDBEYOND_CLASSES_H
#define BPL_DNDBEYOND_CLASSES_H

#include <list>

#include <rapidjson/document.h>

#include <bpl/dndbeyond/api/Class.h>

namespace bpl::dndbeyond::api {

    class Classes {
    public:
        Classes() = default;
        ~Classes() = default;

        [[nodiscard]] bool Load(const rapidjson::Value& value);
        [[nodiscard]] int getTotalLevel() const { return m_totalLevel; }
    private:
        std::list<Class> m_classes;
        int m_totalLevel = 0;
    };

} // bpl::dndbeyond::api

#endif //BPL_DNDBEYOND_CLASSES_H