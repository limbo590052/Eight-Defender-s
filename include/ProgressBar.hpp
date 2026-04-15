#ifndef PROGRESS_BAR_HPP
#define PROGRESS_BAR_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <memory>
#include <string>

class ProgressBar : public Util::GameObject {
public:
    /**
     * @param bgPath 背景底框圖片路徑
     * @param fillPath 填充進度圖片路徑
     */
    ProgressBar(const std::string& bgPath, const std::string& fillPath, glm::vec2 pos);

    void SetProgress(float ratio);
    void Draw();
    float GetProgress() const { return m_Progress; }

private:
    std::shared_ptr<Util::GameObject> m_Background; // 底框
    std::shared_ptr<Util::GameObject> m_Fill;       // 填充條

    float m_Progress = 0.0f;
};

#endif