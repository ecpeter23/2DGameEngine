#pragma once

class Camera {
public:
    enum class View{
        TOP_DOWN,
        SIDE,
        THREE_QUARTERS,
        ISOMETRIC
    };

    static void set_position(float x, float y);
    static void get_position(float &x, float &y);

    static void set_zoom(float zoom);
    static float get_zoom(float &zoom);

    static void set_rotation(float rotation);
    static float get_rotation(float &rotation);

    // static void set_view(View view);
    // static float get_view(View &view);

    static void move(float x, float y);
    static void zoom(float z);
    static void rotate(float r);

private:
    static float x;
    static float y;
    static float z;
    static float rotation;
    static View view;
};
