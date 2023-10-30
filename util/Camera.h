#pragma once

#include "datatypes.h"

class Camera {
public:
    enum class View{
        TOP_DOWN,
        SIDE,
        THREE_QUARTERS,
        ISOMETRIC
    };

    static void set_position(f32 x, f32 y);
    static void get_position(f32 &x, f32 &y);

    static void set_zoom(f32 zoom);
    static void get_zoom(f32 &zoom);

    static void set_rotation(f32 rotation);
    static void get_rotation(f32 &rotation);

    // static void set_view(View view);
    // static float get_view(View &view);

    static void move(f32 x, f32 y);
    static void zoom(f32 z);
    static void rotate(f32 r);

private:
    static f32 x;
    static f32 y;
    static f32 z;
    static f32 rotation;
    static View view;
};