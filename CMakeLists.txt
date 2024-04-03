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

find_package(OpenSSL REQUIRED)

# Instead of find_package for Box2D, directly set the include directory and library file
set(BOX2D_INCLUDE_DIR /opt/homebrew/Cellar/box2d/2.4.1/include)
set(BOX2D_LIBRARY /opt/homebrew/Cellar/box2d/2.4.1/lib/libbox2d.a)

add_executable(2DGameEngine main.cpp display/Window.cpp display/Window.h util/datatypes.h util/Thread.cpp util/Thread.h input/InputHandler.cpp input/InputHandler.h display/Display.cpp display/Display.h scene/SceneManager.cpp scene/SceneManager.h object/GameObject.h object/GameObject.cpp util/Camera.cpp util/Camera.h physics/QuadTree.cpp physics/QuadTree.h UI/Button.cpp UI/Button.h UI/TextEngine.cpp UI/TextEngine.h UI/ImageEngine.cpp UI/ImageEngine.h
        scene/SceneBase.h
        assets/scenes/MenuScene.h
        assets/scenes/MenuScene.cpp
        util/VerifiableRandom.h
        object/Component.h
        object/TransformComponent.h
        util/ResourceManager.h
        util/EventManager.h
        object/AnimationComponent.h
        object/PhysicsComponent.h
        assets/scenes/DebugScene.cpp
        assets/scenes/DebugScene.h
)

# Include directories for SDL2, SDL2_ttf, OpenSSL, and Box2D using Homebrew paths
target_include_directories(2DGameEngine PRIVATE /opt/homebrew/include/SDL2 ${OPENSSL_INCLUDE_DIR} ${BOX2D_INCLUDE_DIR})

# Link SDL2, SDL2_ttf, OpenSSL, and Box2D libraries
target_link_libraries(2DGameEngine ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY} ${OPENSSL_LIBRARIES} ${BOX2D_LIBRARY})

target_compile_definitions(${PROJECT_NAME} PRIVATE SOURCE_DIR="${CMAKE_SOURCE_DIR}")