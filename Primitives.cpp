#include "Primitives.h"

Primitives::Primitives()
{
}

Primitives::~Primitives()
{
}

void Primitives::set(const Vertex* vertices, const unsigned nrVertices, const GLuint* indices, const unsigned nrIndeces)
{
    for (size_t i = 0; i < nrVertices; i++)
    {
        this->vertices.push_back(vertices[i]);
    }
    
    for (size_t i = 0; i < nrIndeces; i++)
    {
        this->indices.push_back(indices[i]);
    }
    
}

Vertex* Primitives::getVertices()
{
    return this->vertices.data();
}

GLuint* Primitives::getIndices()
{
    return this->indices.data();
}

const unsigned Primitives::getNrVertices()
{
    return this->vertices.size();
}

const unsigned Primitives::getNrIndices()
{
    return this->indices.size();
}

//QUAD
Quad::Quad() : Primitives()
{
    Vertex vertices[] = 
    {
        glm::vec3(-0.5f, 0.5f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 0.f, 0.f),
        glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, 0.f),
        glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, 0.f),
        glm::vec3(0.5f, 0.5f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, 0.f)


    };

    unsigned nrVertices = sizeof(vertices) / sizeof(Vertex);

    GLuint indices[] = 
    {
        0, 1, 2,
        0, 2, 3
    };

    unsigned nrIndices = sizeof(indices) / sizeof(GLuint);

    this->set(vertices, nrVertices, indices, nrIndices);
}


//TRIANGLE
Triangle::Triangle() : Primitives()
{
    Vertex vertices[] = 
    {
        glm::vec3(-0.5f, 0.5f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 0.f, 0.f),
        glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, 0.f),
        glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, 0.f),
        glm::vec3(0.5f, 0.5f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, 0.f)


    };

    unsigned nrVertices = sizeof(vertices) / sizeof(Vertex);

    GLuint indices[] = 
    {
        0, 1, 2
    };

    unsigned nrIndices = sizeof(indices) / sizeof(GLuint);

    this->set(vertices, nrVertices, indices, nrIndices);
}

//PYRAMID
Pyramid::Pyramid() : Primitives()
{
    Vertex vertices[] = 
    {
        glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),

			//Triangle left
			glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),

			//Triangle back
			glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),

			//Triangles right
			glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		this->set(vertices, nrOfVertices, nullptr, 0);

};

//CUBE

Cube::Cube() : Primitives()
{
    Vertex vertices[] =
    {
        //Position								//Color							//Texcoords					//Normals
        glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),

        glm::vec3(0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, -1.f),
        glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
        glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
        glm::vec3(-0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, -1.f)
    };
    unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

    GLuint indices[] =
    {
        0, 1, 2,
        0, 2, 3,

        7, 6, 1,
        7, 1, 0,

        4, 5, 6,
        4, 6, 7,

        3, 2, 5,
        3, 5, 4
    };
    unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

    this->set(vertices, nrOfVertices, indices, nrOfIndices);
}
