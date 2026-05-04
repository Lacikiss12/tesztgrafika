#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include <obj/model.h>

typedef struct Scene
{
    Model statue;          // Ez volt a 'cube'
    Material material;
    GLuint texture_id;     // A szobor/kocka textúrája
    GLuint floor_texture;  // ÚJ: A padló külön textúrája
    GLuint wall_texture;
    float light_intensity;
    float rotation_angle;
} Scene;

/**
 * Színtér inicializálása.
 */
void init_scene(Scene* scene);

/**
 * Fények beállítása a színtérben.
 */
void set_lighting(const Scene* scene);

/**
 * Anyagjellemzők beállítása.
 */
void set_material(const Material* material);

/**
 * Színtér frissítése (időalapú animáció).
 */
void update_scene(Scene* scene, double delta_time);

/**
 * Színtér kirajzolása.
 */
void render_scene(const Scene* scene);

/**
 * Fényerő módosítása.
 */
void change_light_intensity(Scene* scene, float amount);

/**
 * Koordináta-rendszer origójának kirajzolása.
 */
void draw_origin();

#endif /* SCENE_H */