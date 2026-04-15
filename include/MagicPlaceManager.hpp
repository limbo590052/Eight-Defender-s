#ifndef MAGIC_PLACE_MANAGER_HPP
#define MAGIC_PLACE_MANAGER_HPP

#include <vector>
#include <memory>
#include "MagicPlace.hpp"

class MagicPlaceManager {
public:
    MagicPlaceManager();

    void Update();
    void Draw();

    // 讓 App 可以傳入「當魔法陣被點擊時要做什麼」的邏輯
    void SetOnPlaceClickedCallback(const std::function<void(std::shared_ptr<MagicPlace>)>& callback);
    const std::vector<std::shared_ptr<MagicPlace>>& GetPlaces() const { return m_Places; }
    void SetAllVisible(bool visible);

private:
    std::vector<std::shared_ptr<MagicPlace>> m_Places;
    std::function<void(std::shared_ptr<MagicPlace>)> m_OnPlaceClicked;
    // 內部輔助函式：用來排列 20 個位置
    void InitializePlaces();
};

#endif