#include "GameUnit.hpp"
#include "Util/Time.hpp"

GameUnit::GameUnit(const std::string& imgPath, Stats stats, const std::vector<glm::vec2>& path)
        : m_Stats(stats), m_Path(path) {
    m_Drawable = std::make_shared<Util::Image>(imgPath);
    m_Transform.translation = path[0]; // 從第一個路徑點出生
}

void GameUnit::Update() {
    if (this->IsDead()) return;
    Move();
}

void GameUnit::Move() {
    if (m_PathIndex >= m_Path.size()) {
        m_Dead = true; // 觸發扣血邏輯
        return;
    }

    glm::vec2 target = m_Path[m_PathIndex];
    glm::vec2 pos = m_Transform.translation;
    float dist = glm::distance(pos, target);

    if (dist < 5.0f) {
        m_PathIndex++;
    } else {
        glm::vec2 dir = glm::normalize(target - pos);
        // 使用 speed 進行位移
        m_Transform.translation += dir * m_Stats.speed;
    }
}

void GameUnit::TakeDamage(float dmg, bool isMelee) {
    float finalDmg = dmg;
    // 飛行單位：近戰傷害 1/3
    if (m_Stats.type == Type::FLY && isMelee) finalDmg /= 3.0f;
    // 金屬單位：固定受傷 1
    if (m_Stats.type == Type::METAL) finalDmg = 1.0f;

    m_Stats.hp -= finalDmg;
    if (m_Stats.hp <= 0) m_Dead = true;
}

