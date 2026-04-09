#include "PictureObj.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"

PictureObj::PictureObj(const std::string& path, float zIndex) {
    LOG_DEBUG("Attempting to load pic: {}", path);

    m_Drawable = std::make_shared<Util::Image>(path);

    // 檢查圖片是否載入成功 (如果失敗，Util::Image 通常會換成 MissingTexture)
    if (m_Drawable == nullptr) {
        LOG_ERROR("Drawable creation failed for path: {}", path);
    }

    SetZIndex(zIndex);
    m_Transform.translation = {0.0f, 0.0f};
    // 確保 Scale 不是 0
    m_Transform.scale = {1.0f, 1.0f};
}