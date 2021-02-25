#include "Game.h"


Game::Game(const char* title, const int WIDTH, const int HEIGHT, const int GL_VER_MAJOR, const int GL_VER_MINOR, bool resizable)
    : WIN_WIDTH(WIDTH), WIN_HEIGHT(HEIGHT), GL_VER_MAJOR(GL_VER_MAJOR), GL_VER_MINOR(GL_VER_MINOR),
    camera(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f))
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

    this->dt = 0.0f;
    this->curTime = 0.f;
    this->lastTime = 0.f;

    this->lastMouseX = 0.0;
    this->lastMouseY = 0.0;
    this->mouseX = 0.0;
    this->mouseY = 0.0;
    this->mouseOffsetX = 0.0;
    this->mouseOffsetY = 0.0;
    this->firstMouse = true;


    this->initGLFW();
    this->initWindow(title, resizable);
    this->initGLEW();
    this->initGLOptions();
    this->initMatrices();
    this->initShaders();
    this->initTextures();
    this->initMaterials();
    this->initLights();
    this->initUniforms();
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

    for(auto*& i : this->models)
    {
        delete i;
    }
    
    for (size_t i = 0; i < this->lights.size(); i++)
    {
        delete this->lights[i];
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

    //INPUT
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void Game::update()
{
    this->updateDt();
    this->updateInput();

    this->models[0]->rotate(glm::vec3(0.f, 1.f, 0.f));

    //this->meshes[0]->rotate(glm::vec3(0.f, 1.f, 0.f));
}

void Game::render()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    this->updateUniforms();

    // this->materials[MAT_1]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);

    // this->shaders[SHADER_CORE_PROGRAM]->use();

    // this->textures[TEX_PUSHEEN0]->bind(0);
    // this->textures[TEX_CONTAINER]->bind(1);

    this->models[0]->render(this->shaders[SHADER_CORE_PROGRAM]);


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

//SHADERS INIT
void Game::initShaders()
{
    this->shaders.push_back(new Shader(this->GL_VER_MAJOR, this->GL_VER_MINOR, "vertex_core.glsl", "fragment_core.glsl", ""));
}

void Game::initTextures()
{
    this->textures.push_back(new Texture("pusheen.png", GL_TEXTURE_2D));

    this->textures.push_back(new Texture("container.png", GL_TEXTURE_2D));
}

//MATERIAL INIT
void Game::initMaterials()
{
    this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), 0, 1));
}

//LIGHTS INIT
void Game::initLights()
{
    this->lights.push_back(new glm::vec3(0.f, 0.f, 1.f));
}

void Game::initUniforms()
{
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix", GL_FALSE);
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix", GL_FALSE);

    this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos");
    
}

void Game::updateUniforms()
{

    //send the updated matrix to the shader
    this->ViewMatrix = this->camera.getViewMatrix();
    //set thhe updated view
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix", false);
    this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPos(), "cameraPos");

    glfwGetFramebufferSize(this->window, &this->fbHeight, &this->fbHeight);

    this->ProjectionMatrix = glm::perspective(
        glm::radians(this->fov), 
        static_cast<float>(this->fbWidth) / this->fbHeight, 
        this->nearPlane, 
        this->farPlane);

    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ProjectionMatrix, "ProjectionMatrix", false);
}

//INPUT UPDATE
void Game::updateKeyoardInput()
{
    //THESE ARE THE BASIC INPUT FOR THE CAMERA MOVEMENT
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(this->window, GLFW_TRUE);
    }
    if(glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
    {
        this->camera.move(this->dt, FORWARD);
    }
    if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
    {
        this->camera.move(this->dt, BACKWARD);
    }
    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
    {
        this->camera.move(this->dt, LEFT);
    }
    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
    {
        this->camera.move(this->dt, RIGHT);
    }
}

void Game::updateMouseInput()
{
    glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

    if(this->firstMouse)
    {
        this->lastMouseX = this->mouseX;
        this->lastMouseY = this->mouseY;
        this->firstMouse = false;
    }

    this->mouseOffsetX = this->mouseX - this->lastMouseX;
    this->mouseOffsetY = this->lastMouseY - this->mouseY;

    this->lastMouseX = this->mouseX;
    this->lastMouseY = this->mouseY;
}

void Game::updateInput()
{
    glfwPollEvents();

    this->updateKeyoardInput();
    this->updateMouseInput();
    this->camera.updateInput(dt, -1, this->mouseOffsetX, this->mouseOffsetY);
}

void Game::updateDt()
{
    /*
        We get the difference in time in between updates and multiply it
        with our movement so that it wont be tied to the framerate
    */
    this->curTime = static_cast<float>(glfwGetTime());
    this->dt = this->curTime - this->lastTime;
    this->lastTime = this->curTime;
}

void Game::initModels()
{
    this->meshes.push_back(new Mesh(&Cube(), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshes.push_back(new Mesh(&Pyramid(), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));

    this->models.push_back(new Model(glm::vec3(0.f), this->materials[0], this->textures[1], this->textures[TEX_CONTAINER],this->meshes));

    for(auto*& i : this->meshes)
        delete i;


    this->meshes.clear();
}