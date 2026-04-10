
#ifndef EIGHTDEFENDERS_HERO_HPP
#define EIGHTDEFENDERS_HERO_HPP

#include "vector"

struct HeroStats {
    float attackDamage;
    float attackSpeed;   // 蓄力速度 (每秒增加的進度)
    float attackRange;
    int currentLevel;
    int upgradeCost;
};

//class Hero {
//
//};


#endif //EIGHTDEFENDERS_HERO_HPP
