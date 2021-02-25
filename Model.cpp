#include "Model.h"

Model::Model(glm::vec3 pos, Material* material, Texture* overrideTexDiff, Texture* overrideTexSpec, std::vector<Mesh*> meshes)
{
    this->pos = pos;
    this->material = material;
    this->overrideTexDiff = overrideTexDiff;
    this->overrideTexSpec = overrideTexSpec;

    for(auto*i : meshes)
    {
        this->meshes.push_back(new Mesh(*i));
    }
}

Model::~Model()
{
    for (auto*&i : this->meshes)
    {
       delete i;
    }
    
}

void Model::render(Shader* shader)
{
    this->updateUniforms();

    this->updateUniforms();

    this->material->sendToShader(*shader);

    shader->use();

    this->overrideTexDiff->bind(0);
    this->overrideTexSpec->bind(1);

    for (auto& i : this->meshes)
    {
        i->render(shader);       
    }
}

void Model::rotate(const glm::vec3 rotation)
{
    for(auto& i : this->meshes)
    {
        i->rotate(rotation);
    }
}