//
// Created by Bradley Remedios on 11/20/24.
//
#ifndef BPL_DNDBEYOND_API_DATA_H
#define BPL_DNDBEYOND_API_DATA_H

#include "rapidjson/document.h"

#include <bpl/dndbeyond/api/Stats.h>
#include <bpl/dndbeyond/api/Classes.h>
#include <bpl/dndbeyond/api/Decorations.h>
#include <bpl/dndbeyond/api/Inventory.h>

namespace bpl::dndbeyond::api {
    class Data {
    public:
        Data();
        ~Data();

        [[nodiscard]] bool Load(const rapidjson::Value& data);

        [[nodiscard]] int getCharacterId() const { return m_characterId; }
        [[nodiscard]] int getUserId() const { return m_userId; }
        [[nodiscard]] const std::string& getUsername() const { return m_username; }
        [[nodiscard]] const std::string& getName() const { return m_name; }
        [[nodiscard]] bool hasInspiration() const { return m_inspiration;}
        [[nodiscard]] int getBaseHitPoints() const { return m_baseHitPoints; }
        [[nodiscard]] int getBonusHitPoints() const { return m_bonusHitPoints; }
        [[nodiscard]] int getOverrideHitPoints() const { return m_overrideHitPoints; }
        [[nodiscard]] int getRemovedHitPoints() const { return m_removedHitPoints; }
        [[nodiscard]] int getTemporaryHitPoints() const { return m_tempHitPoints; }
        [[nodiscard]] const Stats& getStats() const { return m_stats; }
        [[nodiscard]] const Classes& getClasses() const { return m_classes; }
        [[nodiscard]] const Decorations& getDecorations() const { return m_decorations; }
        [[nodiscard]] const Inventory& getInventory() const { return m_inventory; }
        [[nodiscard]] int getArmorClass() const;
    private:
        int m_characterId=-1;
        int m_userId=-1;
        std::string m_username;
        std::string m_name;
        bool m_inspiration=false;
        int m_baseHitPoints=0;
        int m_bonusHitPoints=0;
        int m_tempHitPoints=0;
        int m_removedHitPoints=0;
        int m_overrideHitPoints=0;
        int m_ac = 0;

        Stats m_stats;
        Classes m_classes;
        Decorations m_decorations;
        Inventory   m_inventory;
    };
}; // bpl::dndbeyond::api

#endif //BPL_DNDBEYOND_API_DATA_H