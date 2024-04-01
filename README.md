# 2D Game Engine

## Overview

This 2D Game Engine is designed as a lightweight, versatile framework for building 2D games. Built on top of SDL2, it provides a simple yet powerful foundation for game development, including rendering, input handling, scene management, and basic physics and collision detection capabilities.

## Getting Started

### Prerequisites

- SDL2 Library
- CMake (Version 3.22 or higher)
- C++ Compiler (C++23 standard support required)

### Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/ecpeter23/2DGameEngine.git
2. Navigate to the cloned directory and create a build directory:
   ```bash
   cd 2DGameEngine
   mkdir build && cd build
3. Run CMake and build the project:
   ```bash
   cmake ..
   make
4. Run the game engine executable:
   ```bash
   ./2DGameEngine
## Roadmap

### Core Development:
- Basic Physics Engine: Implement linear physics equations for simple motion and collisions. Introduce both static and dynamic bodies.
- Advanced Rendering: Enhance rendering capabilities to support camera transformations, including zoom and pan functionalities.
### Scene Management
- Enhanced Scene Transitions: Develop support for smooth scene transitions, such as fades and slides, to improve game flow.
- State Management: Implement a state management system for handling game states (e.g., pause, game over) seamlessly.
### Game Objects and Entities
- Component System: Introduce a component-based system for game objects to easily add and manage behaviors (e.g., physics, animations).
- Animation System: Develop an animation system for sprite-based animations, supporting both frame-based and skeletal animations.
### User Interface
- UI Toolkit: Build a UI toolkit for creating menus, buttons, sliders, and other interactive elements, including support for mouse and keyboard inputs.
- In-game Debugging Tools: Implement in-game debugging tools, such as FPS counters, object inspectors, and performance metrics.
### Input Handling
- Input Mapping: Allow customizable key bindings and support for multiple input devices (e.g., gamepads).
- Gesture and Touch Inputs: Add support for touch and gesture-based inputs for mobile or touch-screen devices.
### Physics and Collision
- Collision Detection and Response: Expand the physics engine to include robust collision detection and response mechanisms for various shapes and bodies.
- Physics Optimizations: Implement spatial partitioning techniques (e.g., QuadTree enhancements) for efficient collision detection in densely populated scenes.
### Utilities and Tools
- Editor Tools: Develop editor tools for level design, asset management, and game configuration to streamline game development processes.
- Scripting Support: Introduce scripting support (e.g., Lua integration) for dynamic game behavior and content creation.
## Contributing

Contributions to the 2D Game Engine are welcome. Whether it's bug reports, feature suggestions, or code contributions, please feel free to reach out or submit a pull request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
