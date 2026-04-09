#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include <functional>
#include <memory>

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Button : public Util::GameObject {
public:
    // 狀態定義
    enum class State {
        NORMAL,
        HOVER,
        CLICK
    };

    /**
     * 建構子：傳入三種狀態的圖片路徑
     */
    Button(const std::string& name, const std::string& normal,
           const std::string& hover, const std::string& click);

    void Update();

    // 事件設定
    void SetOnClick(std::function<void()> callback) { m_OnClick = std::move(callback); }
    void SetOnHover(std::function<void()> callback) { m_OnHover = std::move(callback); }
    void SetOnLeave(std::function<void()> callback) { m_OnLeave = std::move(callback); }

private:
    /**
     * 檢查滑鼠是否在按鈕矩形範圍內
     */
    bool IsMouseHovering() const;

private:
    std::string m_Name;
    // 圖片資源
    std::shared_ptr<Util::Image> m_NormalDrawable;
    std::shared_ptr<Util::Image> m_HoverDrawable;
    std::shared_ptr<Util::Image> m_ClickDrawable;

    // 狀態紀錄
    State m_CurrentState = State::NORMAL;
    bool m_IsHoveringLastFrame = false;

    // 回呼函式 (Callbacks)
    std::function<void()> m_OnClick;
    std::function<void()> m_OnHover;
    std::function<void()> m_OnLeave;
};

#endif // BUTTON_HPP