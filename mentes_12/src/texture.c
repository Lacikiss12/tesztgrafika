#include "texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef GL_TEXTURE_MAX_ANISOTROPY_EXT
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#endif

#ifndef GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#endif

#ifndef GL_GENERATE_MIPMAP
#define GL_GENERATE_MIPMAP 0x8191
#endif

GLuint load_texture_with_wrap(char* filename, GLint wrap_mode)
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

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (SDL_GL_ExtensionSupported("GL_SGIS_generate_mipmap")) {
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }

    {
        int row_bytes = converted->w * 3;
        size_t data_size = (size_t)row_bytes * (size_t)converted->h;
        unsigned char* tight_pixels = (unsigned char*)malloc(data_size);
        if (tight_pixels == NULL) {
            SDL_FreeSurface(converted);
            printf("[ERROR] Nem sikerult memoriat foglalni texture bufferhez: %s\n", filename);
            return 0;
        }

        for (int y = 0; y < converted->h; ++y) {
            const unsigned char* src = (const unsigned char*)converted->pixels + (size_t)y * (size_t)converted->pitch;
            unsigned char* dst = tight_pixels + (size_t)y * (size_t)row_bytes;
            memcpy(dst, src, (size_t)row_bytes);
        }

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                     converted->w, converted->h, 0,
                     GL_RGB, GL_UNSIGNED_BYTE, tight_pixels);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        free(tight_pixels);
    }

    if (SDL_GL_ExtensionSupported("GL_EXT_texture_filter_anisotropic")) {
        GLfloat max_aniso = 1.0f;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_aniso);
        if (max_aniso > 1.0f) {
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_aniso);
        }
    }

    SDL_FreeSurface(converted);
    return texture_name;
}

GLuint load_texture(char* filename)
{
    return load_texture_with_wrap(filename, GL_REPEAT);
}
