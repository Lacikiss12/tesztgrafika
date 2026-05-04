#include "camera.h"
#include <GL/gl.h>
#include <math.h>
#include "scene.h"

void init_camera(Camera* camera) {
    camera->position.x = 0.0f;
    camera->position.y = -5.0f; // Hátrébb visszük a kezdőpontot
    camera->position.z = 1.0f;
    camera->rotation.x = 0.0f;
    camera->rotation.z = 0.0f;
    camera->speed.x = 0.0f;
    camera->speed.y = 0.0f;
}

int is_colliding_with_statue(float x, float y, const Scene* scene) {
    float collisionDist = 0.8f; // Pillér sugara + kamera tere

    for (int i = 0; i < 20; i++) {
        float dx = x - scene->statues[i].x;
        float dy = y - scene->statues[i].y;
        float distance = sqrtf(dx * dx + dy * dy);

        if (distance < collisionDist) {
            return 1; // Ütközés!
        }
    }
    return 0; // Tiszta út
}

void update_camera(Camera* camera, const Scene* scene, double time) {
    double angle = degree_to_radian(camera->rotation.z);
    double side_angle = degree_to_radian(camera->rotation.z + 90.0);

    // 1. Kiszámoljuk, hová szeretne lépni a játékos
    float nextX = camera->position.x;
    float nextY = camera->position.y;

    nextX += cos(angle) * camera->speed.y * time;
    nextY += sin(angle) * camera->speed.y * time;
    nextX += cos(side_angle) * camera->speed.x * time;
    nextY += sin(side_angle) * camera->speed.x * time;

    // 2. ELLENŐRZÉS: Csak akkor lépünk, ha nem ütközik szoborral
    if (!is_colliding_with_statue(nextX, nextY, scene)) {
        camera->position.x = nextX;
        camera->position.y = nextY;
    }

    // 3. Falak korlátozása (ez maradhat a végén, hogy ne sétáljunk ki)
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