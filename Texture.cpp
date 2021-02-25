#include "Texture.h"


//constructor/destructor
Texture::Texture(const char* fileName, GLenum type)
{   

    this->type = type;

    unsigned char* image = stbi_load(fileName, &this->width, &this->height, NULL, 4);

    glGenTextures(1, &this->id);
    glBindTexture(this->type, this->id);

    glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if(image)
    {
        glTexImage2D(this->type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    }
    else
    {
        std::cout << "ERROR: TEXTURE LOADING FAILED" << fileName << std::endl;
    }

    glActiveTexture(0);
    glBindTexture(this->type, 0);
    stbi_image_free(image);

}

Texture::~Texture()
{
    glDeleteTextures(1, &this->id);
}

void Texture::bind(const GLint tex_unit) const
{
    glActiveTexture(GL_TEXTURE0 + tex_unit);
    glBindTexture(this->type, this->id);
}

void Texture::unBind()
{
    glActiveTexture(0);
    glBindTexture(this->type, 0);
}

void Texture::loadFromFile(const char* fileName)
{
    if (this->id)
    {
        glDeleteTextures(1, &this->id);
    }

    unsigned char* image = stbi_load(fileName, &this->width, &this->height, NULL, 4);

    glGenTextures(1, &this->id);
    glBindTexture(this->type, this->id);

    glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if(image)
    {
        glTexImage2D(this->type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    }
    else
    {
        std::cout << "ERROR: TEXTURE: LOAD FROM FILE: LOADING FAILED" << fileName << std::endl;
    }

    glActiveTexture(0);
    glBindTexture(this->type, 0);
    stbi_image_free(image);
}

