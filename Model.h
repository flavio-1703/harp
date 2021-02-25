#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"

class Model
{
private:
    Material* material;
    //override textures
    Texture* overrideTexDiff;
    Texture* overrideTexSpec;
    std::vector<Mesh*> meshes;
    glm::vec3 pos;

private:
    void updateUniforms();

public:
    Model(glm::vec3 pos, Material* material, Texture* overrideTexDiff, Texture* overrideTexSpec, std::vector<Mesh*> meshes);
    ~Model();

public:
    void update();
    void render(Shader* shader);

public:
    void rotate(const glm::vec3 rotation);
};