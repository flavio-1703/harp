#include <GL/glew.h>
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>

#include "stb_image.h"

class Texture
{
public:
    Texture(const char* fileName, GLenum type, GLint texUnit);
    ~Texture();

private:
    GLuint id;
    int width;
    int height;
    unsigned char* localBuffer;
    unsigned int type;
    GLint texUnit;
public: 
    void bind() const;
    void unBind();
    void loadFromFile(const char* fileName);
public:
    inline GLuint getId() const { return this->id; }
    inline GLint getTexUnit() const { return this->texUnit; }
    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }
};