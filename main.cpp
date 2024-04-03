#include <iostream>
#include <SDL.h>
#include "util/Thread.h"
#include "util/datatypes.h"
#include "display/Display.h"
#include "object/GameObject.h"
#include "scene/SceneManager.h"
#include "UI/TextEngine.h"

// Scenes:
#include "assets/scenes/MenuScene.h"

/**
 * TODO:
 * 1. Create a basic physics engine using linear equations and add a static and rigidbody
 * 2. Change the render based on what the camera view is
 *
 */




Display display("2D Game Engine", 800, 600);
SceneManager sceneManager;
//Thread thread;
Thread thread2;
Thread thread3;
SDL_Event event;

void test(){
    display.clear();
    display.render();
    display.present();
}

void test2(){
    std::cout << "Hello World" << std::endl;
}

void test3(u_int32_t i){
    std::cout << "num = " << i << std::endl;
}

//int main() {
//    Scene scene(display.getRenderer(), 1);
//    std::shared_ptr<GameObject> square = GameObject::create("Square", {0, 0}, {100, 100}, GameObject::Type::SQUARE);
//    TextEngine textEngine(display.getRenderer());
//    scene.addGameObject(square);
//    textEngine.renderText("Hello World", 100, 100, 24, {255, 0, 0, 255});
//    sceneManager.loadScene(&scene);
//    //scene.render();
//    //thread.addFunction(test);
//    //thread.addFunction(lambda(display.clear())); // Wrap the method call in a lambda function
//    //thread.addFunction(lambda(scene.render())); // Wrap the method call in a lambda function
//    //thread.addFunction([&] { display.present(); }); // Wrap the method call in a lambda function
//
//    thread2.addFunction(test2);
//    u_int32_t i = 2;
//    thread3.addFunctionWithArgs(test3, i);
//
//    //thread.start(true, 10);
//    //thread2.start(true, 10);
//    //thread3.start();
//    //thread2.wait(10000);
//
//
//    while (!display.isClosed()){
//        display.clear();
//        display.render();
//        display.present();
//
//        while (SDL_PollEvent(&event)) {
//            display.pollEvents(event);
//        }
//    }
//    //std::cout << thread.getID() << "\n";
//    std::cout << thread2.getID() << "\n";
//    std::cout << thread3.getID() << std::endl;
//    thread3.end();
//    thread2.end();
//    //thread.end();
//    return 0;
//}

int main() {
    Display display("2D Game Engine", 800, 600);
    SceneManager sceneManager;

    // Switch to the menu scene
    sceneManager.switchScene(std::make_unique<MenuScene>(display.getRenderer()));

    while (!display.isClosed()) {
        display.clear();

        sceneManager.update();
        sceneManager.render();

        display.present();

        while (SDL_PollEvent(&event)) {
            display.pollEvents(event);
        }
    }

    return 0;
}
