#include "Camera.h"


float Camera::x = 0.0f;
float Camera::y = 0.0f;
float Camera::z = 1.0f;
float Camera::rotation = 0.0f;

void Camera::set_position(float x, float y) {
    Camera::x = x;
    Camera::y = y;
}

void Camera::get_position(float &x, float &y) {
    x = Camera::x;
    y = Camera::y;
}

void Camera::set_zoom(float zoom) {
    Camera::z = zoom;
}

float Camera::get_zoom(float &zoom) {
    zoom = Camera::z;
}

void Camera::set_rotation(float rotation) {
    Camera::rotation = rotation;
}

float Camera::get_rotation(float &rotation) {
    rotation = Camera::rotation;
}

void Camera::move(float dx, float dy) {
    Camera::x += dx;
    Camera::y += dy;
}

void Camera::zoom(float dz) {
    Camera::z += dz;
}

void Camera::rotate(float dr) {
    Camera::rotation += dr;
}

/*float Camera::get_view(View &view) {
    view = Camera::view;
}

void Camera::set_view(View view) {
    Camera::view = view;
}*/
