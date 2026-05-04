#include "scene.h"
#include <obj/load.h>
#include <obj/draw.h>
#include <stdio.h>
#include <environment.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>

/* Festményfájlok listája – könnyen bővíthető */
static const char* PAINTING_FILES[PAINTING_COUNT] = {
    "assets/textures/mona_lisa.jpg",
    "assets/textures/danika.jpg",
    "assets/textures/meme3.jpg",
    "assets/textures/meme4.jpg",
    "assets/textures/meme5.jpg",
    "assets/textures/meme6.jpg",
    "assets/textures/meme7.jpg",
    "assets/textures/meme8.jpg",
    "assets/textures/meme9.jpg",
    "assets/textures/meme10.jpg",
    "assets/textures/meme11.jpg",
    "assets/textures/meme12.jpg",
    "assets/textures/meme13.jpg",
    "assets/textures/meme14.jpg",
    "assets/textures/meme15.jpg",
    "assets/textures/meme16.jpg",
    "assets/textures/meme17.jpg",
    "assets/textures/meme18.jpg",
    "assets/textures/meme19.jpg",
    "assets/textures/meme20.jpg"
};

void init_scene(Scene* scene)
{
    srand((unsigned int)time(NULL));

    /* --- Szobor pozíciók véletlen generálása (min. 3 m távolság) --- */
    int count = 0;
    float roomSize = 15.0f;
    while (count < STATUE_COUNT) {
        float posX = ((float)rand() / (float)RAND_MAX) * (roomSize * 2) - roomSize;
        float posY = ((float)rand() / (float)RAND_MAX) * (roomSize * 2) - roomSize;

        int tooClose = 0;
        for (int k = 0; k < count; k++) {
            float dx = posX - scene->statues[k].x;
            float dy = posY - scene->statues[k].y;
            if (sqrtf(dx*dx + dy*dy) < 3.0f) { tooClose = 1; break; }
        }
        if (!tooClose) {
            scene->statues[count].x = posX;
            scene->statues[count].y = posY;
            count++;
        }
    }

    /* --- Modellek betöltése --- */
    load_model(&(scene->cube),   "assets/models/cube.obj");
    load_model(&(scene->statue), "assets/models/statue_1.obj");
    load_model(&(scene->round),  "assets/models/round.obj");

    /* --- Textúrák betöltése --- */
    scene->cube_texture    = load_texture("assets/textures/cube.png");
    scene->statue_texture  = load_texture("assets/textures/szobor_1.jpg");
    scene->round_table     = load_texture("assets/textures/round_table.png");
    scene->floor_texture   = load_texture("assets/textures/floor.jpg");
    scene->wall_texture    = load_texture("assets/textures/wall.jpg");
    scene->ceiling_texture = load_texture("assets/textures/ceiling.jpg");

    /* Festmények – tömbbel */
    for (int i = 0; i < PAINTING_COUNT; i++) {
        scene->painting_textures[i] = load_texture((char*)PAINTING_FILES[i]);
    }

    scene->help_texture = load_texture("assets/textures/help.png");
    if (scene->help_texture == 0)
        printf("[HIBA] Nem sikerult betolteni a help.png-t!\n");
    else
        printf("Sugo textura betoltve, ID: %u\n", scene->help_texture);

    /* --- Alapbeállítások --- */
    scene->light_intensity = 0.8f;
    scene->fog_density     = 0.05f;   /* Enyhe köd alapból */
    scene->rotation_angle  = 0.0f;

    scene->material.ambient.red   = 0.2f;
    scene->material.ambient.green = 0.2f;
    scene->material.ambient.blue  = 0.2f;
    scene->material.diffuse.red   = 1.0f;
    scene->material.diffuse.green = 1.0f;
    scene->material.diffuse.blue  = 1.0f;
    scene->material.shininess     = 50.0f;
}

void set_lighting(const Scene* scene)
{
    float ambient = scene->light_intensity * 0.2f;
    float diffuse = scene->light_intensity;

    float light_ambient[] = { ambient, ambient, ambient, 1.0f };
    float light_diffuse[] = { diffuse, diffuse, diffuse, 1.0f };
    float light_pos[]     = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void update_scene(Scene* scene, double delta_time)
{
    /* Időalapú forgatás (30 fok/másodperc) */
    scene->rotation_angle += 30.0f * (float)delta_time;
    if (scene->rotation_angle > 360.0f)
        scene->rotation_angle -= 360.0f;

    /* Ködsűrűség frissítése futásidőben */
    glFogf(GL_FOG_DENSITY, scene->fog_density);
}

void set_material(const Material* material)
{
    float ambient[]  = { material->ambient.red,  material->ambient.green,  material->ambient.blue,  1.0f };
    float diffuse[]  = { material->diffuse.red,  material->diffuse.green,  material->diffuse.blue,  1.0f };
    float specular[] = { material->specular.red, material->specular.green, material->specular.blue, 1.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT,   ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  specular);
    glMaterialf (GL_FRONT, GL_SHININESS, material->shininess);
}

void render_scene(const Scene* scene)
{
    set_lighting(scene);
    draw_environment(scene);
    draw_paintings(scene);

    for (int i = 0; i < STATUE_COUNT; i++) {
        glPushMatrix();
            glTranslatef(scene->statues[i].x, scene->statues[i].y, 0.0f);
            draw_statue_group(scene, &(scene->statue), scene->statue_texture);
        glPopMatrix();
    }
}

void change_light_intensity(Scene* scene, float amount)
{
    scene->light_intensity += amount;
    if (scene->light_intensity > 1.0f) scene->light_intensity = 1.0f;
    if (scene->light_intensity < 0.0f) scene->light_intensity = 0.0f;
}

void change_fog_density(Scene* scene, float amount)
{
    scene->fog_density += amount;
    if (scene->fog_density > 0.5f) scene->fog_density = 0.5f;
    if (scene->fog_density < 0.0f) scene->fog_density = 0.0f;
}
