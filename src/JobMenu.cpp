#include "JobMenu.hpp"
#include "config.hpp"
#include "Util/Logger.hpp"

JobMenu::JobMenu() {
    // 1. 定義轉職樹
    m_JobTree = {
            {"Root",     {"Fencer", "Hunter", "Thief"}},
            {"Fencer",   {"Warrior", "Knight"}},
            {"Warrior",  {"Samurai", "MagicFighter"}},
            {"Knight",   {"DarkLord", "DragonKnight"}},
            {"Hunter",   {"Archer", "Arms"}},
            {"Archer",   {"Ranger", "Thrower"}},
            {"Arms",     {"Sniper", "Gunner"}},
            {"Thief",    {"Ninja", "Mechanic"}},
            {"Ninja",    {"Assassin", "Pirate"}},
            {"Mechanic", {"Trapper", "Alchemist"}}
    };
}

void JobMenu::Show(std::shared_ptr<MagicPlace> owner) {
    m_CurrentOwner = owner;
    m_Visible = true;
    RefreshMenu("Root"); // 每次打開都從初始職業開始
}

void JobMenu::RefreshMenu(const std::string& jobKey) {
    m_ActiveButtons.clear();
    if (m_JobTree.find(jobKey) == m_JobTree.end()) return;

    auto& branches = m_JobTree[jobKey];
    float spacing = 300.0f; // 因為卡片間距（原為 180）

    for (size_t i = 0; i < branches.size(); ++i) {
        std::string nextJob = branches[i];
        // 1. 定義該職業的卡片路徑
        std::string cardPath = RESOURCE_DIR "/JobCard/" + nextJob + ".png";
        // 2. 將底圖直接設為職業卡片
        std::vector<std::string> jobCardUI = {
                cardPath, // 一般狀態
                cardPath, // 懸停狀態 (Hover)
                cardPath  // 點擊狀態
        };
        // 3. 建立按鈕：底圖用職業卡，Overlay 傳空字串 ""
        auto btn = std::make_shared<Button>(
                nextJob,
                jobCardUI,
                ""
        );
        // ------------------

        btn->SetZIndex(50.0f);

        // 計算排列位置
        float xOffset = (static_cast<float>(i) - (branches.size() - 1) / 2.0f) * spacing;
        btn->m_Transform.translation = MENU_CENTER_POS + glm::vec2(xOffset, 0);
        btn->m_Transform.scale = glm::vec2(1.5f,1.5f); //縮放jobcard (例如 0.8 倍)

        // 如果圖片太大，可以在此加上縮放 (例如 0.8 倍)
        // btn->m_Transform.scale = glm::vec2(0.8f, 0.8f);

        btn->SetOnClick([this, nextJob]() {
            if (m_JobTree.count(nextJob)) {
                this->RefreshMenu(nextJob);
            } else {
                // 觸發轉職/部屬
                if (m_CurrentOwner) {
                    // 1. 取得座標
                    glm::vec2 spawnPos = m_CurrentOwner->GetPosition();

                    // 2. 檢查是「新部屬」還是「舊轉職」
                    // 如果是轉職，要先刪除舊單位 (假設 m_CurrentOwner 綁定了單位參考)

                    // 3. 生成新英雄
                    // SpawnHero(nextJob, spawnPos);

                    // 4. 鎖定並隱藏魔法陣
                    m_CurrentOwner->SetOccupied(true);
                    m_CurrentOwner->SetVisible(false);
                }
                this->Hide();
            }
        });
        m_ActiveButtons.push_back(btn);
    }

    std::vector<std::string> cancelUI =  {
            RESOURCE_DIR "/Cancel.png",
            RESOURCE_DIR "/Cancel.png",
            RESOURCE_DIR "/Cancel.png"
    };

    // 3. 固定加上「取消」按鈕 cancelBtn
    auto cancelBtn = std::make_shared<Button>(
            "Cancel",
            cancelUI,
            ""
    );

    //cancelBtn位置
    cancelBtn->SetZIndex(50.0f);
    cancelBtn->m_Transform.translation = MENU_CENTER_POS + glm::vec2(0, -282);
    cancelBtn->SetOnClick([this]() { this->Hide(); });
    m_ActiveButtons.push_back(cancelBtn);
}

void JobMenu::Update() {
    if (!m_Visible) return;
    // 必須使用反向迭代或小心處理，因為 RefreshMenu 會清空 vector
    // 這裡簡單處理，因為 SetOnClick 會在下一幀或函式末端才觸發 Refresh
    for (size_t i = 0; i < m_ActiveButtons.size(); ++i) {
        m_ActiveButtons[i]->Update();
    }
}

void JobMenu::Draw() {
    if (!m_Visible) return;
    for (auto& btn : m_ActiveButtons) btn->Draw();
}

void JobMenu::Hide() {
    m_Visible = false;
    m_ActiveButtons.clear();
}