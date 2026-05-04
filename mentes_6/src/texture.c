#include "texture.h"
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

GLuint load_texture(char* filename)
{
    SDL_Surface* surface = IMG_Load(filename);
    if (surface == NULL) {
        printf("[ERROR] Failed to load texture: %s\n", filename);
        return 0;
    }

    GLuint texture_name;
    glGenTextures(1, &texture_name);
    glBindTexture(GL_TEXTURE_2D, texture_name);

    // Textúra adatok átadása
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

    // --- ITT A JAVÍTÁS ---
    // Engedélyezzük az ismétlődést (ne nyújtsa, hanem csempézze)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Lineáris szűrés, hogy ne legyen pixeles (elmosott helyett simább lesz)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(surface);
    return texture_name;
}
