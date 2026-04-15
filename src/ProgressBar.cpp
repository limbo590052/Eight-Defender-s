#include "ProgressBar.hpp"

ProgressBar::ProgressBar(const std::string& bgPath, const std::string& fillPath, glm::vec2 pos) {
    // 設定父殼的位置
    m_Transform.translation = pos;

    m_Background = std::make_shared<Util::GameObject>();
    m_Background->SetDrawable(std::make_shared<Util::Image>(bgPath));
    m_Background->m_Transform.translation = m_Transform.translation;
    m_Background->SetZIndex(this->GetZIndex());
    AddChild(m_Background);

    // 2. 初始化填充條
    m_Fill = std::make_shared<Util::GameObject>();
    m_Fill->SetDrawable(std::make_shared<Util::Image>(fillPath));
    m_Fill->m_Transform.translation = m_Transform.translation;
    m_Fill->SetZIndex(this->GetZIndex());
    m_Fill->SetPivot({0.0f, 0.0f});
    AddChild(m_Fill);

    SetProgress(0.0f);
}

void ProgressBar::SetProgress(float ratio) {
    m_Progress = std::clamp(ratio, 0.0f, 1.0f);

    // 直接存取成員變數 m_Transform，而不是透過 GetTransform() 副本
    m_Fill->m_Transform.scale.x = m_Progress;
}

void ProgressBar::Draw() {
    if (!m_Background || !m_Fill) return;


    m_Background->Draw();

    // 計算進度縮放
    float targetScaleX = m_Transform.scale.x * m_Progress;
    m_Fill->m_Transform.scale.x = targetScaleX;

    // --- 關鍵補償邏輯 ---
    // 假設原始圖片寬度為 W。
    // 因為從中心縮放，左邊界會往內縮 (1 - m_Progress) * W * 0.5
    // 我們需要將 X 座標向右移動這段距離，讓左端看起來像固定住
    // 注意：這裡的 150.0f 應替換為你 Fill 圖片的原始寬度 (Pixel)
    float originalWidth = 50.0f;
    float offset = (originalWidth * m_Transform.scale.x * (1.0f - m_Progress)) / 2.0f;

    m_Fill->m_Transform.translation.x = m_Transform.translation.x - offset;

    m_Fill->Draw();
}