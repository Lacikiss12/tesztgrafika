#ifndef APP_H
#define APP_H

#include "camera.h"
#include "scene.h"
#include <SDL2/SDL.h>

#define VIEWPORT_RATIO (16.0 / 9.0)
#define VIEWPORT_ASPECT 50.0
#define VIEWPORT_NEAR 0.5
#define VIEWPORT_FAR 120.0

typedef struct App {
    SDL_Window*   window;
    SDL_GLContext gl_context;
    SDL_bool      is_running;
    SDL_bool      show_help;
    Camera        camera;
    Scene         scene;
} App;

void init_app(App* app, int width, int height);
void init_opengl(void);
void reshape(int width, int height);
void handle_app_events(App* app);
void update_app(App* app, double delta_time);
void render_app(App* app);
void draw_help(App* app);
void destroy_app(App* app);

#endif /* APP_H */
