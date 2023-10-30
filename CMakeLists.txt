cmake_minimum_required(VERSION 3.22)
project(2DGameEngine)

set(CMAKE_CXX_STANDARD 23)
find_library(SDL2_LIBRARY NAMES SDL2
        HINTS /Users/elipeter/Library/Frameworks
        PATH_SUFFIXES SDL2.framework)

add_executable(2DGameEngine main.cpp display/Window.cpp display/Window.h util/datatypes.h util/Thread.cpp util/Thread.h input/InputHandler.cpp input/InputHandler.h display/Display.cpp display/Display.h scene/Scene.cpp scene/Scene.h scene/SceneManager.cpp scene/SceneManager.h object/GameObject.cpp object/GameObject.h util/Camera.cpp util/Camera.h physics/QuadTree.cpp physics/QuadTree.h UI/Button.cpp UI/Button.h UI/TextEngine.cpp UI/TextEngine.h UI/ImageEngine.cpp UI/ImageEngine.h
)

target_include_directories(2DGameEngine PRIVATE /Users/elipeter/Library/Frameworks/SDL2.framework/Headers)
target_link_libraries(2DGameEngine ${SDL2_LIBRARY})

target_compile_definitions(${PROJECT_NAME} PRIVATE SOURCE_DIR="${CMAKE_SOURCE_DIR}")