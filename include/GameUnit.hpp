#ifndef GAME_UNIT_HPP
#define GAME_UNIT_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <vector>
#include <glm/vec2.hpp>

class GameUnit : public Util::GameObject {
public:
    enum class Type { NORMAL, FLY, RAPID, METAL, BOSS };

    struct Stats {
        float hp;
        float speed;
        int gold;      // 擊殺獎勵金錢
        int exp;       // 擊殺獎勵經驗 (CP)
        int baseDmg;   // 衝到關底扣的村人血量
        Type type;
    };

    GameUnit(const std::string& imgPath, Stats stats, const std::vector<glm::vec2>& path);

    void TakeDamage(float dmg, bool isMelee);

    bool IsDead() const { return m_Dead; }
    int GetGold() const { return m_Stats.gold; }
    void Update();
    int GetExp() const { return m_Stats.exp; }
    int GetBaseDmg() const { return m_Stats.baseDmg; }
    size_t GetPathIndex() const { return m_PathIndex; }

private:
    Stats m_Stats;
    bool m_Dead = false;
    std::vector<glm::vec2> m_Path;
    size_t m_PathIndex = 0;

    void Move();
};

#endif