#include "Button.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp" // 必須引入這個才能用 LOG_DEBUG

Button::Button(const std::string& name, const std::string& normalPath,
               const std::string& hoverPath, const std::string& clickPath): m_Name(name)
        {
    m_NormalDrawable = std::make_shared<Util::Image>(normalPath);
    m_HoverDrawable = std::make_shared<Util::Image>(hoverPath);
    m_ClickDrawable = std::make_shared<Util::Image>(clickPath);

    m_Drawable = m_NormalDrawable;
    m_ZIndex = 10.0f;
}

void Button::Update() {
    if (!m_Visible) return;

    bool isHoveringNow = IsMouseHovering();

    // 紀錄：偵測滑鼠進入/離開
    if (isHoveringNow && !m_IsHoveringLastFrame) {
        LOG_DEBUG("[{}] Button '{}': Mouse Enter", __func__, m_Name);
        if (m_OnHover) m_OnHover();
    } else if (!isHoveringNow && m_IsHoveringLastFrame) {
        LOG_DEBUG("[{}] Button '{}': Mouse Leave", __func__, m_Name);
        if (m_OnLeave) m_OnLeave();
    }

    // 2. 狀態機邏輯
    if (isHoveringNow) {
        if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
            LOG_DEBUG("[{}] Button '{}': Mouse LB Down", __func__, m_Name);
            m_CurrentState = State::CLICK;
            m_Drawable = m_ClickDrawable;
        } else {
            // 偵測點擊釋放
            if (m_CurrentState == State::CLICK) {
                LOG_INFO("[{}] Button '{}': Click Triggered!", __func__, m_Name);
                if (m_OnClick) m_OnClick();
            }
            m_CurrentState = State::HOVER;
            m_Drawable = m_HoverDrawable;
        }
    } else {
        m_CurrentState = State::NORMAL;
        m_Drawable = m_NormalDrawable;
    }

    m_IsHoveringLastFrame = isHoveringNow;
}

bool Button::IsMouseHovering() const {
    const auto mousePos = Util::Input::GetCursorPosition();
    const auto size = m_Drawable->GetSize() * m_Transform.scale;
    const auto halfSize = size / 2.0f;
    const auto center = m_Pivot;;

    // 計算邊界
    float left = center.x - halfSize.x;
    float right = center.x + halfSize.x;
    float bottom = center.y - halfSize.y;
    float top = center.y + halfSize.y;

    bool hovering = mousePos.x >= left && mousePos.x <= right &&
                    mousePos.y >= bottom && mousePos.y <= top;

    return hovering;
}