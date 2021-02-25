#pragma once

#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
    GLuint id;

    const int VER_MAJOR;
    const int VER_MINOR;

    std::string loadShaderSrc(const char* filename);
    GLuint loadShader(GLenum type, const char* filename);
    void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader);


public:
    //Constructor Destructor
    Shader(const int VER_MAJOR, const int VER_MINOR, const char* vertexFile, const char* fragmentFile, const char* geometryFile);
    ~Shader();

public:
    void use();
    void unUse();
public:
    void setVec1f(GLfloat value, const GLchar* name);
    void setVec2f(glm::fvec2 value, const GLchar* name);
    void setVec3f(glm::fvec3 value, const GLchar* name);
    void setVec4f(glm::fvec4 value, const GLchar* name);
    void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose);
    void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose);
    void set1i(GLint value, const GLchar* name);

};