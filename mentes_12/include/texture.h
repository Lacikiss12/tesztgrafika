#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

typedef GLubyte Pixel[3];

/**
 * Load texture from file and returns with the texture name.
 */
GLuint load_texture(char* filename);
GLuint load_texture_with_wrap(char* filename, GLint wrap_mode);

#endif /* TEXTURE_H */
void show_texture_preview();
