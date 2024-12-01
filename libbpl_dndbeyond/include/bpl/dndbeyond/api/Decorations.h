//
// Created by Bradley Remedios on 11/21/24.
//

#ifndef BPL_DNDBEYOND_API_DECORATIONS_H
#define BPL_DNDBEYOND_API_DECORATIONS_H

#include <string>

namespace bpl::dndbeyond::api {
    class Decorations {
    public:
        Decorations() = default;
        ~Decorations() = default;

        [[nodiscard]] bool Load(const rapidjson::Value& value);
        [[nodiscard]] const std::string& getAvatarUrl() const { return m_avatarUrl; }
    private:
        std::string m_avatarUrl;
    };
} // bpl::dndbeyond::api

#endif //BPL_DNDBEYOND_API_DECORATIONS_H