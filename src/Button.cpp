#include "Button.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp" // 必須引入這個才能用 LOG_DEBUG
#include <optional>

// 基礎版本：委託給完整版本
Button::Button(const std::string &name, const std::vector<std::string> &baseLayers)
    : Button(name, baseLayers, std::nullopt)
{
}

// 2. 完整建構子：處理所有初始化邏輯
Button::Button(const std::string &name,
               const std::vector<std::string> &baseLayers,
               const std::optional<std::string> overlay)
    : m_Name(name)
{

    // 放入基礎三狀態圖層
    for (const auto &path : baseLayers)
    {
        m_BaseLayers.push_back(std::make_shared<Util::Image>(path));
    }

    // 防錯：確保至少有底圖，避免 m_BaseLayers[0] 崩潰
    if (m_BaseLayers.empty())
    {
        LOG_ERROR("Button '{}' initialized with empty baseLayers!", m_Name);
    }
    else
    {
        m_Drawable = m_BaseLayers[0];
    }

    // 處理疊加層 (如果有提供值)
    if (overlay.has_value() && !overlay.value().empty())
    {
        m_Overlay = std::make_shared<Util::Image>(overlay.value());
    }

    // 預設層級
    m_ZIndex = 10.0f;
}

void Button::Update()
{
    if (!m_Visible)
        return;

    bool isHoveringNow = IsMouseHovering();

    // 紀錄：偵測滑鼠進入/離開
    if (isHoveringNow && !m_IsHoveringLastFrame)
    {
        LOG_DEBUG("[{}] Button '{}': Mouse Enter", __func__, m_Name);
        if (m_OnHover)
            m_OnHover();
    }
    else if (!isHoveringNow && m_IsHoveringLastFrame)
    {
        LOG_DEBUG("[{}] Button '{}': Mouse Leave", __func__, m_Name);
        if (m_OnLeave)
            m_OnLeave();
    }

    // 2. 狀態機邏輯
    if (isHoveringNow)
    {
        if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB))
        {
            LOG_DEBUG("[{}] Button '{}': Mouse LB Down", __func__, m_Name);
            m_CurrentState = State::CLICK;
            m_Drawable = m_BaseLayers[2];
        }
        else
        {
            // 偵測點擊釋放
            if (m_CurrentState == State::CLICK)
            {
                LOG_INFO("[{}] Button '{}': Click Triggered!", __func__, m_Name);
                if (m_OnClick)
                    m_OnClick();
            }
            m_CurrentState = State::HOVER;
            m_Drawable = m_BaseLayers[1];
        }
    }
    else
    {
        m_CurrentState = State::NORMAL;
        m_Drawable = m_BaseLayers[0];
    }

    m_IsHoveringLastFrame = isHoveringNow;
}

bool Button::IsMouseHovering() const
{
    const auto mousePos = Util::Input::GetCursorPosition();
    const auto size = m_Drawable->GetSize() * m_Transform.scale;
    const auto halfSize = size / 2.0f;
    const auto center = m_Transform.translation;

    // X 軸通常是正常的
    float left = center.x - halfSize.x;
    float right = center.x + halfSize.x;

    // 關鍵修正：將 mousePos.y 加上負號，或者反轉中心點的判定
    // 因為框架目前的 mousePos.y 越往下越正，這跟一般邏輯相反
    float invertedMouseY = -mousePos.y;

    float bottom = center.y - halfSize.y;
    float top = center.y + halfSize.y;

    bool hovering = (mousePos.x >= left && mousePos.x <= right) &&
                    (invertedMouseY >= bottom && invertedMouseY <= top);

    return hovering;
}