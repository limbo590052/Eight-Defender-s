
#ifndef EIGHTDEFENDERS_HERO_HPP
#define EIGHTDEFENDERS_HERO_HPP

#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"
#include "Util/Image.hpp"
#include "JobDefine.hpp"
#include <string>
#include <memory>
#include "ProgressBar.hpp"

struct HeroStats {
    float attackDamage;
    float attackSpeed;   // 蓄力速度 (每秒增加的進度)
    float attackRange;
    int currentLevel;
    int upgradeCost;
};

class Hero : public Util::GameObject {
public:
    Hero(const std::string& jobName, glm::vec2 pos);

    void Update();
    void Draw();

    // 觸發攻擊動畫
    void PlayAttackAnimation();

private:
    std::string m_JobName;
    Job m_JobType;

    // 角色本體圖
    std::shared_ptr<Util::GameObject> m_Sprite;

    // 攻擊特效動畫 (例如揮劍或火花)
    std::shared_ptr<Util::GameObject> m_AttackEffect;
    bool m_IsAttacking = false;

    JobStats m_Stats; // 儲存該職業的基礎數值
    std::shared_ptr<Util::Animation> m_AnimationLoop;

    std::shared_ptr<ProgressBar> m_AttackBar; // 攻擊蓄力條
    std::shared_ptr<ProgressBar> m_RestBar;   // 休息進度條
};

#endif
