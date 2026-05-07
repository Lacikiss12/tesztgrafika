#include "environment.h"
#include <GL/gl.h>

/* ------------------------------------------------------------------ */
/*  Segédfüggvény: festménykeret rajzolása GL_LINES-szal               */
/*  p0..p1: a festmény síkbeli sarokpontjai, n: normálvektor iránya    */
/* ------------------------------------------------------------------ */
void draw_painting_frame(float x0, float y0, float z0,
                         float x1, float y1, float z1,
                         float nx, float ny, float nz)
{
    (void)nx; (void)ny; (void)nz;   /* normál itt csak tájékoztató */

    /* A négy sarokpont meghatározása (a két átlós végpontból) */
    /* Feltételezzük: x0<=x1 vagy y0<=y1, z0<=z1 */
    float offset = 0.02f;   /* keret kicsit előrébb, hogy ne z-harcoljon */

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3f(0.55f, 0.35f, 0.05f);   /* arany/dió barna szín */
    glLineWidth(4.0f);

    glBegin(GL_LINE_LOOP);
        /* A keret koordinátái a fal elé tolva offset-tel */
        glVertex3f(x0 + nx*offset, y0 + ny*offset, z0);
        glVertex3f(x1 + nx*offset, y1 + ny*offset, z0);
        glVertex3f(x1 + nx*offset, y1 + ny*offset, z1);
        glVertex3f(x0 + nx*offset, y0 + ny*offset, z1);
    glEnd();

    glLineWidth(1.0f);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
}

/* ------------------------------------------------------------------ */
/*  Padló, falak, plafon                                               */
/* ------------------------------------------------------------------ */
void draw_environment(const Scene* scene)
{
    /* PADLÓ */
    glBindTexture(GL_TEXTURE_2D, scene->floor_texture);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glTexCoord2f(0.0f,  0.0f);  glVertex3f(-20.0f, -20.0f, 0.0f);
        glTexCoord2f(10.0f, 0.0f);  glVertex3f( 20.0f, -20.0f, 0.0f);
        glTexCoord2f(10.0f, 10.0f); glVertex3f( 20.0f,  20.0f, 0.0f);
        glTexCoord2f(0.0f,  10.0f); glVertex3f(-20.0f,  20.0f, 0.0f);
    glEnd();

    /* FALAK */
    glBindTexture(GL_TEXTURE_2D, scene->wall_texture);
    glBegin(GL_QUADS);

        /* Hátsó fal  Y = +20 */
        glNormal3f(0.0f, -1.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-20.0f, 20.0f, 0.0f);
        glTexCoord2f(5.0f, 1.0f); glVertex3f( 20.0f, 20.0f, 0.0f);
        glTexCoord2f(5.0f, 0.0f); glVertex3f( 20.0f, 20.0f, 5.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-20.0f, 20.0f, 5.0f);

        /* Bal fal  X = -20 */
        glNormal3f(1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-20.0f, -20.0f, 0.0f);
        glTexCoord2f(5.0f, 1.0f); glVertex3f(-20.0f,  20.0f, 0.0f);
        glTexCoord2f(5.0f, 0.0f); glVertex3f(-20.0f,  20.0f, 5.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-20.0f, -20.0f, 5.0f);

        /* Jobb fal  X = +20 */
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 20.0f,  20.0f, 0.0f);
        glTexCoord2f(5.0f, 1.0f); glVertex3f( 20.0f, -20.0f, 0.0f);
        glTexCoord2f(5.0f, 0.0f); glVertex3f( 20.0f, -20.0f, 5.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 20.0f,  20.0f, 5.0f);

        /* Elülső fal  Y = -20 */
        glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 20.0f, -20.0f, 0.0f);
        glTexCoord2f(5.0f, 1.0f); glVertex3f(-20.0f, -20.0f, 0.0f);
        glTexCoord2f(5.0f, 0.0f); glVertex3f(-20.0f, -20.0f, 5.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 20.0f, -20.0f, 5.0f);
    glEnd();

    /* PLAFON */
    glBindTexture(GL_TEXTURE_2D, scene->ceiling_texture);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glTexCoord2f(0.0f,  0.0f);  glVertex3f(-20.0f, -20.0f, 5.0f);
        glTexCoord2f(10.0f, 0.0f);  glVertex3f( 20.0f, -20.0f, 5.0f);
        glTexCoord2f(10.0f, 10.0f); glVertex3f( 20.0f,  20.0f, 5.0f);
        glTexCoord2f(0.0f,  10.0f); glVertex3f(-20.0f,  20.0f, 5.0f);
    glEnd();
}

/* ------------------------------------------------------------------ */
/*  Festmény segédfüggvény: 1 kép kirajzolása + keret                 */
/* ------------------------------------------------------------------ */
static void draw_one_painting(GLuint tex,
                               float ax, float ay, float az,
                               float bx, float by, float bz,
                               float nx, float ny, float nz)
{
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
        glNormal3f(nx, ny, nz);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(ax, ay, az);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(bx, by, az);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(bx, by, bz);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(ax, ay, bz);
    glEnd();

    draw_painting_frame(ax, ay, az, bx, by, bz, nx, ny, nz);
}

static void fit_painting_size(float aspect, float max_width, float max_height, float* out_width, float* out_height)
{
    float width = max_width;
    float height;

    if (aspect < 0.1f) {
        aspect = 4.0f / 3.0f;
    }

    height = width / aspect;
    if (height > max_height) {
        height = max_height;
        width = height * aspect;
    }

    *out_width = width;
    *out_height = height;
}

/* ------------------------------------------------------------------ */
/*  Összes festmény kirajzolása (4 fal, egyenletesen elosztva)        */
/* ------------------------------------------------------------------ */
void draw_paintings(const Scene* scene)
{
    int idx = 0;
    const float max_slot_width = 4.0f;
    const float max_slot_height = 3.0f;

    /* ---- HÁTSÓ FAL  (Y = +19.95, normál: (0,-1,0)) ---- */
    /* 5 kép vízszintesen */
    float back_xs[][2] = {
        {-18.0f, -14.0f},
        {-10.0f,  -6.0f},
        { -2.0f,   2.0f},
        {  6.0f,  10.0f},
        { 14.0f,  18.0f}
    };
    for (int i = 0; i < 5 && idx < PAINTING_COUNT; i++, idx++) {
        float cx = (back_xs[i][0] + back_xs[i][1]) * 0.5f;
        float cy = 19.95f;
        float cz = 2.5f;
        float width;
        float height;
        fit_painting_size(scene->painting_aspects[idx], max_slot_width, max_slot_height, &width, &height);
        draw_one_painting(scene->painting_textures[idx],
            cx - width * 0.5f, cy, cz - height * 0.5f,
            cx + width * 0.5f, cy, cz + height * 0.5f,
            0.0f, -1.0f, 0.0f);
    }

    /* ---- BAL FAL  (X = -19.95, normál: (1,0,0)) ---- */
    /* 5 kép, Y tengelyen elosztva */
    float left_ys[][2] = {
        {-18.0f, -14.0f},
        {-10.0f,  -6.0f},
        { -2.0f,   2.0f},
        {  6.0f,  10.0f},
        { 14.0f,  18.0f}
    };
    for (int i = 0; i < 5 && idx < PAINTING_COUNT; i++, idx++) {
        float cx = -19.95f;
        float cy = (left_ys[i][0] + left_ys[i][1]) * 0.5f;
        float cz = 2.5f;
        float width;
        float height;
        fit_painting_size(scene->painting_aspects[idx], max_slot_width, max_slot_height, &width, &height);
        draw_one_painting(scene->painting_textures[idx],
                          cx, cy - width * 0.5f, cz - height * 0.5f,
                          cx, cy + width * 0.5f, cz + height * 0.5f,
                          1.0f, 0.0f, 0.0f);
    }

    /* ---- JOBB FAL  (X = +19.95, normál: (-1,0,0)) ---- */
    float right_ys[][2] = {
        {-18.0f, -14.0f},
        {-10.0f,  -6.0f},
        { -2.0f,   2.0f},
        {  6.0f,  10.0f},
        { 14.0f,  18.0f}
    };
    for (int i = 0; i < 5 && idx < PAINTING_COUNT; i++, idx++) {
        float cx = 19.95f;
        float cy = (right_ys[i][0] + right_ys[i][1]) * 0.5f;
        float cz = 2.5f;
        float width;
        float height;
        fit_painting_size(scene->painting_aspects[idx], max_slot_width, max_slot_height, &width, &height);
        draw_one_painting(scene->painting_textures[idx],
                          cx, cy - width * 0.5f, cz - height * 0.5f,
                          cx, cy + width * 0.5f, cz + height * 0.5f,
                          -1.0f, 0.0f, 0.0f);
    }

    /* ---- ELÜLSŐ FAL  (Y = -19.95, normál: (0,1,0)) ---- */
    float front_xs[][2] = {
        {-18.0f, -14.0f},
        {-10.0f,  -6.0f},
        { -2.0f,   2.0f},
        {  6.0f,  10.0f},
        { 14.0f,  18.0f}
    };
    for (int i = 0; i < 5 && idx < PAINTING_COUNT; i++, idx++) {
        float cx = (front_xs[i][0] + front_xs[i][1]) * 0.5f;
        float cy = -19.95f;
        float cz = 2.5f;
        float width;
        float height;
        fit_painting_size(scene->painting_aspects[idx], max_slot_width, max_slot_height, &width, &height);
        draw_one_painting(scene->painting_textures[idx],
                          cx - width * 0.5f, cy, cz - height * 0.5f,
                          cx + width * 0.5f, cy, cz + height * 0.5f,
                          0.0f, 1.0f, 0.0f);
    }
}

/* ------------------------------------------------------------------ */
/*  Szoborcsoport: pillér + forgó szobor + vitrin                     */
/* ------------------------------------------------------------------ */
void draw_statue_group(const Scene* scene, const Model* current_model, GLuint current_texture)
{
    /* 1. PILLÉR */
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->wall_texture);
        glTranslatef(0.0f, 0.0f, 0.4f);
        glScalef(0.6f, 0.6f, 0.8f);
        draw_model(&(scene->cube));
    glPopMatrix();

    /* 2. FORGÓ EGYSÉG */
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.8f);
        glRotatef(scene->rotation_angle, 0, 0, 1);

        /* Korong */
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, scene->round_table);
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            glScalef(0.05f, 0.1f, 0.05f);
            draw_model(&(scene->round));
        glPopMatrix();

        /* Szobor */
        glPushMatrix();
            glTranslatef(0.0f, 0.0f, 0.01f);
            glBindTexture(GL_TEXTURE_2D, current_texture);
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            glScalef(0.04f, 0.04f, 0.04f);
            draw_model(current_model);
        glPopMatrix();
    glPopMatrix();

    /* 3. VITRIN */
    draw_vitrine(scene);
}

/* ------------------------------------------------------------------ */
/*  Áttetsző üvegvitrin                                               */
/* ------------------------------------------------------------------ */
void draw_vitrine(const Scene* scene)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDepthMask(GL_FALSE);

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 1.1f);
        /* Halvány kékes-zöld üveg szín, 25% átlátszóság */
        glColor4f(0.4f, 0.85f, 0.9f, 0.25f);
        glScalef(0.65f, 0.65f, 0.65f);
        draw_model(&(scene->cube));
    glPopMatrix();

    glDepthMask(GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}
