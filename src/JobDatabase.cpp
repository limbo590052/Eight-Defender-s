#include "JobDatabase.hpp"

// 工具函式：安全取得對應等級的 vector 數值，防止索引越界
inline int GetValueAtLevel(const std::vector<int>& vec, int level) {
    if (vec.empty()) return 0;
    if (level < 0) return vec.front();
    if (level >= static_cast<int>(vec.size())) return vec.back();
    return vec[level];
}

// 速度計算：將幀數 (F) 轉換為每秒蓄力進度百分比 (30F = 1.0秒)
float CalcSpeed(int frames) {
    if (frames <= 0) return 0.0f;
    return 100.0f / (static_cast<float>(frames) / 30.0f);
}

std::map<Job, JobStats> JobDatabase = {
        // ---------------------- Fencer 分支 (近戰輸出/坦克) ----------------------

        {Job::Fencer, {
                              Job::Fencer,
                              {16, 24, 50, 100},           // 攻擊力成長 (Lv0-Lv3)
                              {50, 45, 40, 35, 32, 29},    // 攻速 Rank B: 50F -> 29F
                              18.0f,                       // 射程: 18
                              100,                         // 進化金幣
                              {ResourceType::Exp, 50.0f, 1.0f},
                              {.restSpeed = 5.0f}}},       // 特性：無特殊能力

        {Job::Warrior, {
                              Job::Warrior,
                              {150, 250, 400, 750},        // 攻擊力成長
                              {80, 71, 64, 58},            // 攻速 Rank D+: 80F -> 58F
                              18.0f,
                              250,
                              {ResourceType::Exp, 100.0f, 1.0f},
                              {.metalBonusDamage = 5}}},   // 特性：對金屬系造成大量傷害

        {Job::Knight, {
                              Job::Knight,
                              {70, 100, 150, 280},         // 攻擊力成長
                              {35, 32, 28, 25},            // 攻速 Rank A: 35F -> 25F
                              25.0f,
                              250,
                              {ResourceType::Exp, 100.0f, 1.0f},
                              {.flyingMultiplier = 1.3f}}}, // 特性：對飛行系造成中量傷害

        {Job::Samurai, {
                              Job::Samurai,
                              {1200, 1500, 1800, 2100, 2400, 3000, 3600, 4500, 6000, 9000, 15000}, // 高成長攻擊力
                              {50, 45, 40, 35, 32, 29},    // 攻速 Rank B
                              20.0f,
                              500,
                              {ResourceType::Exp, 200.0f, 1.6f},
                              {.metalBonusDamage = 10}}},  // 特性：對金屬系特大傷害，隨等級強化

        {Job::MagicFighter, {
                              Job::MagicFighter,
                              {2600, 3200, 3800, 4400, 5000, 6200, 7400, 9300, 12000, 18000, 30000},
                              {100, 90, 80, 72, 64, 58},   // 攻速 Rank E+: 100F -> 58F
                              20.0f,
                              500,
                              {ResourceType::Exp, 200.0f, 1.0f},
                              {.slowAmount = 1}}},         // 特性：大幅減速敵人，效果隨等級提升

        {Job::DarkLord, {
                              Job::DarkLord,
                              {800},                       // 無法升級攻擊力
                              {35, 32, 28, 25},            // 攻速 Rank A
                              26.0f,
                              600,
                              {ResourceType::SpecialExp, 100.0f, 1.0f},
                              {.flyingMultiplier = 1.3f, .collectMaxHpAsExp = true}}}, // 特性：擊倒敵人吸血強化

        {Job::DragonKnight, {
                              Job::DragonKnight,
                              {1200, 1800, 2400, 3000, 3600, 4200, 5000, 6300, 8400, 12000, 21000},
                              {240, 192, 152, 121, 97, 77}, // 攻速 Rank F: 240F -> 77F (成長極高)
                              9999.0f,                     // 射程：全螢幕
                              600,
                              {ResourceType::Exp, 150.0f, 2.0f},
                              {.slowAmount = 1, .IsFullMapAttack = true}}}, // 特性：全圖攻擊不致命(留1HP)

        // ---------------------- Hunter 分支 (遠程/對空) ----------------------

        {Job::Hunter, {
                              Job::Hunter,
                              {10, 16, 40, 80},
                              {60, 54, 48, 43, 37, 33},    // 攻速 Rank C+: 60F -> 33F
                              28.0f,
                              100,
                              {ResourceType::Exp, 40.0f, 1.0f},
                              {.flyingMultiplier = 1.5f}}}, // 特性：對飛行系大量傷害

        {Job::Archer, {
                              Job::Archer,
                              {80, 120, 180, 250},
                              {40, 36, 32, 29, 27, 24},    // 攻速 Rank B+
                              34.0f,
                              250,
                              {ResourceType::Exp, 100.0f, 1.0f},
                              {.flyingMultiplier = 1.5f}}},

        {Job::Arms, {
                              Job::Arms,
                              {120, 200, 300, 450},
                              {85, 76, 68, 60},            // 攻速 Rank D: 85F -> 60F
                              40.0f,
                              250,
                              {ResourceType::Exp, 100.0f, 1.0f},
                              {.flyingMultiplier = 1.5f, .IsOnlyForward = true}}}, // 特性：僅限前方攻擊

        {Job::Ranger, {
                              Job::Ranger,
                              {300, 350, 400, 450, 500, 650, 800, 1000, 1300, 2000, 3300},
                              {25, 23, 21, 19, 17, 15},    // 攻速 Rank S: 25F -> 15F
                              40.0f,
                              500,
                              {ResourceType::Exp, 200.0f, 1.0f},
                              {.slowAmount = 1, .flyingMultiplier = 2.0f}}}, // 特性：對空特大傷害

        {Job::Thrower, {
                              Job::Thrower,
                              {400, 600, 800, 1000, 1200, 1400, 1700, 2100, 2800, 4200, 7000},
                              {30, 27, 24, 21, 19, 17},    // 攻速 Rank A+
                              40.0f,
                              500,
                              {ResourceType::Exp, 200.0f, 1.0f},
                              {.flyingMultiplier = 1.5f, .metalBonusDamage = 1}}}, // 特性：攻擊金屬系後降防

        {Job::Sniper, {
                              Job::Sniper,
                              {2000, 2700, 3400, 4100, 4800, 6000, 7200, 9000, 12000, 18000, 30000},
                              {100, 90, 80, 72, 64, 58},   // 攻速 Rank E+
                              9999.0f,
                              600,
                              {ResourceType::Exp, 250.0f, 1.0f},
                              {.flyingMultiplier = 2.0f, .IsFullMapAttack = true}}}, // 特性：全圖對空特化

        {Job::Gunner, {
                              Job::Gunner,
                              {1000, 1400, 1800, 2200, 2600, 3000, 3600, 4500, 6000, 9000, 15000},
                              {160, 143, 129, 116, 104, 93}, // 攻速 Rank E: 160F -> 93F
                              40.0f,
                              600,
                              {ResourceType::Exp, 250.0f, 1.0f},
                              {.knockbackForce = 30.0f, .flyingMultiplier = 1.5f}}}, // 特性：對空大量傷害並擊退

        // ---------------------- Thief 分支 (特殊/打幣) ----------------------

        {Job::Thief, {
                              Job::Thief,
                              {6, 12, 30, 40},
                              {30, 27, 24, 21, 19, 17},    // 攻速 Rank A+
                              15.0f,
                              100,
                              {ResourceType::Exp, 20.0f, 1.0f},
                              {.dropCoinRateMultiplier = 3}}}, // 特性：擊倒敵人金幣 3 倍

        {Job::Ninja, {
                              Job::Ninja,
                              {30, 40, 60, 120},
                              {15, 13, 12, 10},            // 攻速 Rank S+
                              15.0f,
                              300,
                              {ResourceType::Exp, 50.0f, 1.0f},
                              {.dropCoinRateMultiplier = 3}}},

        {Job::Mechanic, {
                              Job::Mechanic,
                              {60, 80, 120, 250},
                              {60, 54, 48, 43, 37, 33},    // 攻速 Rank C+
                              5.0f,
                              300,
                              {ResourceType::Gold, 50.0f, 1.0f},
                              {.slowAmount = 1}}},         // 特性：使敵人遲緩並微量停止

        {Job::Assassin, {
                              Job::Assassin,
                              {200, 250, 300, 350, 400, 500, 600, 750, 1000, 1500, 2500},
                              {12, 11, 10, 9, 8, 7},       // 攻速 Rank SS: 12F -> 7F (極快)
                              20.0f,
                              800,
                              {ResourceType::Gold, 150.0f, 1.0f},
                              {.dropCoinRateMultiplier = 3}}},

        {Job::Pirate, {
                              Job::Pirate,
                              {800, 1000, 1200, 1400, 1600, 2000, 2500, 3000, 4000, 6000, 10000},
                              {60, 54, 48, 43, 37, 33},    // 攻速 Rank C+
                              25.0f,
                              700,
                              {ResourceType::Gold, 120.0f, 1.0f},
                              {.restSpeed = 12.0f}}},      // 特性：攻擊時竊取金幣

        {Job::Trapper, {
                              Job::Trapper,
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 攻擊力為 0
                              {100, 90, 80, 72, 64, 58},   // 攻速 Rank E+
                              5.0f,
                              700,
                              {ResourceType::Gold, 100.0f, 1.0f},
                              {.slowAmount = 2}}},         // 特性：強力停止敵人

        {Job::Alchemist, {
                              Job::Alchemist,
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {100, 90, 80, 72, 64, 58},   // 攻速 Rank E+
                              25.0f,
                              750,
                              {ResourceType::Gold, 150.0f, 1.0f},
                              {.defReduction = 20.0f, .restSpeed =20.0f}}} // 特性：休息獲幣、降敵防
};