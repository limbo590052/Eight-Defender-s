#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include <functional>
#include <memory>

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <optional>

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
    //baseLayers = {normal, hover, click}
    Button(const std::string& name, const std::vector<std::string>& baseLayers);
    Button(const std::string& name,
           const std::vector<std::string>& baseLayers,
           std::optional<std::string> overlay);

    void Update();

    // 添加新的疊加層
    void AddOverlay(const std::string& path);
    // 重設，只保留底圖與初始 path
    void ResetLayers();

    // 事件設定
    void SetOnClick(std::function<void()> callback) { m_OnClick = std::move(callback); }
    void SetOnHover(std::function<void()> callback) { m_OnHover = std::move(callback); }
    void SetOnLeave(std::function<void()> callback) { m_OnLeave = std::move(callback); }

    /**
     * 檢查滑鼠是否在按鈕矩形範圍內
     */
    bool IsMouseHovering() const;
    bool IsVisible() const { return m_Visible; }

private:
    std::string m_Name;
    std::vector<std::shared_ptr<Util::Image>> m_BaseLayers; // 存放三態底圖
    std::shared_ptr<Util::Image> m_Overlay = nullptr;      // 疊加層 (如職業圖)

    State m_CurrentState = State::NORMAL;
    bool m_IsHoveringLastFrame = false;

    // 回呼函式 (Callbacks)
    std::function<void()> m_OnClick;
    std::function<void()> m_OnHover;
    std::function<void()> m_OnLeave;
};

#endif // BUTTON_HPP