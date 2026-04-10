#include "MagicPlaceManager.hpp"
#include "Util/Logger.hpp"

MagicPlaceManager::MagicPlaceManager() {
    InitializePlaces();
}

void MagicPlaceManager::InitializePlaces() {
    // 根據截圖，大約是上下兩排，每排 10 個
    // 這裡的數值需要根據你的背景圖解析度微調
    float startX = -450.0f;
    float row1Y = -150.0f;  // 上排魔法陣的 Y 座標
    float row2Y = -300.0f; // 下排魔法陣的 Y 座標
    float offsetX = 100.0f; // 每個魔法陣的間距

    for (int i = 0; i < 20; i++) {
        float x = startX + (i % 10) * offsetX;
        float y = (i < 10) ? row1Y : row2Y;

        auto place = std::make_shared<MagicPlace>(
                "MagicPlace_" + std::to_string(i),
                glm::vec2(x, y)
        );
        m_Places.push_back(place);
    }
    LOG_DEBUG("MagicPlaceManager: 20 places initialized.");
}

void MagicPlaceManager::Update() {
    for (auto& place : m_Places) {
        place->Update();
    }
}

void MagicPlaceManager::Draw() {
    for (auto& place : m_Places) {
        place->Draw();
    }
}

void MagicPlaceManager::SetOnPlaceClickedCallback(const std::function<void(std::shared_ptr<MagicPlace>)>& callback) {
    for (auto& place : m_Places) {
        // 為每個 MagicPlace 綁定點擊事件
        place->SetOnClick([callback, place]() {
            if (callback) {
                callback(place);
            }
        });
    }
}