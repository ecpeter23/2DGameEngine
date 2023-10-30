#include "Camera.h"


f32 Camera::x = 0.0f;
f32 Camera::y = 0.0f;
f32 Camera::z = 1.0f;
f32 Camera::rotation = 0.0f;

void Camera::set_position(f32 x, f32 y) {
    Camera::x = x;
    Camera::y = y;
}

void Camera::get_position(f32 &x, f32 &y) {
    x = Camera::x;
    y = Camera::y;
}

void Camera::set_zoom(f32 zoom) {
    Camera::z = zoom;
}

void Camera::get_zoom(f32 &zoom) {
    zoom = Camera::z;
}

void Camera::set_rotation(f32 rotation) {
    Camera::rotation = rotation;
}

void Camera::get_rotation(f32 &rotation) {
    rotation = Camera::rotation;
}

void Camera::move(f32 dx, f32 dy) {
    Camera::x += dx;
    Camera::y += dy;
}

void Camera::zoom(f32 dz) {
    Camera::z += dz;
}

void Camera::rotate(f32 dr) {
    Camera::rotation += dr;
}

/*float Camera::get_view(View &view) {
    view = Camera::view;
}

void Camera::set_view(View view) {
    Camera::view = view;
}*/