#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 worldUp)
{
    this->ViewMatrix = glm::mat4(1.f);
    
    this->movSpeed = 3.f;
    this->sens = 6.f;
    
    this->worldUp = worldUp;
    this->pos = pos;
    this->right = glm::vec3(0.f);
    this->up = worldUp;

    this->updateCameraVecs();
    this->pitch = 0.f;
    this->yaw = 0.f;
    this->roll = 0.f;
}

Camera::~Camera()
{
}

void Camera::updateCameraVecs()
{   
    //?????????????
    this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->front.y = sin(glm::radians(this->pitch));
    this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

    this->front = glm::normalize(this->front);
    this->right = glm::normalize(glm::cross(this->front, this->worldUp));
    this->up    = glm::normalize(glm::cross(this->right, this->front));
}

const glm::mat4 Camera::getViewMatrix()
{
    this->ViewMatrix = glm::lookAt(this->pos, this->pos + this->front, this->up);
    this->updateCameraVecs();

    return this->ViewMatrix;
}

const glm::vec3 Camera::getPos()
{
    return this->pos;
}

void Camera::updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY)
{
    this->updateMouseInput(dt, offsetX, offsetY);
    
}

void Camera::updateMouseInput(const float& dt, const double& offsetX, const double& offsetY)
{
    //PITCH + YAW
    this->pitch += static_cast<GLfloat>(offsetY * this->sens * dt);
    this->yaw += static_cast<GLfloat>(offsetX * this->sens * dt);

    if(this->pitch >= 80.f)
    {
        this->pitch = 80.f;
    }
    else if(this->pitch < -80.f)
    {
        this->pitch = -80.f;
    }


    if(this->yaw > 360 || this->yaw < -360)
    {
        this->yaw = 0.f;
    }
}

void Camera::move(const float& dt, const int direction)
{
    switch (direction)
    {
    case FORWARD:
    {
        this->pos += this->front * this->movSpeed * dt;
        break;
    }
        
    case BACKWARD:
    {
        this->pos -= this->front * this->movSpeed * dt;
        break;
    }
    case LEFT:
    {
        this->pos -= this->right * this->movSpeed * dt;
    }
    
    case RIGHT:
    {
        this->pos += this->right * this->movSpeed * dt;
        break;
    }
    default:
        break;
    }
}