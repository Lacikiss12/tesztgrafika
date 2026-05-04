#include "app.h"
#include <SDL2/SDL_image.h>
#include <GL/glu.h>
#include <stdio.h>
#include "scene.h"

void init_app(App* app, int width, int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) return;

    app->window = SDL_CreateWindow(
        "Az Ejszakai Muzeum",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    app->gl_context = SDL_GL_CreateContext(app->window);

    /* Relatív egérmód: nincs kattintás szükséges a nézelődéshez */
    SDL_SetRelativeMouseMode(SDL_TRUE);

    init_opengl();
    reshape(width, height);
    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->is_running = SDL_TRUE;
    app->show_help  = SDL_FALSE;
}

void init_opengl()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);

    /* Köd beállítása */
    glEnable(GL_FOG);
    GLfloat fogColor[] = { 0.05f, 0.05f, 0.1f, 1.0f };
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogi(GL_FOG_MODE, GL_EXP2);
    glFogf(GL_FOG_DENSITY, 0.05f);   /* enyhe köd alapból */
}

void reshape(int width, int height)
{
    double ratio = (double)width / height;
    int x, y, w, h;

    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2; y = 0;
    } else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0; y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 1000.0);
}

void handle_app_events(App* app)
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {

            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                    /* Mozgás */
                    case SDL_SCANCODE_W: set_camera_speed(&(app->camera),  3); break;
                    case SDL_SCANCODE_S: set_camera_speed(&(app->camera), -3); break;
                    case SDL_SCANCODE_A: set_camera_side_speed(&(app->camera),  3); break;
                    case SDL_SCANCODE_D: set_camera_side_speed(&(app->camera), -3); break;

                    /* Fény */
                    case SDL_SCANCODE_KP_PLUS:  change_light_intensity(&(app->scene),  0.05f); break;
                    case SDL_SCANCODE_KP_MINUS: change_light_intensity(&(app->scene), -0.05f); break;

                    /* Ködsűrűség (Extra funkció #1) */
                    case SDL_SCANCODE_G: change_fog_density(&(app->scene),  0.01f); break;
                    case SDL_SCANCODE_H: change_fog_density(&(app->scene), -0.01f); break;

                    /* Súgó */
                    case SDL_SCANCODE_F1: app->show_help = !app->show_help; break;

                    /* Kilépés – ESC felszabadítja az egeret is */
                    case SDL_SCANCODE_ESCAPE:
                        if (app->show_help) {
                            app->show_help = SDL_FALSE;
                        } else {
                            app->is_running = SDL_FALSE;
                        }
                        break;

                    default: break;
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_W: case SDL_SCANCODE_S:
                        set_camera_speed(&(app->camera), 0); break;
                    case SDL_SCANCODE_A: case SDL_SCANCODE_D:
                        set_camera_side_speed(&(app->camera), 0); break;
                    default: break;
                }
                break;

            /* Relatív egérmozgás – nem kell lenyomva tartani a gombot */
            case SDL_MOUSEMOTION:
                if (!app->show_help) {
                    rotate_camera(&(app->camera),
                                  -event.motion.xrel,
                                  -event.motion.yrel);
                }
                break;

            case SDL_QUIT:
                app->is_running = SDL_FALSE;
                break;

            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                    reshape(event.window.data1, event.window.data2);
                break;
        }
    }
}

void update_app(App* app, double delta_time)
{
    update_camera(&(app->camera), &(app->scene), delta_time);
    update_scene(&(app->scene), delta_time);
}

void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    set_view(&(app->camera));
    set_lighting(&(app->scene));
    render_scene(&(app->scene));
    draw_help(app);
    SDL_GL_SwapWindow(app->window);
}

void draw_help(App* app)
{
    if (!app->show_help) return;

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);         /* ne menjen át a ködön a súgó */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 1, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    if (app->scene.help_texture != 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, app->scene.help_texture);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    } else {
        glDisable(GL_TEXTURE_2D);
        glColor4f(0.0f, 0.0f, 0.0f, 0.85f);
    }

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(0, 0);
        glTexCoord2f(1, 0); glVertex2f(1, 0);
        glTexCoord2f(1, 1); glVertex2f(1, 1);
        glTexCoord2f(0, 1); glVertex2f(0, 1);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPopAttrib();
}

void destroy_app(App* app)
{
    SDL_SetRelativeMouseMode(SDL_FALSE);
    SDL_GL_DeleteContext(app->gl_context);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
}
