//
// Created by limbo on 2026/3/13.
//

#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_BACKGROUND_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_BACKGROUND_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Background : public Util::GameObject {
public:
    explicit Background(const std::string& imagePath) {
        this->SetDrawable(std::make_shared<Util::Image>(imagePath));
        this->m_Transform.translation = {0, 0};
    }
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_BACKGROUND_HPP
