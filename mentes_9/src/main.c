#include "app.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    (void)argc; (void)argv;
    App app;
    uint32_t last_time, current_time;
    double delta_time;

    init_app(&app, 1280, 720);
    last_time = SDL_GetTicks();

    while (app.is_running) {
        current_time = SDL_GetTicks();
        delta_time = (double)(current_time - last_time) / 1000.0;
        last_time = current_time;

        handle_app_events(&app);
        update_app(&app, delta_time);
        render_app(&app);
    }
    destroy_app(&app);
    return 0;
}