#include "LevelInfoUI.hpp"

LevelInfoUI::LevelInfoUI() {
    // --- 1. Panel Base & Top (假設只有一張，存入 vector) ---
    auto base = std::make_shared<PictureObj>(RESOURCE_DIR "/LevelPanel/Base1.png");
    base->SetZIndex(10);
    base->m_Transform.translation = {-360.f, 160.f};
    base->m_Transform.scale = {1.2f, 1.2f};
    m_PanelBase.push_back(base);
    AddChild(base);

    auto top = std::make_shared<PictureObj>(RESOURCE_DIR "/LevelPanel/Top1.png");
    top->SetZIndex(11);
    top->m_Transform.translation = {-360.f, 145.f};
    top->m_Transform.scale = {1.2f, 1.2f};
    m_PanelTop.push_back(top);
    AddChild(top);

    // --- 2. Type 相關 (7 種類型圖片 + 一張 "Type" 文字圖) ---
    m_TypeText = std::make_shared<PictureObj>(RESOURCE_DIR "/LevelPanel/TypeText.png");
    m_TypeText->SetZIndex(12);
    m_TypeText->m_Transform.translation = {-360.f, 190.f};
    m_TypeText->m_Transform.scale = {1.20f, 1.20f};
    AddChild(m_TypeText);

    std::vector<std::string> typeNames = {"Metal", "Fly", "Rapid", "Boss", "Mix", "Normal", "Strong"};
    for (const auto& name : typeNames) {
        auto typeImg = std::make_shared<PictureObj>(RESOURCE_DIR "/TypeText/" + name + ".png");
        typeImg->SetVisible(false);
        typeImg->SetZIndex(13);
        typeImg->m_Transform.translation = {-360.f, 150.f};
        typeImg->m_Transform.scale = {1.25f, 1.25f};
        m_Type.push_back(typeImg);
        AddChild(typeImg);
    }

    // --- 3. Speed 相關 (SpeedPanel + 0~10 圖片) ---
    m_SpeedPanel = std::make_shared<PictureObj>(RESOURCE_DIR "/SpeedLevel/SpeedPanel.png");
    m_SpeedPanel->SetZIndex(14);
    m_SpeedPanel->m_Transform.translation = {-360.f, 70.f};
    m_SpeedPanel->m_Transform.scale = {1.5f, 1.5f};
    AddChild(m_SpeedPanel);

    for (int i = 0; i <= 10; ++i) {
        auto sNum = std::make_shared<PictureObj>(RESOURCE_DIR "/SpeedLevel/" + std::to_string(i) + ".png");
        sNum->SetVisible(false);
        sNum->SetZIndex(15);
        sNum->m_Transform.translation = {-360.f, 85.f};
        sNum->m_Transform.scale = {1.5f, 1.5f};
        m_SpeedNum.push_back(sNum);
        AddChild(sNum);
    }

    // --- 4. Stage 相關 (Title "STAGE" + 1~25 圖片) ---
    m_StageTitle = std::make_shared<PictureObj>(RESOURCE_DIR "/Level/Title.png");
    m_StageTitle->SetZIndex(16);
    m_StageTitle->m_Transform.translation = {0.f, 195.f};
    m_StageTitle->m_Transform.scale = {0.8f, 0.8f};
    AddChild(m_StageTitle);

    for (int i = 1; i <= 25; ++i) {
        auto stNum = std::make_shared<PictureObj>(RESOURCE_DIR "/Level/" + std::to_string(i) + ".png");
        stNum->SetVisible(false);
        stNum->SetZIndex(17);
        stNum->m_Transform.translation = {65.f, 195.f};
        stNum->m_Transform.scale = {0.5f, 0.5f};
        m_StageNum.push_back(stNum);
        AddChild(stNum);
    }
}

void LevelInfoUI::SetLevel(int stage, const std::string& type, int speed) {
    // 全部隱藏
    for (auto& t : m_Type) t->SetVisible(false);
    for (auto& s : m_SpeedNum) s->SetVisible(false);
    for (auto& n : m_StageNum) n->SetVisible(false);

    // 1. 設定敵人種類 (比對字串或索引)
    std::vector<std::string> typeNames = {"Metal", "Fly", "Rapid", "Boss", "Mix", "Normal", "Strong"};
    for (size_t i = 0; i < typeNames.size(); ++i) {
        if (type == typeNames[i]) {
            m_Type[i]->SetVisible(true);
            break;
        }
    }

    // 2. 設定速度 (0-10)
    if (speed >= 0 && speed <= 10) {
        m_SpeedNum[speed]->SetVisible(true);
    }

    // 3. 設定關卡 (1-25)
    if (stage >= 1 && stage <= 25) {
        m_StageNum[stage - 1]->SetVisible(true);
    }
}
bool LevelInfoUI::IsVisible(){return m_Visible;};

void LevelInfoUI::Draw() {
    // 如果父物件本身不可見，直接返回
    if (!IsVisible()) return;

    // 渲染順序：底層 -> 高層
    // 1. Panel Base (Vector)
    for (auto& obj : m_PanelBase) if (obj->IsVisible()) obj->Draw();

    // 2. Panel Top (Vector)
    for (auto& obj : m_PanelTop) if (obj->IsVisible()) obj->Draw();

    // 3. 固定標籤文字
    if (m_TypeText->IsVisible()) m_TypeText->Draw();
    if (m_SpeedPanel->IsVisible()) m_SpeedPanel->Draw();
    if (m_StageTitle->IsVisible()) m_StageTitle->Draw();

    // 4. 動態內容 (Vector) - 這裡只會畫出 SetLevel 啟用的那個
    for (auto& obj : m_Type)     if (obj->IsVisible()) obj->Draw();
    for (auto& obj : m_SpeedNum) if (obj->IsVisible()) obj->Draw();
    for (auto& obj : m_StageNum) if (obj->IsVisible()) obj->Draw();
}