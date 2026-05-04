#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "scene.h"
#include "model.h"
#include <GL/gl.h>
#include <obj/draw.h>

// Környezeti elemek kirajzolása (padló, falak, plafon)
void draw_environment(const Scene* scene);

// Összes festmény kirajzolása
void draw_paintings(const Scene* scene);

void draw_statue_group(const Scene* scene);

void draw_vitrine(const Scene* scene);

#endif