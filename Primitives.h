#pragma once

#include <GL/glew.h>
#include <vector>
#include "Vertex.h"
#include <glm/glm.hpp>
#include <glm/vec2.hpp>

class Primitives
{
private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

public:
    Primitives();
    virtual ~Primitives();

public:
    void set(const Vertex* vertices, const unsigned nrVertices, const GLuint* indices, const unsigned nrIndeces);
    Vertex* getVertices();
    GLuint* getIndices();
    const unsigned getNrVertices();
    const unsigned getNrIndices();

};


class Quad : public Primitives 
{
public:
    Quad();

private:
};

class Triangle : public Primitives
{
public:
    Triangle();
private:
};

class Pyramid : public Primitives
{
public:
    Pyramid();
};

class Cube : public Primitives
{
public:
    Cube();
};