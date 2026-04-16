#include "App.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Hero.hpp"

void App::Init()
{
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
        "");

    m_StartButton->SetOnClick([this]() {
        LOG_INFO("Game Start!");

        // 1. 隱藏開始按鈕與文字
        m_StartButton->SetVisible(false);
        m_startText->SetVisible(false);

        // 2. 設定預覽資訊
        m_LevelInfoUI->SetLevel(1, "Normal", 3);
        m_LevelInfoUI->SetVisible(true);

        m_PlaceManager->SetAllVisible(true);
    });

    // 加入文字圖片作為子物件
    m_startText = std::make_shared<PictureObj>(RESOURCE_DIR "/StartText.png");
    m_startText->SetZIndex(m_StartButton->GetZIndex() + 0.1f);
    m_startText->m_Transform.scale = {0.75f, 0.75f};
    m_startText->SetPivot({0, 0});

    m_StartButton->AddChild(m_startText); // 文字會跟著按鈕動
    m_StartButton->m_Transform.scale = {3.0f, 3.0f};
    m_StartButton->SetPivot({0, 0}); // 放在畫面下方一點

    m_JobMenu = std::make_unique<JobMenu>();
    m_PlaceManager = std::make_unique<MagicPlaceManager>();

    m_LevelInfoUI = std::make_unique<LevelInfoUI>();
    m_LevelInfoUI->SetVisible(false);
    m_LevelInfoUI->m_Transform.translation = {0, 0};

    // 綁定
    m_PlaceManager->SetOnPlaceClickedCallback([this](std::shared_ptr<MagicPlace> clickedPlace)
                                              {
        glm::vec2 pos = clickedPlace->GetPosition();
        LOG_INFO("MagicPlace at ({}, {}) clicked!", pos.x, pos.y);
        // 顯示職業選單
        m_JobMenu->Show(clickedPlace); });

    m_JobMenu->SetOnJobSelectedCallback([this](const std::string &jobName, std::shared_ptr<MagicPlace> place)
                                        {
        // 1. 取得生成位置 (MagicPlace 的位置)
        glm::vec2 spawnPos = place->GetPosition();

        // 2. 生成英雄物件 (假設你的 Hero 建構子接收職業名與位置)
        auto newHero = std::make_shared<Hero>(jobName, spawnPos);

        // 3. 加入到 App 管理的 Hero 向量中
        m_Heroes.push_back(newHero);
        LOG_DEBUG("Spawned {} at ({}, {})", jobName, spawnPos.x, spawnPos.y);

        if (m_Heroes.size() == 8) {
            LOG_INFO("Hero limit reached (8). Hiding all MagicPlaces.");

            m_PlaceManager->SetAllVisible(false);
        } });

    m_Resources = std::make_unique<ResourceManager>(0, 0);
    m_CurrentState = State::UPDATE;
}