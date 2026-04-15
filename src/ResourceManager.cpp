#include "../include/ResourceManager.hpp"
#include "Util/Logger.hpp"

ResourceManager::ResourceManager(int initialCoin, int initialExp)
        : m_Coin(initialCoin), m_Exp(initialExp) {}

void ResourceManager::AddCoin(int amount) { m_Coin += amount; Notify();}
void ResourceManager::AddExp(int amount) { m_Exp += amount; Notify();}

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

void ResourceManager::SetOnResourceChanged(ResourceCallback callback) {
    m_OnResourceChanged = callback;
    // 第一次設定時先執行一次，確保 UI 初始化正確
    if (m_OnResourceChanged) m_OnResourceChanged(m_Coin, m_Exp);
}

void ResourceManager::Notify() {
    if (m_OnResourceChanged) {
        m_OnResourceChanged(m_Coin, m_Exp);
    }
}