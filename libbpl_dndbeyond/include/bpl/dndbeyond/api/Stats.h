//
// Created by Bradley Remedios on 11/20/24.
//
#ifndef BPL_DNDBEYOND_API_STATS_H
#define BPL_DNDBEYOND_API_STATS_H

#include <rapidjson/document.h>

namespace bpl::dndbeyond::api {
    enum StatType : int {
        STAT_NONE=0,
        STAT_MIN=1,
        STAT_STR=1,
        STAT_DEX=2,
        STAT_CON=3,
        STAT_INT=4,
        STAT_WIS=5,
        STAT_CHA=6,
        STAT_MAX=6
    };

    class Stats {
    public:
        [[nodiscard]] bool LoadBase(const rapidjson::Value& data);
        [[nodiscard]] bool LoadBonus(const rapidjson::Value& data);
        [[nodiscard]] bool LoadOverride(const rapidjson::Value& data);

        [[nodiscard]] int getStat(StatType stat) const;
        [[nodiscard]] int getStatMod(StatType stat) const;
    private:
        [[nodiscard]] bool LoadStat_(const rapidjson::Value &value, int* stats,  bool* statsValid);

        int m_base[STAT_MAX+1]={0};
        int m_bonus[STAT_MAX+1]={0};
        int m_override[STAT_MAX+1]={0};
        bool m_overrideValid[STAT_MAX+1]={false};
        bool m_bonusValid[STAT_MAX+1]={false};
        bool m_baseValid[STAT_MAX+1]={false};
    };
} // bpl::dndbeyond::api

#endif //BPL_DNDBEYOND_API_STATS_H