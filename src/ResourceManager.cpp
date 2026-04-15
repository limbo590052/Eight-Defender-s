#include "../include/ResourceManager.hpp"
#include "Util/Logger.hpp"

ResourceManager::ResourceManager(int initialCoin, int initialExp)
        : m_Coin(initialCoin), m_Exp(initialExp) {}

void ResourceManager::AddCoin(int amount) { m_Coin += amount; }
void ResourceManager::AddExp(int amount) { m_Exp += amount; }

int ResourceManager::GetCoin() const { return m_Coin; }
int ResourceManager::GetExp() const { return m_Exp; }

bool ResourceManager::CanAfford(int coinReq, int expReq) const {
    return (m_Coin >= coinReq && m_Exp >= expReq);
}

bool ResourceManager::Spend(int coinReq, int expReq) {
    if (CanAfford(coinReq, expReq)) {
        m_Coin -= coinReq;
        m_Exp -= expReq;
        LOG_INFO("升級扣除成功！剩餘 Coin: {}, EXP: {}", m_Coin, m_Exp);
        return true;
    }
    LOG_WARN("通貨不足！需要: {}/{}，當前: {}/{}", coinReq, expReq, m_Coin, m_Exp);
    return false;
}