#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"


enum shader_enum
{
    SHADER_CORE_PROGRAM = 0
};

enum texture_enum
{
    TEX_PUSHEEN0, TEX_CONTAINER
};

enum material_num
{
    MAT_1 = 0
};

enum mesh_enum 
{
    MESH_QUAD = 0
};

class Game
{
private:
    GLFWwindow* window;
    const int WIN_WIDTH;
    const int WIN_HEIGHT;
    int fbWidth;
    int fbHeight;

private:
//Opengl context
    const int GL_VER_MAJOR;
    const int GL_VER_MINOR;

private:
//Matrices
    glm::mat4 ViewMatrix;
    glm::vec3 camPos;
    glm::vec3 woldUp;
    glm::vec3 camFront;
    glm::mat4 ProjectionMatrix;
    
    float fov;
    float nearPlane;
    float farPlane;

private:
    std::vector<Shader*> shaders;
    std::vector<Texture*> textures;
    std::vector<Material*> materials;
    std::vector<Mesh*> meshes;

private:
//Funcs
    void initGLFW();
    void initWindow(const char* title, bool resizable);
    void initGLEW();
    void initGLOptions();
    void initMatrices();
    void initShaders();
    void initTextures();
    void initMaterials();
    void initMeshes();
    
public:
    Game(const char* title, const int WIDTH, const int HEIGHT, const int GL_VER_MAJOR, const int GL_VER_MINOR, bool resizable);
    virtual ~Game();

public:
//Getters
    int getWindowShouldClose();
public:
//Setters
    void setWindowShouldClose();
public:
//Funcs
    void update();
    void render();
};


