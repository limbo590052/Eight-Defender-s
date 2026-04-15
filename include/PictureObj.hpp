#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <string>
#include <memory>

class PictureObj : public Util::GameObject
{
public:
    /**
     * @param imagePath 背景圖片路徑
     * @param zIndex 背景層級 (預設 -10.0f)
     */
    explicit PictureObj(const std::string &imagePath, float zIndex = -10.0f);

    /**
     * 動態更換圖片
     */
    void SetImage(const std::string &imagePath);

    /**
     * 設定位置
     */
    void SetPosition(const glm::vec2 &position) { m_Transform.translation = position; }

    /**
     * 取得目前位置
     */
    [[nodiscard]] glm::vec2 GetPosition() const { return m_Transform.translation; }

    bool IsVisible(){return m_Visible;};
};

#endif // BACKGROUND_HPP