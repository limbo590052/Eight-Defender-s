#include <functional>

class ResourceManager {
public:
    ResourceManager(int coin, int exp);

    void AddCoin(int amount);
    void AddExp(int amount);

    int GetCoin() const;
    int GetExp() const;

    bool CanAfford(int coinReq, int expReq) const;

    bool Spend(int coinReq, int expReq);

    using ResourceCallback = std::function<void(int, int)>;
    void SetOnResourceChanged(ResourceCallback callback);

private:
    int m_Coin = 0;
    int m_Exp = 0;
    ResourceCallback m_OnResourceChanged;
    void Notify();
};