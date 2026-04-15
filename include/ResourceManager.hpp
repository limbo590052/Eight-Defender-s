class ResourceManager {
public:
    ResourceManager(int coin, int exp);

    void AddCoin(int amount);
    void AddExp(int amount);

    int GetCoin() const;
    int GetExp() const;


    bool CanAfford(int coinReq, int expReq) const;

    bool Spend(int coinReq, int expReq);

private:
    int m_Coin;
    int m_Exp;
};