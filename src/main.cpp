#include "App.hpp"

#include "Core/Context.hpp"

int main(int, char**) {
    auto context = Core::Context::GetInstance();
    App app;

    while (!context->GetExit()) {
        // 1. 準備這一幀的畫布
        context->Setup();

//        ImGui_ImplOpenGL3_NewFrame();
//        ImGui_ImplSDL2_NewFrame();
//        ImGui::NewFrame();

        // 3. 執行遊戲狀態機 (內部會呼叫 app.Update，裡面有你的 ImGui::Begin)
        switch (app.GetCurrentState()) {
            case App::State::INIT:
                app.Init();
                break;

            case App::State::UPDATE:
                app.Update();
                break;

//            case App::State::GAME:
//                app.Update();
//                break;

            case App::State::END:
                app.End();
                context->SetExit(true);
                break;
        }
        // 4. 【核心修復】結束 ImGui 影格並渲染
        ImGui::Render(); // 這行會解決你的 "Forgot to call Render()" 報錯
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // 5. 交換緩衝區，把畫好的東西推到螢幕
        context->Update();
    }
    return 0;
}
