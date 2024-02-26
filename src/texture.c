#include "texture.h"

texture_t texture_new(const char *file_path, int slot) {
    texture_t texture;
    int width, height, num_chan;    


    unsigned char* bytes = stbi_load(file_path, &width, &height, &num_chan, 0);

    glGenTextures(1, &texture.ID);
    texture_activate(slot);
    texture_bind(texture);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    texture_unbind();

    return texture;
}

void texture_activate(int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
}

void texture_bind(texture_t texture) {
    glBindTexture(GL_TEXTURE_2D, texture.ID);
}

void texture_unbind() {
    glBindTexture(GL_TEXTURE_2D, 0); 
}

void texture_delete(texture_t texture) {
    glDeleteTextures(1, &texture.ID);
}
