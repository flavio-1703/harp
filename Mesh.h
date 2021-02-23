#pragma once

#include "Vertex.h"
#include <vector>
#include <GL/glew.h>
#include "Shader.h"
#include "Primitives.h"


class Mesh
{
private:
    unsigned nrVertices;
    unsigned nrIndices;

private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 ModelMatrix;

private:
    void initVAO(Vertex* vertexArray, const unsigned& nrVertices, GLuint* indexArray, const unsigned& nrIndices);
    void initVAO(Primitives* primitive);
    void initModelMatrix();
public:
    Mesh(Vertex* vertexArray, const unsigned& nrVertices, GLuint* indexArray, const unsigned& nrIndices, glm::vec3 position,
            glm::vec3 rotation,
            glm::vec3 scale);
    Mesh(Primitives* primitive, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    ~Mesh();

public:
    void update();
    void render(Shader* shader);
    void updateUniforms(Shader* shader);
    void updateModelMatrix();

public:
    //setters
    void setPostion(const glm::vec3 position);
    void setRotation(const glm::vec3 rotation);
    void setScale(const glm::vec3 scale);

public:
    //funcs
    void move(const glm::vec3 position);
    void rotate(const glm::vec3 rotation);
    void _scale(const glm::vec3 scale);

};