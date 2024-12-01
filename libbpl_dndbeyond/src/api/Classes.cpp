//
// Created by Bradley Remedios on 11/20/24.
//
#include <iostream>

#include <bpl/dndbeyond/api/Classes.h>

#include "../Debug.h"

namespace bpl::dndbeyond::api {
    bool Classes::Load(const rapidjson::Value& value) {
        m_totalLevel = 0;

        if (!value.IsArray()) {
            ERROR_MSG("Invalid root object");
            return false;
        }

        for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
            Class charClass;

            if (!charClass.Load(value[i])) {
                ERROR_MSG("Failed to load class " << i);

                return false;
            }

            m_totalLevel += charClass.getLevel();

            m_classes.emplace_back(charClass);
        }
        return true;
    } // Load
} // bpl::dndbeyond:::api