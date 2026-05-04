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

        // --- FESTMÉNY A HÁTSÓ FALON (JAVÍTOTT KOORDINÁTÁK) ---
    glBindTexture(GL_TEXTURE_2D, scene->painting_texture);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, -1.0f, 0.0f);
        
        // A 0.0f és 1.0f felcserélésével megfordítjuk a képet függőlegesen
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 19.95f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f, 19.95f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.0f, 19.95f, 4.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 19.95f, 4.0f);
    glEnd();

// --- MÁSODIK FESTMÉNY (Jobbra, távolsággal) ---
    glBindTexture(GL_TEXTURE_2D, scene->painting_texture2);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, -1.0f, 0.0f);
        // x = 2.0-tól 6.0-ig (így marad köztük 4 egység távolság)
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 6.0f, 19.95f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 10.0f, 19.95f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 10.0f, 19.95f, 4.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 6.0f, 19.95f, 4.0f);
    glEnd();

    // --- Harmadik FESTMÉNY (Jobbra, távolsággal) ---
    glBindTexture(GL_TEXTURE_2D, scene->painting_texture3);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, -1.0f, 0.0f);
        // x = 2.0-tól 6.0-ig (így marad köztük 4 egység távolság)
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 14.0f, 19.95f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 18.0f, 19.95f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 18.0f, 19.95f, 4.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 14.0f, 19.95f, 4.0f);
    glEnd();

    // --- negyedik FESTMÉNY (balra, távolsággal) ---
    glBindTexture(GL_TEXTURE_2D, scene->painting_texture4);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, -1.0f, 0.0f);
        // x = 2.0-tól 6.0-ig (így marad köztük 4 egység távolság)
        glTexCoord2f(0.0f, 1.0f); glVertex3f( -10.0f, 19.95f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( -6.0f, 19.95f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( -6.0f, 19.95f, 4.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( -10.0f, 19.95f, 4.0f);
    glEnd();

    // --- ötödik FESTMÉNY (balra, távolsággal) ---
    glBindTexture(GL_TEXTURE_2D, scene->painting_texture5);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, -1.0f, 0.0f);
        // x = 2.0-tól 6.0-ig (így marad köztük 4 egység távolság)
        glTexCoord2f(0.0f, 1.0f); glVertex3f( -18.0f, 19.95f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( -14.0f, 19.95f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( -14.0f, 19.95f, 4.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( -18.0f, 19.95f, 4.0f);
    glEnd();

    // --- FESTMÉNY A BAL OLDALI FALON középen ---
    glBindTexture(GL_TEXTURE_2D, scene->painting_texture6);
    glBegin(GL_QUADS);
        // A normálvektor most jobbra, azaz az X tengely pozitív irányába mutat
        glNormal3f(1.0f, 0.0f, 0.0f); 

        // Az X fixen -19.95f, az Y változik (pl. -2-től +2-ig), a Z a magasság (1-től 4-ig)
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-19.95f, -2.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-19.95f,  2.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-19.95f,  2.0f, 4.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-19.95f, -2.0f, 4.0f);
    glEnd();

    // --- FESTMÉNY A BAL OLDALI FALON középtől jobra 1-el ---
    glBindTexture(GL_TEXTURE_2D, scene->painting_texture7);
    glBegin(GL_QUADS);
        // A normálvektor most jobbra, azaz az X tengely pozitív irányába mutat
        glNormal3f(1.0f, 0.0f, 0.0f); 

        // Az X fixen -19.95f, az Y változik (pl. -2-től +2-ig), a Z a magasság (1-től 4-ig)
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-19.95f, 6.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-19.95f, 10.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-19.95f, 10.0f, 4.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-19.95f, 6.0f, 4.0f);
    glEnd();

    // --- FESTMÉNY A BAL OLDALI FALON középtől jobbra 2-vel ---
    glBindTexture(GL_TEXTURE_2D, scene->painting_texture8);
    glBegin(GL_QUADS);
        // A normálvektor most jobbra, azaz az X tengely pozitív irányába mutat
        glNormal3f(1.0f, 0.0f, 0.0f); 

        // Az X fixen -19.95f, az Y változik (pl. -2-től +2-ig), a Z a magasság (1-től 4-ig)
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-19.95f, 14.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-19.95f, 18.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-19.95f, 18.0f, 4.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-19.95f, 14.0f, 4.0f);
    glEnd();

    // --- FESTMÉNY A BAL OLDALI FALON középtől balra 1-el ---
    glBindTexture(GL_TEXTURE_2D, scene->painting_texture9);
    glBegin(GL_QUADS);
        // A normálvektor most jobbra, azaz az X tengely pozitív irányába mutat
        glNormal3f(1.0f, 0.0f, 0.0f); 

        // Az X fixen -19.95f, az Y változik (pl. -2-től +2-ig), a Z a magasság (1-től 4-ig)
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-19.95f, -10.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-19.95f, -6.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-19.95f, -6.0f, 4.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-19.95f, -10.0f, 4.0f);
    glEnd();

    // --- FESTMÉNY A BAL OLDALI FALON középtől balra 2-vel ---
    glBindTexture(GL_TEXTURE_2D, scene->painting_texture10);
    glBegin(GL_QUADS);
        // A normálvektor most jobbra, azaz az X tengely pozitív irányába mutat
        glNormal3f(1.0f, 0.0f, 0.0f); 

        // Az X fixen -19.95f, az Y változik (pl. -2-től +2-ig), a Z a magasság (1-től 4-ig)
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-19.95f, -18.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-19.95f, -14.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-19.95f, -14.0f, 4.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-19.95f, -18.0f, 4.0f);
    glEnd();

    // --- FESTMÉNY A JOBB OLDALI FALON középen ---
    glBindTexture(GL_TEXTURE_2D, scene->painting_texture11);
    glBegin(GL_QUADS);
        glNormal3f(-1.0f, 0.0f, 0.0f); // Bevilágítás iránya: balra
        
        // Itt is az X fix (19.95), de a pontok sorrendje megfordul, hogy befelé nézzen a kép
        glTexCoord2f(0.0f, 1.0f); glVertex3f(19.95f,  2.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(19.95f, -2.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(19.95f, -2.0f, 4.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(19.95f,  2.0f, 4.0f);
    glEnd();

    // --- FESTMÉNY A JOBB OLDALI FALON középtől jobbra 1-el ---
    glBindTexture(GL_TEXTURE_2D, scene->painting_texture12);
    glBegin(GL_QUADS);
        glNormal3f(-1.0f, 0.0f, 0.0f); // Bevilágítás iránya: balra
        
        // Itt is az X fix (19.95), de a pontok sorrendje megfordul, hogy befelé nézzen a kép
        glTexCoord2f(0.0f, 1.0f); glVertex3f(19.95f,  10.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(19.95f,  6.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(19.95f,  6.0f, 4.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(19.95f,  10.0f, 4.0f);
    glEnd();

    // --- FESTMÉNY A JOBB OLDALI FALON középtől jobbra 2-vel ---
    glBindTexture(GL_TEXTURE_2D, scene->painting_texture13);
    glBegin(GL_QUADS);
        glNormal3f(-1.0f, 0.0f, 0.0f); // Bevilágítás iránya: balra
        
        // Itt is az X fix (19.95), de a pontok sorrendje megfordul, hogy befelé nézzen a kép
        glTexCoord2f(0.0f, 1.0f); glVertex3f(19.95f,  18.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(19.95f,  14.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(19.95f,  14.0f, 4.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(19.95f,  18.0f, 4.0f);
    glEnd();

    // --- FESTMÉNY A JOBB OLDALI FALON középtől balra 1-el ---
    glBindTexture(GL_TEXTURE_2D, scene->painting_texture14);
    glBegin(GL_QUADS);
        glNormal3f(-1.0f, 0.0f, 0.0f); // Bevilágítás iránya: balra
        
        // Itt is az X fix (19.95), de a pontok sorrendje megfordul, hogy befelé nézzen a kép
        glTexCoord2f(0.0f, 1.0f); glVertex3f(19.95f, -6.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(19.95f, -10.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(19.95f, -10.0f, 4.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(19.95f, -6.0f, 4.0f);
    glEnd();

    // --- FESTMÉNY A JOBB OLDALI FALON középtől balra 2-vel ---
    glBindTexture(GL_TEXTURE_2D, scene->painting_texture15);
    glBegin(GL_QUADS);
        glNormal3f(-1.0f, 0.0f, 0.0f); // Bevilágítás iránya: balra
        
        // Itt is az X fix (19.95), de a pontok sorrendje megfordul, hogy befelé nézzen a kép
        glTexCoord2f(0.0f, 1.0f); glVertex3f(19.95f, -14.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(19.95f, -18.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(19.95f, -18.0f, 4.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(19.95f, -14.0f, 4.0f);
    glEnd();

    // --- FESTMÉNY AZ ELSŐ FALON festmény középen (A hátad mögött) ---
    glBindTexture(GL_TEXTURE_2D, scene->painting_texture16);
    glBegin(GL_QUADS);
        // A normálvektor előre néz, a terem belseje felé
        glNormal3f(0.0f, 1.0f, 0.0f); 

        // y = -19.95f (a fal előtt), x változik, z a magasság
        // A sorrendet megfordítjuk a hátsó falhoz képest, hogy ne legyen tükrözve!
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.0f, -19.95f, 1.0f); // Bal alsó
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.0f, -19.95f, 1.0f); // Jobb alsó
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f, -19.95f, 4.0f); // Jobb felső
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 2.0f, -19.95f, 4.0f); // Bal felső
    glEnd();

    // --- FESTMÉNY AZ ELSŐ FALON festmény középétől balra 1-el (A hátad mögött) ---
    glBindTexture(GL_TEXTURE_2D, scene->painting_texture17);
    glBegin(GL_QUADS);
        // A normálvektor előre néz, a terem belseje felé
        glNormal3f(0.0f, 1.0f, 0.0f); 

        // y = -19.95f (a fal előtt), x változik, z a magasság
        // A sorrendet megfordítjuk a hátsó falhoz képest, hogy ne legyen tükrözve!
        glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, -19.95f, 1.0f); // Bal alsó
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 6.0f, -19.95f, 1.0f); // Jobb alsó
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 6.0f, -19.95f, 4.0f); // Jobb felső
        glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, -19.95f, 4.0f); // Bal felső
    glEnd();

    // --- FESTMÉNY AZ ELSŐ FALON festmény középétől balra 2-vel (A hátad mögött) ---
    glBindTexture(GL_TEXTURE_2D, scene->painting_texture18);
    glBegin(GL_QUADS);
        // A normálvektor előre néz, a terem belseje felé
        glNormal3f(0.0f, 1.0f, 0.0f); 

        // y = -19.95f (a fal előtt), x változik, z a magasság
        // A sorrendet megfordítjuk a hátsó falhoz képest, hogy ne legyen tükrözve!
        glTexCoord2f(0.0f, 1.0f); glVertex3f(18.0f, -19.95f, 1.0f); // Bal alsó
        glTexCoord2f(1.0f, 1.0f); glVertex3f(14.0f, -19.95f, 1.0f); // Jobb alsó
        glTexCoord2f(1.0f, 0.0f); glVertex3f(14.0f, -19.95f, 4.0f); // Jobb felső
        glTexCoord2f(0.0f, 0.0f); glVertex3f(18.0f, -19.95f, 4.0f); // Bal felső
    glEnd();
    
    // --- FESTMÉNY AZ ELSŐ FALON festmény középtől jobbra 1-el (A hátad mögött) ---
    glBindTexture(GL_TEXTURE_2D, scene->painting_texture19);
    glBegin(GL_QUADS);
        // A normálvektor előre néz, a terem belseje felé
        glNormal3f(0.0f, 1.0f, 0.0f); 

        // y = -19.95f (a fal előtt), x változik, z a magasság
        // A sorrendet megfordítjuk a hátsó falhoz képest, hogy ne legyen tükrözve!
        glTexCoord2f(0.0f, 1.0f); glVertex3f( -6.0f, -19.95f, 1.0f); // Bal alsó
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, -19.95f, 1.0f); // Jobb alsó
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -19.95f, 4.0f); // Jobb felső
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -19.95f, 4.0f); // Bal felső
    glEnd();

    // --- FESTMÉNY AZ ELSŐ FALON festmény középtől jobbra 2-vel (A hátad mögött) ---
    glBindTexture(GL_TEXTURE_2D, scene->painting_texture20);
    glBegin(GL_QUADS);
        // A normálvektor előre néz, a terem belseje felé
        glNormal3f(0.0f, 1.0f, 0.0f); 

        // y = -19.95f (a fal előtt), x változik, z a magasság
        // A sorrendet megfordítjuk a hátsó falhoz képest, hogy ne legyen tükrözve!
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-14.0f, -19.95f, 1.0f); // Bal alsó
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-18.0f, -19.95f, 1.0f); // Jobb alsó
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-18.0f, -19.95f, 4.0f); // Jobb felső
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-14.0f, -19.95f, 4.0f); // Bal felső
    glEnd();

    // --- 3. PLAFON (ÚJ) ---
    glBindTexture(GL_TEXTURE_2D, scene->ceiling_texture);
    glBegin(GL_QUADS);
        // A normálvektor LEFELÉ mutat (Z tengely negatív iránya)
        glNormal3f(0.0f, 0.0f, -1.0f);
        
        // A sarkok z=5.0 magasságban vannak
        glTexCoord2f(0.0f, 0.0f);   glVertex3f(-20.0f, -20.0f, 5.0f);
        glTexCoord2f(10.0f, 0.0f);  glVertex3f( 20.0f, -20.0f, 5.0f);
        glTexCoord2f(10.0f, 10.0f); glVertex3f( 20.0f,  20.0f, 5.0f);
        glTexCoord2f(0.0f, 10.0f);  glVertex3f(-20.0f,  20.0f, 5.0f);
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