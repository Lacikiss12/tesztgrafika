#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include <obj/model.h>

#define STATUE_COUNT 20
#define PAINTING_COUNT 20

typedef struct {
    float x, y;
} StatuePosition;

typedef struct Scene
{
    Model statue;
    Model cube;
    Model round;
    Material material;

    GLuint round_table;
    GLuint cube_texture;
    GLuint statue_texture;
    GLuint floor_texture;
    GLuint wall_texture;
    GLuint ceiling_texture;

    /* Festmények tömbként – sokkal karbantarthatóbb */
    GLuint painting_textures[PAINTING_COUNT];

    GLuint help_texture;

    float light_intensity;
    float fog_density;       /* G/H billentyűvel állítható ködsűrűség */
    float rotation_angle;

    StatuePosition statues[STATUE_COUNT];
} Scene;

void init_scene(Scene* scene);
void set_lighting(const Scene* scene);
void set_material(const Material* material);
void update_scene(Scene* scene, double delta_time);
void render_scene(const Scene* scene);
void change_light_intensity(Scene* scene, float amount);
void change_fog_density(Scene* scene, float amount);
void draw_origin();

#endif /* SCENE_H */
