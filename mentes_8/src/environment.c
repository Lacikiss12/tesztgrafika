#include "environment.h"
#include <GL/gl.h>

void draw_environment(const Scene* scene) {
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
}

void draw_paintings(const Scene* scene) {
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
}

void draw_statue_group(const Scene* scene) {
    // 1. PILLÉR (Fix)
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->wall_texture); 
        glTranslatef(0.0f, 0.0f, 0.4f); 
        glScalef(0.6f, 0.6f, 0.8f);
        draw_model(&(scene->cube)); // Ha ez a kocka modellje
    glPopMatrix();

   // 2. FORGÓ EGYSÉG (A pillér tetején)
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.8f); // Felvisszük a pillér tetejére (fix pozíció)
        
        // Itt hívjuk meg a forgatást! 
        // Mivel ez a korong és a szobor blokkja előtt van, mindkettő forogni fog.
        glRotatef(scene->rotation_angle, 0, 0, 1); 

    // --- Korong (Kör objektum) ---
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->round_table);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glScalef(0.05f, 0.1f, 0.05f); // Kicsit szélesebb korong (0.4)
        draw_model(&(scene->round)); 
    glPopMatrix();

    // --- AZ ÚJ SZOBOR ---
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.01f); // Emelés a korongra
        glBindTexture(GL_TEXTURE_2D, scene->statue_texture);

        // Ha fejjel lefelé van, próbáld meg ezt a forgatást:
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // -90 helyett +90

        // VAGY ha még mindig nem áll jól, próbáld meg az Y tengelyen (ami most a függőleges):
        // glRotatef(180.0f, 0.0f, 1.0f, 0.0f); 

        glScalef(0.04f, 0.04f, 0.04f); 
        draw_model(&(scene->statue));
    glPopMatrix();

    glPopMatrix();
}

void draw_vitrine(const Scene* scene) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_LIGHTING); 
    glDisable(GL_TEXTURE_2D);
    glDepthMask(GL_FALSE); 

    glPushMatrix();
        // ELTOLÁS: 
        // X, Y = 0 (középen van)
        // Z = Pillér teteje (0.8) + Vitrin magasságának fele (1.4 / 2 = 0.7)
        // Összesen: 0.8 + 0.7 = 1.5f
        glTranslatef(0.0f, 0.0f, 1.1f); 

        glColor4f(0.5f, 0.8f, 1.0f, 0.2f); 

        // SKÁLÁZÁS:
        // X, Y = 0.6f (pontosan a pillér szélessége)
        // Z = 1.4f (a vitrin saját magassága)
        glScalef(0.6f, 0.6f, 0.6f); 

        draw_model(&(scene->cube)); 
    glPopMatrix();

    glDepthMask(GL_TRUE); 
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}
