#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "PictureObj.hpp"
#include "Button.hpp"
#include "GameUnit.hpp"
#include "Position.hpp"
#include "Input.hpp"
#include "MagicPlaceManager.hpp"
#include "JobMenu.hpp"
#include "Hero.hpp"
#include "Text.hpp"
#include "ResourceManager.hpp"
#include "LevelInfoUI.hpp"

#define MAKE_BUTTON(var, normal, hover, click) \
    var = std::make_shared<Button>(#var, normal, hover, click)

class App
{
public:
    enum class State
    {
        INIT,
        UPDATE,
        END,
        // PREPARE,
        // DEPLOY,
        // COMBAT,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Init();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    State m_CurrentState = State::INIT;

    // 剛才報錯缺少的變數都在這裡定義
    std::shared_ptr<PictureObj> m_Background;
    std::shared_ptr<Button> m_StartButton;
    std::shared_ptr<PictureObj> m_startText;

    int m_BaseHp = 10;

    std::unique_ptr<LevelInfoUI> m_LevelInfoUI;
    std::unique_ptr<ResourceManager> m_Resources;
    std::vector<std::shared_ptr<GameUnit>> m_Enemies;
    std::vector<std::shared_ptr<Hero>> m_Heroes;
    std::vector<glm::vec2> Waypoints = {{0, 0}, {100, 0}}; // 路徑點
    std::unique_ptr<MagicPlaceManager> m_PlaceManager;
    std::unique_ptr<JobMenu> m_JobMenu;
    int m_RestLimitCommon = 10; // 預設值
    int m_RestLimitSpecial = 10;
};

#endif
