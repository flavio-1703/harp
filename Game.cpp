#include "Game.h"


Game::Game(const char* title, const int WIDTH, const int HEIGHT, const int GL_VER_MAJOR, const int GL_VER_MINOR, bool resizable)
    : WIN_WIDTH(WIDTH), WIN_HEIGHT(HEIGHT), GL_VER_MAJOR(GL_VER_MAJOR), GL_VER_MINOR(GL_VER_MINOR)
{
    this->window = nullptr;
    this->fbWidth = WIN_WIDTH;
    this->fbHeight = WIN_HEIGHT;

    this->camPos = glm::vec3(0.f, 0.f, 2.f);
    this->woldUp = glm::vec3(0.f, 1.f, 0.f);
    this->camFront = glm::vec3(0.f, 0.f, -1.f);
    
    //projection matrix
    this->fov = 90.f;
    this->nearPlane = 0.1f;
    this->farPlane = 500.f;
    this->ProjectionMatrix = glm::mat4(1.f);

    this->initGLFW();
    this->initWindow(title, resizable);
    this->initGLEW();
    this->initGLOptions();
    this->initMatrices();
}

Game::~Game()
{
    glfwDestroyWindow(this->window);
    glfwTerminate();

    for (size_t i = 0; i < this->shaders.size(); i++)
    {
        delete this->shaders[i];
    }

    for (size_t i = 0; i < this->textures.size(); i++)
    {
        delete this->textures[i];
    }

    for (size_t i = 0; i < this->materials.size(); i++)
    {
        delete this->materials[i];
    }

    for (size_t i = 0; i < this->meshes.size(); i++)
    {
        delete this->meshes[i];
    }
    
}

//Priv
void Game::initGLFW()
{
    if (glfwInit() == GLFW_FALSE)
    {
        std::cout << "ERROR: GLFW: glfwInit() FAILED!" << std::endl;
        glfwTerminate();
    }
}

void Game::initWindow(const char* title, bool resizable)
{
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VER_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VER_MINOR);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


    this->window = glfwCreateWindow(this->WIN_WIDTH, this->WIN_HEIGHT, title, NULL, NULL);

    if(this->window == nullptr)
    {
        std::cout << "ERROR: GLFW WINDOW: WINDOW DID NOT INIT!" << std::endl;
        glfwTerminate();
    }

    glfwGetFramebufferSize(this->window, &this->fbWidth, &this->fbHeight);
    glViewport(0, 0, this->fbWidth, this->fbHeight);

    glfwMakeContextCurrent(this->window);

}

void Game::initGLEW()
{
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK)
    {
        std::cout << "ERROR: GLEW: glewInit() FAILED!" << std::endl;
    }
}

void Game::initGLOptions()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void Game::update()
{
    glfwPollEvents();
}

void Game::render()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glfwSwapBuffers(this->window);
    glFlush();

    //reset
    glBindVertexArray(0);
    glUseProgram(0);
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);


}

int Game::getWindowShouldClose()
{
    return glfwWindowShouldClose(this->window);
}

void Game::setWindowShouldClose()
{
    glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

void Game::initMatrices()
{
    this->ViewMatrix = glm::mat4(1.f);
    this->ViewMatrix = glm::lookAt(this->camPos , this->camPos + this->camFront, this->woldUp);

    this->ProjectionMatrix = glm::perspective(
        glm::radians(this->fov), 
        static_cast<float>(this->fbWidth) / this->fbHeight, 
        this->nearPlane, 
        this->farPlane);
}

void Game::initShaders()
{
    this->shaders.push_back(new Shader(this->GL_VER_MAJOR, this->GL_VER_MINOR, "dasdsa", "sdas"));
}

void Game::initTextures()
{
    this->textures.push_back(new Texture(" ", GL_TEXTURE_2D, 0));
}

void Game::initMaterials()
{
    this->materials.push_back(new Material(glm::vec3(0.1f,), glm::vec3(1.f), glm::vec3(1.f), ));
}