#include "Mesh.h"
#include <iostream>

Mesh::Mesh( Vertex* vertexArray, 
            const unsigned& 
            nrVertices, 
            GLuint* indexArray, 
            const unsigned& nrIndices,
            glm::vec3 position,
            glm::vec3 rotation,
            glm::vec3 scale
            )
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;

    this->initVAO(vertexArray, nrVertices, indexArray, nrIndices);
    this->updateModelMatrix();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
}

void Mesh::initVAO(Vertex* vertexArray, const unsigned& nrVertices, GLuint* indexArray, const unsigned& nrIndices)
{
    //set vars
    this->nrVertices = nrVertices;
    this->nrIndices = nrIndices;

    //create VEO
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    //VBO
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->nrVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW);


    //EBO
    glGenBuffers(1, &this->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrIndices * sizeof(GLuint), indexArray, GL_STATIC_DRAW);

    //Enable
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(GLvoid*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    //color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    //texcoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),(GLvoid*)offsetof(Vertex, texcoord));
    glEnableVertexAttribArray(2);

    //Vind VAD
    glBindVertexArray(0);
}

void Mesh::updateUniforms(Shader* shader)
{
    shader->setMat4fv(this->ModelMatrix, "ModelMatrix", GL_FALSE);
}

void Mesh::render(Shader* shader)
{
    //update uniforms
    this->updateModelMatrix();
    this->updateUniforms(shader);

    shader->use();
    
    //binds
    glBindVertexArray(this->VAO);
    
    //render
    glDrawElements(GL_TRIANGLES, this->nrIndices, GL_UNSIGNED_INT, 0);
    
}

void Mesh::update()
{

}

void Mesh::updateModelMatrix()
{
    this->ModelMatrix = glm::mat4(1.f);
    this->ModelMatrix = glm::translate(ModelMatrix, this->position);
    this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
    this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
    this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
    this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
}

//GETTERS
void Mesh::setPostion(const glm::vec3 position)
{
    this->position = position;
}

void Mesh::setRotation(const glm::vec3 rotation)
{
    this->rotation = rotation;
}

void Mesh::setScale(const glm::vec3 scale)
{
    this->scale = scale;
}

//FUNCS
void Mesh::move(const glm::vec3 position)
{
    this->position += position; 
}

void Mesh::rotate(const glm::vec3 rotation)
{
    this->rotation += rotation; 
}

void Mesh::_scale(const glm::vec3 scale)
{
    this->scale += scale;
}
