#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

// 引入 Background 類別
#include "PictureObj.hpp"
#include "Button.hpp" // 引入你的新按鈕類別
#include "Util/Input.hpp"

void App::Start() {
    Util::Logger::SetLevel(Util::Logger::Level::DEBUG);
    LOG_TRACE("App Start");

    std::string bgPath = RESOURCE_DIR "/Background.png";
    LOG_DEBUG("Loading background from: {}", bgPath);
    m_Background = std::make_shared<PictureObj>(bgPath);
    m_Background->m_Transform.scale = {1.5f, 1.5f};

    m_StartButton = std::make_shared<Button>(
            "StartButton",
            RESOURCE_DIR "/StartButton.png",
            RESOURCE_DIR "/StartButton.png",
            RESOURCE_DIR "/StartButton.png"
    );

    // 設定點擊事件：切換場景或開始遊戲
    m_StartButton->SetOnClick([this]() {
        LOG_DEBUG("Game Start!");
        m_CurrentState = State::UPDATE;
    });

    m_StartButton->SetOnClick([this]() {
        LOG_DEBUG("Game Start! Clearing UI...");

        // 1. 切換遊戲狀態
        m_CurrentState = State::UPDATE;

        // 2. 清除 UI 物件指標 (shared_ptr 會自動處理記憶體)
        m_StartButton->SetVisible(false);
        m_startText->SetVisible(false);
    });

    // 加入文字圖片作為子物件
    m_startText = std::make_shared<PictureObj>(RESOURCE_DIR "/StartText.png");
    m_startText->SetZIndex(m_StartButton->GetZIndex() + 0.1f);
    m_startText->m_Transform.scale = {0.35f, 0.35f};
    m_startText->SetPivot({0, 425});

    m_StartButton->AddChild(m_startText); // 文字會跟著按鈕動

    m_StartButton->m_Transform.scale = {1.5f, 1.5f};
    m_StartButton->SetPivot({0, 100}); // 放在畫面下方一點
    m_CurrentState = State::UPDATE;
}

void App::Update() {
    Util::Logger::SetLevel(Util::Logger::Level::DEBUG);
    // 1. 渲染背景 (GameObject::Draw 會自動處理 Transform 與 ZIndex)
    if (m_Background) {
        m_Background->Draw();
    }

    if (m_StartButton) {
        m_StartButton->Update();
        m_StartButton->Draw();
    }

    if (m_startText) {
        m_startText->Draw();
    }

    // 2. 邏輯測試：按下空白鍵在 Log 輸出資訊
    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
        LOG_DEBUG("M Pos: X{}, Y{}",Util::Input::GetCursorPosition().x, Util::Input::GetCursorPosition().y);
    }

    for (auto it = m_Enemies.begin(); it != m_Enemies.end(); ) {
        (*it)->Update();
        (*it)->Draw();

        if ((*it)->IsDead()) {
            if ((*it)->GetPathIndex() >= Waypoints.size()) {
                // 敵人衝到關底了
                m_BaseHp -= (*it)->GetBaseDmg();
            } else {
                // 敵人被殺死了
                m_Gold += (*it)->GetGold();
            }
            it = m_Enemies.erase(it); // 從清單移除
        } else {
            ++it;
        }
    }

    // 2. 檢查遊戲結束
    if (m_BaseHp <= 0) {
        m_CurrentState = State::END;
    }

    /*
     * 視窗關閉邏輯。
     */
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() {
    LOG_TRACE("App End");
    // shared_ptr 會自動釋放 m_Background，不需要手動 delete
}