//
// Created by Bradley Remedios on 11/20/24.
//
//#define DEBUG_PRINT_KEYS 1

#include <iostream>

#include <bpl/storage/Json.h>

#include <bpl/dndbeyond/api/Data.h>

#include "../Debug.h"

namespace bpl::dndbeyond::api {
    Data::Data() {
    } // Data

    Data::~Data() {
    } // ~Data

    bool Data::Load(const rapidjson::Value& value)
    {
        if (!value.IsObject()) {
            ERROR_MSG("Invalid root object");
            return false;
        }

        if (!bpl::storage::Json::Load(value, "id", m_characterId)) {
            ERROR_MSG("Failed to load id");
            return false;
        }
        if (!bpl::storage::Json::Load(value, "userId", m_userId)) {
            ERROR_MSG("Failed to load userId");
            return false;
        }

        if (!bpl::storage::Json::Load(value, "username", m_username)) {
            ERROR_MSG("Failed to load username");
            return false;
        }
        if (!bpl::storage::Json::Load(value, "name", m_name)) {
            ERROR_MSG("Failed to load name");
            return false;
        }
        if (!bpl::storage::Json::Load(value, "inspiration", m_inspiration)) {
            ERROR_MSG("Failed to load inspiration");
            return false;
        }
        if (!bpl::storage::Json::Load(value, "baseHitPoints", m_baseHitPoints)) {
            ERROR_MSG("Failed to load baseHitPoints");
            return false;
        }
        if (!bpl::storage::Json::Load(value, "bonusHitPoints", m_bonusHitPoints)) {
            ERROR_MSG("WARN: No bonus hit points set.");
            m_bonusHitPoints = 0;
        }
        if (!bpl::storage::Json::Load(value, "temporaryHitPoints", m_tempHitPoints)) {
            ERROR_MSG("Failed to load tempHitPoints");
            return false;
        }
        if (!bpl::storage::Json::Load(value, "removedHitPoints", m_removedHitPoints)) {
            ERROR_MSG("Failed to load removedHitPoints");
            return false;
        }
        if (!bpl::storage::Json::Load(value, "overrideHitPoints", m_overrideHitPoints)) {
            ERROR_MSG("WARN: No override hit points set.");
            m_overrideHitPoints =0;
        }

        if (!m_stats.LoadBase(value.GetObject()["stats"])) {
            ERROR_MSG("Failed to load stats");

            return false;
        }

        if (!m_stats.LoadBonus(value.GetObject()["bonusStats"])) {
            ERROR_MSG("Failed to load bonusStats");

            return false;
        }

        if (!m_stats.LoadOverride(value.GetObject()["overrideStats"])) {
            ERROR_MSG("Failed to load overrideStats");

            return false;
        }
#if defined(DEBUG_PRINT_KEYS)
        DEBUG_MSG("Data::Load(): Keys:");

        for ( auto item = value.GetObject().MemberBegin(); item != value.GetObject().MemberEnd(); ++item) {
            DEBUG_MSG("    " << item->name.GetString());
        }
#endif

        if (!m_classes.Load(value.GetObject()["classes"])) {
            ERROR_MSG("Failed to load classes");

            return false;
        }

        if (!m_decorations.Load(value.GetObject()["decorations"])) {
            ERROR_MSG("Failed to load decorations");

            return false;
        }

        if (!m_inventory.Load(value.GetObject()["inventory"])) {
            ERROR_MSG("Failed to load inventory");

            return false;
        }

        m_baseHitPoints += m_classes.getTotalLevel() * m_stats.getStatMod(StatType::STAT_CON);

        return true;
    }

    int Data::getArmorClass() const {
        int baseArmorClass = 0;

        for (auto &it : m_inventory.getItems()) {
            if (it.isEquipped()) {
                baseArmorClass += it.getArmorClass();
            }
        }

        return baseArmorClass + m_stats.getStatMod(StatType::STAT_DEX);
    }// getArmorClass
} // bpl::dndbeyond::api