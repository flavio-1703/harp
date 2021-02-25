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
    Game game("Harp", 1280, 720, 4, 0, false);
    
    
    //main loop
    while (!game.getWindowShouldClose())
    {
        game.update();
        game.render();
        
    }

    return 0;
}