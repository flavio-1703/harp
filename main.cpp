#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Texture.h"
#include "Game.h"

//vectex structure
struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texcoord;
};


void updateInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}



void updateInput(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale)
{
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        position.z -= 0.01f;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        position.z += 0.01f;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        position.x -= 0.01f;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        position.x += 0.01f;
    }
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        rotation.y -= 1.f;
    }
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        rotation.y += 1.f;
    }
}

int main(void)
{
    //glfw
    glfwInit();

    if(!glfwInit())
    {
        std::cout << "glfw did not init" << std::endl;
        return -1;
    }

    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;
    
    int frameBufferWidth = 0;
    int frameBufferHeight = 0;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Harp", NULL, NULL);

    if(window == NULL)
    {
        std::cout << "window did not open" << std::endl;
    }

    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
    glViewport(0, 0, frameBufferWidth, frameBufferWidth);

    glfwMakeContextCurrent(window);

    //glew
    glewExperimental = GL_TRUE;

    //error
    if(glewInit() != GLEW_OK)
    {
        std::cout << "Error Glew init failed" << std::endl;
        glfwTerminate();
    }

    //GL options
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    Shader core_program("vertex_core.glsl", "fragment_core.glsl", "");

    // GLuint core_program;
    // if(!loadShaders(core_program))
    // {
    //     glfwTerminate();
    // }
    
    //VBO
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //VBO
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //EBO
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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


    
    //values
    glm::vec3 position(0.f);
    glm::vec3 rotation(0.f);
    glm::vec3 scale(1.f);
    //modelmatrix
    glm::mat4 ModelMatrix(1.f);
    ModelMatrix = glm::translate(ModelMatrix, position);
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
    ModelMatrix = glm::scale(ModelMatrix, scale);


    //view matrix
    glm::vec3 camPosition(0.f, 0.f, 2.f);
    glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f);
    glm::vec3 camFront = glm::vec3(0.f, 0.f, -1.f);

    glm::mat4 ViewMatrix(1.f);

    ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp);

    
    //projection matrix
    float fov = 90.f;
    float nearPlane = 0.1f;
    float farPlane = 500.f;
    glm::mat4 ProjectionMatrix(1.f);

    ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(frameBufferWidth) / frameBufferHeight, nearPlane, farPlane);


    core_program.setMat4fv(ModelMatrix, "ModelMatrix", GL_FALSE);
    core_program.setMat4fv(ViewMatrix, "ViewMatrix", GL_FALSE);
    core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix", GL_FALSE);

    
    glUseProgram(0);
    
    
    //main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        updateInput(window, position, rotation, scale);
        //update
        updateInput(window);

        //draw
        

        //draw
        Game game("HARP", 1280, 720, 4, 0, false);
        

        //update
        
        
        //move rotate scale

        ModelMatrix = glm::mat4(1.f);
        ModelMatrix = glm::translate(ModelMatrix, position);
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
        ModelMatrix = glm::scale(ModelMatrix, scale);

        core_program.setMat4fv(ModelMatrix, "ModelMatrix", GL_FALSE);

        ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(frameBufferWidth) / frameBufferHeight, nearPlane, farPlane);

        core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix", GL_FALSE);   
        //program
        core_program.use();

        //bind vao
        glBindVertexArray(VAO);

        //draw
        glDrawElements(GL_TRIANGLES, nrIndices, GL_UNSIGNED_INT, 0);


        //end draw

        glfwSwapBuffers(window);
        glFlush();
    }
    
    //end of program
    glfwDestroyWindow(window);
    glfwTerminate();


    //end
    glfwTerminate();

    return 0;
}