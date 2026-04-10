#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::End() {
    LOG_TRACE("App End");
    // shared_ptr 會自動釋放 m_Background，不需要手動 delete
}