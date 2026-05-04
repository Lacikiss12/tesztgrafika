#include "texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

GLuint load_texture(char* filename)
{
    SDL_Surface* surface = IMG_Load(filename);
    if (surface == NULL) {
        printf("[ERROR] Nem sikerult betolteni: %s\n", filename);
        return 0;
    }

    /* Ha a kép nem RGB formátumú (pl. RGBA PNG), konvertáljuk */
    SDL_Surface* converted = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB24, 0);
    SDL_FreeSurface(surface);
    if (converted == NULL) {
        printf("[ERROR] Nem sikerult konvertalni: %s\n", filename);
        return 0;
    }

    GLuint texture_name;
    glGenTextures(1, &texture_name);
    glBindTexture(GL_TEXTURE_2D, texture_name);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 converted->w, converted->h, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, converted->pixels);

    SDL_FreeSurface(converted);
    return texture_name;
}
