#include "scene.h"
#include <obj/load.h>
#include <obj/draw.h>
#include <stdio.h>

/* --- FÜGGVÉNYEK DEFINÍCIÓJA --- */

void init_scene(Scene* scene)
{
    // Szobor modell és textúra betöltése
    load_model(&(scene->statue), "assets/models/cube.obj"); 
    scene->texture_id = load_texture("assets/textures/cube.png");

    // Padló textúra betöltése
    scene->floor_texture = load_texture("assets/textures/floor.jpg");
    scene->wall_texture = load_texture("assets/textures/wall.jpg");

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

void render_scene(const Scene* scene)
{
    // 1. Fények beállítása
    set_lighting(scene);

            // PADLÓ RAJZOLÁSA
        glBindTexture(GL_TEXTURE_2D, scene->floor_texture);
        glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);

        // Ha 0.0 és 1.0 között adod meg, akkor 1x rakja ki (nyújtja)
        // Ha 0.0 és 10.0 között, akkor 10x10-es négyzethálóban csempézi!
        glTexCoord2f(0.0f, 0.0f);   glVertex3f(-20.0f, -20.0f, 0.0f);
        glTexCoord2f(10.0f, 0.0f);  glVertex3f( 20.0f, -20.0f, 0.0f);
        glTexCoord2f(10.0f, 10.0f); glVertex3f( 20.0f,  20.0f, 0.0f);
        glTexCoord2f(0.0f, 10.0f);  glVertex3f(-20.0f,  20.0f, 0.0f);
    glEnd();

        // --- 2. FALAK RAJZOLÁSA ---
        glBindTexture(GL_TEXTURE_2D, scene->wall_texture);
        glBegin(GL_QUADS);

        // HÁTSÓ FAL (Y = 20 sík)
        glNormal3f(0.0f, -1.0f, 0.0f); // Befelé néz
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-20.0f, 20.0f, 0.0f);
        glTexCoord2f(5.0f, 1.0f); glVertex3f( 20.0f, 20.0f, 0.0f);
        glTexCoord2f(5.0f, 0.0f); glVertex3f( 20.0f, 20.0f, 5.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-20.0f, 20.0f, 5.0f);

        // BAL OLDALI FAL (X = -20 sík)
        glNormal3f(1.0f, 0.0f, 0.0f); // Jobbra, befelé néz
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-20.0f, -20.0f, 0.0f);
        glTexCoord2f(5.0f, 1.0f); glVertex3f(-20.0f,  20.0f, 0.0f);
        glTexCoord2f(5.0f, 0.0f); glVertex3f(-20.0f,  20.0f, 5.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-20.0f, -20.0f, 5.0f);

        // JOBB OLDALI FAL (X = 20 sík)
        glNormal3f(-1.0f, 0.0f, 0.0f); // Balra, befelé néz
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 20.0f,  20.0f, 0.0f);
        glTexCoord2f(5.0f, 1.0f); glVertex3f( 20.0f, -20.0f, 0.0f);
        glTexCoord2f(5.0f, 0.0f); glVertex3f( 20.0f, -20.0f, 5.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 20.0f,  20.0f, 5.0f);

        // ELÜLSŐ FAL (Y = -20 sík)
        glNormal3f(0.0f, 1.0f, 0.0f); // Kifelé, befelé néz
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 20.0f, -20.0f, 0.0f);
        glTexCoord2f(5.0f, 1.0f); glVertex3f(-20.0f, -20.0f, 0.0f);
        glTexCoord2f(5.0f, 0.0f); glVertex3f(-20.0f, -20.0f, 5.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 20.0f, -20.0f, 5.0f);

    glEnd();
    // 3. Szobor/Kocka rajzolása
    glBindTexture(GL_TEXTURE_2D, scene->texture_id);
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 1.0f); // Emeljük a padló fölé
        glRotatef(scene->rotation_angle, 0, 0, 1);
        draw_model(&(scene->statue));
    glPopMatrix();
}

void change_light_intensity(Scene* scene, float amount)
{
    scene->light_intensity += amount;
    if (scene->light_intensity > 1.0f) scene->light_intensity = 1.0f;
    if (scene->light_intensity < 0.0f) scene->light_intensity = 0.0f;
}