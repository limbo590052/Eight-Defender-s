#include "MagicPlace.hpp"

// 如果你的 Button.hpp 裡已經有 m_Transform (它是 public)，
// 我們就直接操作它，不要透過 GetTransform() 抓引用。

MagicPlace::MagicPlace(const std::string& name, glm::vec2 pos) {
    std::vector<std::string> layers(3, RESOURCE_DIR "/MagicPlace.png");
    m_Object = std::make_shared<Button>(
            name,
            layers,
            ""
    );
    m_Object->SetVisible(false);
    // 直接設定位置，不要用 auto&
    m_Object->m_Transform.translation = pos;
    m_Object->m_Transform.scale = m_NormalScale;
}

void MagicPlace::Update() {
    // 確保被佔用時，物件是不顯示的
    if (m_IsOccupied) {
        if (m_Object->IsVisible()) {
            m_Object->SetVisible(false);
        }
        return;
    }
    // 1. 偵測懸停
    bool isHovering = m_Object->IsMouseHovering();

    // 2. 決定目標縮放
    glm::vec2 targetScale = isHovering ? m_HoverScale : m_NormalScale;

    // 平滑線性插值 (Lerp)
    float lerpX = (targetScale.x - m_Object->m_Transform.scale.x) * m_LerpFactor;
    float lerpY = (targetScale.y - m_Object->m_Transform.scale.y) * m_LerpFactor;

    m_Object->m_Transform.scale.x += lerpX;
    m_Object->m_Transform.scale.y += lerpY;

    // 4. 更新
    m_Object->Update();
}

void MagicPlace::Draw() {
    if (!m_IsOccupied) { // 只有在可見且未被佔用時才畫
        m_Object->Draw(); // Visible->Button->GameObject
    }
}

void MagicPlace::SetOnClick(const std::function<void()>& callback) {
    m_Object->SetOnClick(callback);
}

void MagicPlace::SetOccupied(bool occupied) {
    m_IsOccupied = occupied;//(True)
    // 當被佔用時，隱藏內部的 Button，使其無法被點擊觸發 SelectionMenu
    m_Object->SetVisible(!occupied); // 如果被佔用，按鈕就不見（不可見也不可點擊）
}

void MagicPlace::SetVisible(bool visible) {
    // 只有在未被佔用的情況下，外部的顯示控制才有效
    if (!m_IsOccupied) {
        m_Object->SetVisible(visible);
    }
}