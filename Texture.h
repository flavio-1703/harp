#pragma once

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>

#include "stb_image.h"

class Texture
{
public:
    Texture(const char* fileName, GLenum type);
    ~Texture();

private:
    GLuint id;
    int width;
    int height;
    unsigned char* localBuffer;
    unsigned int type;

public: 
    void bind(const GLint tex_unit) const;
    void unBind();
    void loadFromFile(const char* fileName);
public:
    inline GLuint getId() const { return this->id; }
    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }
};