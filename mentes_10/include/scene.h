#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include <obj/model.h>

typedef struct {
    float x, y;
} StatuePosition;

typedef struct Scene
{
    Model statue;
    Model cube;
    Model round;            // Ez volt a 'cube'
    Material material;
    GLuint round_table;
    GLuint cube_texture; 
    GLuint statue_texture;
    GLuint floor_texture;  // ÚJ: A padló külön textúrája
    GLuint wall_texture;
    GLuint ceiling_texture; // ÚJ: A mennyezet textúrája
    GLuint painting_texture;
    GLuint painting_texture2;
    GLuint painting_texture3;
    GLuint painting_texture4;
    GLuint painting_texture5;
    GLuint painting_texture6;
    GLuint painting_texture7;
    GLuint painting_texture8;
    GLuint painting_texture9;
    GLuint painting_texture10;
    GLuint painting_texture11;
    GLuint painting_texture12;
    GLuint painting_texture13;
    GLuint painting_texture14;
    GLuint painting_texture15;
    GLuint painting_texture16;
    GLuint painting_texture17;
    GLuint painting_texture18;
    GLuint painting_texture19;
    GLuint painting_texture20;
    float light_intensity;
    float rotation_angle;
    StatuePosition statues[20];
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