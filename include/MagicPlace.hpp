#ifndef MAGIC_PLACE_HPP
#define MAGIC_PLACE_HPP

#include <memory>
#include <string>
#include "Button.hpp" // 必須包含，因為我們組合了 Button

class MagicPlace {
public:
    MagicPlace(const std::string& name, glm::vec2 pos);

    void Update();
    void Draw();

    // 提供給 Manager 與 Menu 使用的介面
    void SetVisible(bool visible);
    void SetOnClick(const std::function<void()>& callback);

    // 狀態設定：當被佔用時，魔法陣會消失且無法再被點擊
    void SetOccupied(bool occupied);
    bool IsOccupied() const { return m_IsOccupied; }

    // 取得位置（選單彈出時需要知道座標）
    [[nodiscard]] glm::vec2 GetPosition() const { return m_Object->GetTransform().translation; }
    std::string GetName() const { return m_Name; }

private:
    std::shared_ptr<Button> m_Object;
    std::string m_Name;

    glm::vec2 m_NormalScale = {1.0f, 1.0f};
    glm::vec2 m_HoverScale = {2.0f, 2.0f};
    float m_LerpFactor = 0.15f; // 抽出來方便微調
    bool m_IsOccupied = false;
};

#endif