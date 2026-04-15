#ifndef SELECTION_MENU_HPP
#define SELECTION_MENU_HPP

#include <vector>
#include <string>
#include <map>
#include <memory>
#include "Button.hpp"
#include "MagicPlace.hpp"

struct JobNode {
    std::string currentJob;
    std::vector<std::string> branches;
};

class JobMenu {
public:
    JobMenu();
    void Update();
    void Draw();

    // 雖然名稱叫 ShowAt，但內部位置是固定的
    void Show(std::shared_ptr<MagicPlace> owner);
    void Hide();
    bool IsVisible() const { return m_Visible; }
    // 定義一個函式型態：接收職業名稱與在哪個魔法陣生成
    using OnJobSelectedCallback = std::function<void(const std::string&, std::shared_ptr<MagicPlace>)>;
    void SetOnJobSelectedCallback(OnJobSelectedCallback callback) { m_OnJobSelected = callback; }

private:
    void RefreshMenu(const std::string& jobKey);

    bool m_Visible = false;
    std::vector<std::shared_ptr<Button>> m_ActiveButtons;
    std::shared_ptr<MagicPlace> m_CurrentOwner; // 紀錄是哪個魔法陣開的
    OnJobSelectedCallback m_OnJobSelected;

    // 固定座標設定 (例如畫面中心下方)
    const glm::vec2 MENU_CENTER_POS = {0, -60};
    std::map<std::string, std::vector<std::string>> m_JobTree;
};
#endif