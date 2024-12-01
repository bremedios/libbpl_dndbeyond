//
// Created by Bradley Remedios on 11/20/24.
//
#include <iostream>

#include <bpl/storage/Json.h>

#include <bpl/dndbeyond/api/Stats.h>

#include "../Debug.h"

namespace bpl::dndbeyond::api {
    bool Stats::LoadStat_(const rapidjson::Value &value, int* stats,  bool* statsValid) {
        if (!value.IsArray()) {
            ERROR_MSG("Invalid root object");
            return false;
        }

        if ((nullptr == stats) || (nullptr == statsValid)){
            ERROR_MSG("Invalid stats or valid array");

            return false;
        }

        //
        //Initialize our stats.
        //
        for (int i = 0; i <= StatType::STAT_MAX;++i){
            stats[i] = 0;
            statsValid[i] = false;
        }

        for ( int i = 0; i < value.Size(); ++i) {
            int    stat=StatType::STAT_NONE;
            int    statValue = 0;

            if (!bpl::storage::Json::Load(value[i], "id", stat)) {
                ERROR_MSG("Failed to load stat id");
                return false;
            }

            if (!bpl::storage::Json::Load(value[i], "value", statValue)) {
                ERROR_MSG("Failed to load stat value");
                continue;
            }

            if ((stat > StatType::STAT_MAX) || (stat < StatType::STAT_MIN)) {
                ERROR_MSG("Stat type out of range");
                continue;
            }

            stats[stat] = statValue;
            statsValid[stat] = true;
        }

        return true;
    } // LoadStat_

    bool Stats::LoadBase(const rapidjson::Value& value)
    {
        return LoadStat_(value, m_base, m_baseValid);
    } // LoadBase

    bool Stats::LoadBonus(const rapidjson::Value& value)
    {
        return LoadStat_(value, m_bonus, m_bonusValid);
    } // LoadBase

    bool Stats::LoadOverride(const rapidjson::Value& value)
    {
        return LoadStat_(value, m_override, m_overrideValid);
    } // LoadBase

    int Stats::getStatMod(StatType stat) const {
        if ((stat > StatType::STAT_MAX)  || (stat < StatType::STAT_MIN)) {
            ERROR_MSG("Stat type out of range");
            return 0;
        }

        return (getStat(stat) - 10) / 2;
    } // getStatMod

    int Stats::getStat(StatType stat) const {
        if ((stat > StatType::STAT_MAX)  || (stat < StatType::STAT_MIN)) {
            ERROR_MSG("Stat type out of range");
            return -1;;
        }

        if (m_overrideValid[stat]) {
            return m_override[stat];
        }

        return m_base[stat] + m_bonus[stat];
    } // getStat
} // bpl::dndbeyond::api