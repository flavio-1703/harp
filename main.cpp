#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

//vectex structure
struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texcoord;
};


Vertex vertices[] = 
{
    glm::vec3(0.0f, 0.5f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 1.f),
    glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f),
    glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f)

};

unsigned nrVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] = 
{
    0, 1, 2
};

unsigned nrIndices = sizeof(indices) / sizeof(GLuint);


void updateInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

bool loadShaders(GLuint &program)
{
    bool loadSuccsess = true;
    char infoLog[512];
    GLint success; 

    std::string temp = "";
    std::string src = "";

    std::fstream in_file;

    //vertex
    in_file.open("vertex_core.glsl");

    if(in_file.is_open())
    {
        while (std::getline(in_file, temp))
        {
            src +=temp + "\n";   
        }
        
    }
    else
    {
        std::cout << "Error: LoadShaders: could not open vertex shader" << std::endl;
        loadSuccsess = false;
    }

    in_file.close();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertSrc = src.c_str();
    glShaderSource(vertexShader, 1, &vertSrc, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error, could not compile vertex shader" << std::endl;
        std::cout << infoLog << "\n" << std::endl;
        loadSuccsess = false;
    }
    

    temp = "";
    src = "";

    //fragment
    in_file.open("fragment_core.glsl");
    if (in_file.is_open())
    {
        while (std::getline(in_file, temp))
        {
           src += temp + "\n";
        }
        
    }
    else
    {
        std::cout << "Error: LoadShaders: could not open fragment shader" << std::endl;
        loadSuccsess = false;
        
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* frgSrc = src.c_str();
    glShaderSource(fragmentShader, 1, &frgSrc, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Error: could not compile fragment shader" << std::endl;
        loadSuccsess = false;
    }

    //program
    program = glCreateProgram();

    //attach
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    
    //link
    glLinkProgram(program);


    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "Error: program did no link correctly!" << std::endl;
        std::cout << infoLog << std::endl;
        loadSuccsess = false;
    }

    //end
    glUseProgram(0);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return loadSuccsess;
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

    GLuint core_program;
    if(!loadShaders(core_program))
    {
        glfwTerminate();
    }
    
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

    //main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        
        //update
        updateInput(window);

        //draw
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        //draw

        //program
        glUseProgram(core_program);

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

    //delete program
    glDeleteProgram(core_program);

    //end
    glfwTerminate();

    return 0;
}