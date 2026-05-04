#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "scene.h"
#include <obj/model.h>
#include <obj/draw.h>
#include <GL/gl.h>

/* Környezeti elemek kirajzolása (padló, falak, plafon) */
void draw_environment(const Scene* scene);

/* Összes festmény kirajzolása kerettel */
void draw_paintings(const Scene* scene);

/* Egy szoborcsoport kirajzolása (pillér + forgó szobor + vitrin) */
void draw_statue_group(const Scene* scene, const Model* current_model, GLuint current_texture);

/* Áttetsző üvegvitrin rajzolása */
void draw_vitrine(const Scene* scene);

/* Festmény keret rajzolása */
void draw_painting_frame(float x0, float y0, float z0,
                         float x1, float y1, float z1,
                         float nx, float ny, float nz);

#endif
