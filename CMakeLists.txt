cmake_minimum_required(VERSION 3.16)
project(EightDefenders)

set(CMAKE_CXX_STANDARD 17)
cmake_policy(SET CMP0135 NEW)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

# 自動下載 PTSD 框架
FetchContent_Declare(
        ptsd
        URL         https://github.com/ntut-open-source-club/practical-tools-for-simple-design/archive/refs/tags/v0.3-rc1.zip
        SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/PTSD
)
FetchContent_MakeAvailable(ptsd)

# 設定路徑變數
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/include)

# 加入所有你要編譯的 .cpp
add_executable(${PROJECT_NAME}
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/PictureObj.cpp
        ${SRC_DIR}/Button.cpp
        ${SRC_DIR}/GameUnit.cpp
        ${SRC_DIR}/MagicPlace.cpp
        include/MagicPlace.hpp
        include/MagicPlaceManager.hpp
        ${SRC_DIR}/MagicPlaceManager.cpp
        ${SRC_DIR}/AppStart.cpp
        ${SRC_DIR}/AppUpdate.cpp
        ${SRC_DIR}/AppEnd.cpp
        src/JobMenu.cpp
        include/JobMenu.hpp
        src/Hero.cpp
        include/Hero.hpp
        src/JobDatabase.cpp
        include/JobDatabase.hpp
        include/JobDefine.hpp
)

# 關鍵：這行會讓編譯器去 include 資料夾找你的 App.hpp, GameUnit.hpp 等等
target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIR})

# 這些是 PTSD 框架必要的搜尋路徑
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/PTSD/include
        ${CMAKE_CURRENT_SOURCE_DIR}/PTSD/include/Util
        ${CMAKE_CURRENT_SOURCE_DIR}/PTSD/lib/include
        ${CMAKE_CURRENT_SOURCE_DIR}/PTSD/lib/glew/include
        ${CMAKE_CURRENT_SOURCE_DIR}/PTSD/lib/spdlog/include
        ${CMAKE_CURRENT_SOURCE_DIR}/PTSD/lib/sdl2/include
        ${CMAKE_CURRENT_SOURCE_DIR}/PTSD/lib/glm
        ${CMAKE_CURRENT_SOURCE_DIR}/PTSD/lib/imgui
)

# 編譯選項
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

# 設定資源路徑
target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Resources")

# 連結庫
target_link_libraries(${PROJECT_NAME}
        PRIVATE PTSD
        PRIVATE SDL2::SDL2      # 加上這行
        PRIVATE SDL2::SDL2main  # 確保這行存在
        -mconsole               # 絕招：強制指定為 Console 模式，可以避開 WinMain 檢查
)