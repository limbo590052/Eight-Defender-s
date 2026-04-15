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

#define MAKE_BUTTON(var, normal, hover, click) \
    var = std::make_shared<Button>(#var, normal, hover, click)

class App
{
public:
    enum class State
    {
        START,
        UPDATE,
        END,
        // PREPARE,
        // DEPLOY,
        // COMBAT,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    State m_CurrentState = State::START;

    // 剛才報錯缺少的變數都在這裡定義
    std::shared_ptr<PictureObj> m_Background;
    std::shared_ptr<Button> m_StartButton;
    std::shared_ptr<PictureObj> m_startText;

    int m_BaseHp = 10;
    int m_Gold = 0;
    int m_Exp = 0;
    std::vector<std::shared_ptr<GameUnit>> m_Enemies;
    std::vector<glm::vec2> Waypoints = {{0, 0}, {100, 0}}; // 路徑點
    std::unique_ptr<MagicPlaceManager> m_PlaceManager;
    std::unique_ptr<JobMenu> m_JobMenu;
    int m_RestLimitCommon = 10; // 預設值
    int m_RestLimitSpecial = 10;
};

#endif
