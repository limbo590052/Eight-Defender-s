#ifndef LEVEL_PREVIEW_UI_HPP
#define LEVEL_PREVIEW_UI_HPP

#include "PictureObj.hpp" // 假設你之前的 PictureObj 已經有 SetImage 功能
#include "Util/GameObject.hpp"
#include <string>
#include <vector>

class LevelInfoUI : public Util::GameObject {
public:
    LevelInfoUI();
    void Draw();
    bool IsVisible();
    // 核心功能：一鍵切換關卡內容
    void SetLevel(int stage, const std::string& type, int speed);

private:
    // Panel 層 (Base 最下, Top 中, TypeText 最上)
    std::vector<std::shared_ptr<PictureObj>> m_PanelBase;
    std::vector<std::shared_ptr<PictureObj>> m_PanelTop;
    std::vector<std::shared_ptr<PictureObj>> m_Type;
    std::shared_ptr<PictureObj> m_TypeText;

    // 速度層 (Panel 下, Num 上)
    std::shared_ptr<PictureObj> m_SpeedPanel;
    std::vector<std::shared_ptr<PictureObj>> m_SpeedNum;

    // 標題層 (STAGE 下, 1-25關 上)
    std::shared_ptr<PictureObj> m_StageTitle;
    std::vector<std::shared_ptr<PictureObj>> m_StageNum;
};

#endif