#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"


void App::Update() {
    Util::Logger::SetLevel(Util::Logger::Level::DEBUG);

    // --- 1. 狀態判定 ---
    bool isMenuOpen = m_JobMenu->IsVisible();
    bool isCombat = !m_Enemies.empty(); // 是否對戰中

    // --- 2. 邏輯更新 (Update) ---
    // 選單邏輯永遠優先處理
    m_JobMenu->Update();

    // 如果選單「沒打開」，才執行遊戲主體邏輯
    if (!isMenuOpen) {
        // 非對戰中才允許魔法陣互動 (轉職)
        if (!isCombat) {
            m_PlaceManager->Update();
        }
        for (auto& hero : m_Heroes) {
            hero->Update();
        }

        // 按鈕更新
        if (m_StartButton) {
            m_StartButton->Update();
        }

        // 敵人邏輯更新
        for (auto it = m_Enemies.begin(); it != m_Enemies.end(); ) {
            (*it)->Update();
            if ((*it)->IsDead()) {
                if ((*it)->GetPathIndex() >= Waypoints.size()) {
                    m_BaseHp -= (*it)->GetBaseDmg();
                } else {
                    m_Gold += (*it)->GetGold();
                }
                it = m_Enemies.erase(it);
            } else {
                ++it;
            }
        }

        // 偵測滑鼠位置 (Log)
        if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
            LOG_DEBUG("M Pos: X{}, Y{}", Util::Input::GetCursorPosition().x, Util::Input::GetCursorPosition().y);
        }
    }

    // 右鍵關閉選單 (這部分放在 if 外面，確保打開選單時右鍵能生效)
    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_RB)) {
        m_JobMenu->Hide();
    }

    // --- 3. 渲染區域 (Draw) ---
    // 注意：所有的 Draw 必須放在 if (!isMenuOpen) 之外！
    // 這樣選單打開時，背景物件才會繼續被繪製，不會黑屏。

    if (m_Background) {
        m_Background->Draw();
    }

    m_PlaceManager->Draw();

    if (m_startText) {
        m_startText->Draw();
    }

    if (m_StartButton) {
        m_StartButton->Draw();
    }

    for (auto& enemy : m_Enemies) {
        enemy->Draw();
    }

    for (auto& hero : m_Heroes) {
        hero->Draw();
    }

    // 最後才畫選單，確保選單卡片在所有東西的最前方
    m_JobMenu->Draw();

    // --- 4. 系統判定 ---
    if (m_BaseHp <= 0) {
        m_CurrentState = State::END;
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}
