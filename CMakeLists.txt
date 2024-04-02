cmake_minimum_required(VERSION 3.22)
project(2DGameEngine)

set(CMAKE_CXX_STANDARD 23)

# Find SDL2 library using Homebrew path
find_library(SDL2_LIBRARY NAMES SDL2
        HINTS /opt/homebrew/lib
        PATH_SUFFIXES libSDL2.dylib)

# Find SDL2_ttf library using Homebrew path
find_library(SDL2_TTF_LIBRARY NAMES SDL2_ttf
        HINTS /opt/homebrew/lib
        PATH_SUFFIXES libSDL2_ttf.dylib)

add_executable(2DGameEngine main.cpp display/Window.cpp display/Window.h util/datatypes.h util/Thread.cpp util/Thread.h input/InputHandler.cpp input/InputHandler.h display/Display.cpp display/Display.h scene/Scene.cpp scene/Scene.h scene/SceneManager.cpp scene/SceneManager.h object/GameObject.cpp object/GameObject.h util/Camera.cpp util/Camera.h physics/QuadTree.cpp physics/QuadTree.h UI/Button.cpp UI/Button.h UI/TextEngine.cpp UI/TextEngine.h UI/ImageEngine.cpp UI/ImageEngine.h
        scene/SceneBase.h
        assets/scenes/MenuScene.h
        assets/scenes/MenuScene.cpp)

# Include directories for SDL2 and SDL2_ttf using Homebrew paths
target_include_directories(2DGameEngine PRIVATE /opt/homebrew/include/SDL2)

# Link SDL2 and SDL2_ttf libraries
target_link_libraries(2DGameEngine ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY})

target_compile_definitions(${PROJECT_NAME} PRIVATE SOURCE_DIR="${CMAKE_SOURCE_DIR}")