#include "scene.h"
#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene) {
    // Tanári elvárás: relatív elérési utak
    load_model(&(scene->statue), "assets/models/cube.obj"); 
    scene->texture_id = load_texture("assets/textures/cube.png");
    scene->light_intensity = 0.8f;
    scene->rotation_angle = 0.0f;
}

void set_lighting(const Scene* scene) {
    float ambient = scene->light_intensity * 0.2f;
    float diffuse = scene->light_intensity;
    float light_ambient[] = { ambient, ambient, ambient, 1.0f };
    float light_diffuse[] = { diffuse, diffuse, diffuse, 1.0f };
    float light_pos[] = { 0.0f, 0.0f, 5.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void change_light_intensity(Scene* scene, float amount) {
    scene->light_intensity += amount;
    if (scene->light_intensity > 1.0f) scene->light_intensity = 1.0f;
    if (scene->light_intensity < 0.0f) scene->light_intensity = 0.0f;
}

void update_scene(Scene* scene, double delta_time) {
    // Időalapú forgatás: 30 fok másodpercenként
    scene->rotation_angle += 30.0f * (float)delta_time;
}

void render_scene(const Scene* scene) {
    glBindTexture(GL_TEXTURE_2D, scene->texture_id);
    
    glPushMatrix();
    glRotatef(scene->rotation_angle, 0, 0, 1);
    draw_model(&(scene->statue));
    glPopMatrix();
}