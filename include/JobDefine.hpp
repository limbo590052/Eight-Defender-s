#pragma once
#include <vector>
#include <map>
#include <string>

enum class Job {
    Fencer, Hunter, Thief,
    Warrior, Knight, Archer, Arms, Ninja, Mechanic,
    Samurai, MagicFighter, DarkLord, DragonKnight,
    Ranger, Thrower, Sniper, Gunner,
    Assassin, Pirate, Trapper, Alchemist
};

enum class ResourceType { Gold, Exp, SpecialExp };

Job StringToJob(const std::string& name);

struct JobProperties {
    int slowAmount = 0;             // [修改] 減少速度的絕對值 (0~9)
    float knockbackForce = 0.0f;
    float flyingMultiplier = 1.0f;
    int metalBonusDamage = 1;       // [新] 對金屬怪物的額外固定傷害 (預設 1)
    float defReduction = 0.0f;
    float restSpeed = 5.0f;
    bool collectMaxHpAsExp = false;
    bool IsOnlyForward = false;
    bool IsFullMapAttack = false;
    int dropCoinRateMultiplier = 1;
};

struct UpgradeInfo {
    ResourceType resType;
    float baseAmount;
    float costMultiplier = 1.0f;
};

struct JobStats {
    Job job;
    std::vector<int> attackDamageLevels; // 攻擊力 (Lv0~Lv10)
    std::vector<int> attackFrameLevels;  // 攻擊幀數 (Lv0~Lv5/10)
    float attackRange;                   // 範圍 (已換算 1.5x)
    int evolveGold;
    UpgradeInfo upgradeInfo;
    JobProperties props;
};