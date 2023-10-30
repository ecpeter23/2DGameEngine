#include <iostream>
#include <SDL.h>
#include <unistd.h>
#include "util/Thread.h"
#include "util/datatypes.h"
#include "display/Display.h"
#include "object/GameObject.h"
#include "scene/Scene.h"

/**
 * TODO:
 * 1. Create a basic physics engine using linear equations and add a static and rigidbody
 * 2. Change the render based on what the camera view is
 *
 */




Display display("2D Game Engine", 800, 600);
Thread thread;
SDL_Event event;

void test(){
    display.clear();
    display.render();
    display.present();
}

int main() {
    Scene scene(display.getRenderer(), 1);
    std::shared_ptr<GameObject> square = GameObject::create("Square", {0, 0}, {100, 100}, GameObject::Type::SQUARE);
    scene.addGameObject(square);
    thread.addFunction(lambda(display.clear())); // Wrap the method call in a lambda function
    thread.addFunction([&] { display.render(); }); // Wrap the method call in a lambda function
    thread.addFunction([&] { display.present(); }); // Wrap the method call in a lambda function
    thread.start(true, 10);


    while (!display.isClosed()){
        while (SDL_PollEvent(&event)) {
            display.pollEvents(event);
        }
    }

    thread.end();
    return 0;
}
