#include "camera.h"
#include <GL/gl.h>
#include <math.h>

void init_camera(Camera* camera) {
    camera->position.x = 0.0f;
    camera->position.y = -5.0f; // Hátrébb visszük a kezdőpontot
    camera->position.z = 1.0f;
    camera->rotation.x = 0.0f;
    camera->rotation.z = 0.0f;
    camera->speed.x = 0.0f;
    camera->speed.y = 0.0f;
}

void update_camera(Camera* camera, double time) {
    double angle = degree_to_radian(camera->rotation.z);
    double side_angle = degree_to_radian(camera->rotation.z + 90.0);

    // Időalapú mozgás számítása
    camera->position.x += cos(angle) * camera->speed.y * time;
    camera->position.y += sin(angle) * camera->speed.y * time;
    camera->position.x += cos(side_angle) * camera->speed.x * time;
    camera->position.y += sin(side_angle) * camera->speed.x * time;

    // Példa egyszerű korlátozásra
    if (camera->position.x < -19.0f) camera->position.x = -19.0f;
    if (camera->position.x >  19.0f) camera->position.x =  19.0f;
    if (camera->position.y < -19.0f) camera->position.y = -19.0f;
    if (camera->position.y >  19.0f) camera->position.y =  19.0f;
}

void set_view(const Camera* camera) {
    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical) {
    camera->rotation.z += horizontal * 0.2; // Érzékenység beállítása
    camera->rotation.x += vertical * 0.2;
}

void set_camera_speed(Camera* camera, double speed) { camera->speed.y = speed; }
void set_camera_side_speed(Camera* camera, double speed) { camera->speed.x = speed; }