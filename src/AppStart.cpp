#include "App.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    Util::Logger::SetLevel(Util::Logger::Level::DEBUG);
    LOG_TRACE("App Start");

    // 1. 載入基礎背景
    std::string bgPath = RESOURCE_DIR "/Background.png";
    LOG_DEBUG("Loading background from: {}", bgPath);
    m_Background = std::make_shared<PictureObj>(bgPath);
    m_Background->m_Transform.scale = {1.5f, 1.5f};

     auto startsPics = std::vector<std::string>(3, RESOURCE_DIR "/StartButton.png");

    m_StartButton = std::make_shared<Button>(
            "StartButton",
            startsPics,
            ""
    );

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
    m_startText->SetPivot({0, 0});

    m_StartButton->AddChild(m_startText); // 文字會跟著按鈕動
    m_StartButton->m_Transform.scale = {1.5f, 1.5f};
    m_StartButton->SetPivot({0, 0}); // 放在畫面下方一點

    m_SelectionMenu = std::make_unique<JobMenu>();

    m_PlaceManager = std::make_unique<MagicPlaceManager>();
    // 範例：點擊任何一個魔法陣，就印出它的位置
    m_PlaceManager->SetOnPlaceClickedCallback([this](std::shared_ptr<MagicPlace> magicPlace) {
        glm::vec2 pos = magicPlace->GetPosition();
        LOG_INFO("MagicPlace at ({}, {}) clicked!", pos.x, pos.y);
        // 顯示職業選單
        m_SelectionMenu->Show(magicPlace);
    });



    m_CurrentState = State::UPDATE;
}