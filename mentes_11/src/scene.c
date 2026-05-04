#include "scene.h"
#include <obj/load.h>
#include <obj/draw.h>
#include <stdio.h>
#include <environment.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

/* --- FÜGGVÉNYEK DEFINÍCIÓJA --- */

void init_scene(Scene* scene)
{
   srand(time(NULL));

    int count = 0;          // Csak EGYSZER definiáljuk
    float roomSize = 15.0f;  // Csak EGYSZER definiáljuk

    // Kitöröljük az összes korábbi ciklust, és csak ez marad:
    while (count < 20) {
        float posX = ((float)rand() / (float)RAND_MAX) * (roomSize * 2) - roomSize;
        float posY = ((float)rand() / (float)RAND_MAX) * (roomSize * 2) - roomSize;

        int tooClose = 0;
        for (int k = 0; k < count; k++) {
            float dx = posX - scene->statues[k].x;
            float dy = posY - scene->statues[k].y;
            float dist = sqrtf(dx * dx + dy * dy);
            
            if (dist < 3.0f) { // Minimum 3 méter távolság
                tooClose = 1;
                break;
            }
        }

        if (!tooClose) {
            scene->statues[count].x = posX;
            scene->statues[count].y = posY;
            count++;
        }
    }






    // Szobor modell és textúra betöltése
    load_model(&(scene->cube), "assets/models/cube.obj"); 
    load_model(&(scene->statue), "assets/models/statue_1.obj");
    load_model(&(scene->round), "assets/models/round.obj");
    scene->cube_texture = load_texture("assets/textures/cube.png");
    scene->statue_texture = load_texture("assets/textures/szobor_1.jpg");
    scene->round_table = load_texture("assets/textures/round_table.png");

    // Padló textúra betöltése
    scene->floor_texture = load_texture("assets/textures/floor.jpg");
    scene->wall_texture = load_texture("assets/textures/wall.jpg");
    scene->ceiling_texture = load_texture("assets/textures/ceiling.jpg");
    scene->painting_texture = load_texture("assets/textures/mona_lisa.jpg");
    scene->painting_texture2 = load_texture("assets/textures/danika.jpg");
    scene->painting_texture3 = load_texture("assets/textures/meme3.jpg");
    scene->painting_texture4 = load_texture("assets/textures/meme4.jpg");
    scene->painting_texture5 = load_texture("assets/textures/meme5.jpg");
    scene->painting_texture6 = load_texture("assets/textures/meme6.jpg");
    scene->painting_texture7 = load_texture("assets/textures/meme7.jpg");
    scene->painting_texture8 = load_texture("assets/textures/meme8.jpg");
    scene->painting_texture9 = load_texture("assets/textures/meme9.jpg");
    scene->painting_texture10 = load_texture("assets/textures/meme10.jpg");
    scene->painting_texture11 = load_texture("assets/textures/meme11.jpg");
    scene->painting_texture12 = load_texture("assets/textures/meme12.jpg");
    scene->painting_texture13 = load_texture("assets/textures/meme13.jpg");
    scene->painting_texture14 = load_texture("assets/textures/meme14.jpg");
    scene->painting_texture15 = load_texture("assets/textures/meme15.jpg");
    scene->painting_texture16 = load_texture("assets/textures/meme16.jpg");
    scene->painting_texture17 = load_texture("assets/textures/meme17.jpg");
    scene->painting_texture18 = load_texture("assets/textures/meme18.jpg");
    scene->painting_texture19 = load_texture("assets/textures/meme19.jpg");
    scene->painting_texture20 = load_texture("assets/textures/meme20.jpg");
    scene->help_texture = load_texture("assets/textures/help.png");
    if (scene->help_texture == 0) {
        printf("[HIBA] Nem sikerult betolteni a help.png-t!\n");
    } else {
        printf("Sugo textura betoltve, ID: %u\n", scene->help_texture);
    }

    // Alapbeállítások
    scene->light_intensity = 0.8f;
    scene->rotation_angle = 0.0f;

    // Anyagjellemzők beállítása (példa)
    scene->material.ambient.red = 0.2f;
    scene->material.ambient.green = 0.2f;
    scene->material.ambient.blue = 0.2f;
    
    scene->material.diffuse.red = 1.0f;
    scene->material.diffuse.green = 1.0f;
    scene->material.diffuse.blue = 1.0f;

    scene->material.shininess = 50.0f;
}

void set_lighting(const Scene* scene)
{
    float ambient = scene->light_intensity * 0.2f;
    float diffuse = scene->light_intensity;

    float light_ambient[] = { ambient, ambient, ambient, 1.0f };
    float light_diffuse[] = { diffuse, diffuse, diffuse, 1.0f };
    float light_pos[] = { 0.0f, 0.0f, 10.0f, 1.0f }; // Fentről jövő fény

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void update_scene(Scene* scene, double delta_time)
{
    // Időalapú forgatás (30 fok/másodperc)
    scene->rotation_angle += 30.0f * (float)delta_time;
    if (scene->rotation_angle > 360.0f) {
        scene->rotation_angle -= 360.0f;
    }
}

void set_material(const Material* material)
{
    float ambient[] = { material->ambient.red, material->ambient.green, material->ambient.blue, 1.0f };
    float diffuse[] = { material->diffuse.red, material->diffuse.green, material->diffuse.blue, 1.0f };
    float specular[] = { material->specular.red, material->specular.green, material->specular.blue, 1.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);
}

void render_scene(const Scene* scene)
{
    // 1. Fények beállítása
    set_lighting(scene);
    // 1. Környezet (Falak, padló, plafon)
    draw_environment(scene);
    // 2. Dekoráció (Festmények)
    draw_paintings(scene);


    // A render_scene-ben a környezet rajzolása után:
    for (int i = 0; i < 20; i++) {
        glPushMatrix();
            // Elvisszük a szoborcsoportot az előre kiszámolt véletlen helyére
            glTranslatef(scene->statues[i].x, scene->statues[i].y, 0.0f);
            
            // Paraméterek: 
            // 1. scene (környezeti adatok)
            // 2. &(scene->statue) (a konkrét modell címe)
            // 3. scene->statue_texture (a hozzá tartozó textúra)
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
