#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

enum direction 
{
    FORWARD = 0, BACKWARD, LEFT, RIGHT
};


class Camera
{
private:
    glm::mat4 ViewMatrix;

    GLfloat movSpeed;
    GLfloat sens;

    glm::vec3 worldUp;
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

    GLfloat pitch;
    GLfloat yaw;
    GLfloat roll;
   

    void updateCameraVecs();
    
public:
    Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 worldUp);
    ~Camera();

public:
    //getters
    const glm::mat4 getViewMatrix();
    const glm::vec3 getPos();

    void updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY);
    void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY);
    void move(const float& dt, const int direction);

};

