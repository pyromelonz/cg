#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "frame_limiter.h"
#include "CGConfig.h"
#include "shader.h"
#include "game_object.h"
#include "components/camera.h"
#include "components/cube.h"
#include "components/transform.h"
#include <memory>

#define WIDTH 800
#define HEIGHT 600

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, height, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    EntityManager::instance().mouse.x = xpos;
    EntityManager::instance().mouse.y = ypos;
}

int main()
{
    srand(time(NULL));
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Super fancy window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    
    Shader shader("assets/shaders/basic.vs", "assets/shaders/basic.fs", nullptr);
   
    /*
    for (int i = 0; i < 300; i++)
    {
        Quad *quad = new Quad(((float)rand() / (float)(RAND_MAX) * 2) - 1.0f, ((float)rand() / (float)(RAND_MAX) * 2) - 1.0f, 0.01f, 0.01f, &shader);
        EntityManager::instance().AddGameObject(quad);
    }*/

    auto& EM = EntityManager::instance();

    {
        auto cam = std::make_unique<Entity>(), cube = std::make_unique<Entity>();
        auto cam_trans = std::make_unique<Transform>();
        cam_trans->pos = CGXYZ(0);
        cam->addComponent(std::move(cam_trans));
        cam->addComponent(std::make_unique<Camera>());
        auto cube_trans = std::make_unique<Transform>();
        cube_trans->pos = CGXYZ(2.0,0.0,0.0);
        cube->addComponent(std::move(cube_trans));
        cube->addComponent(std::make_unique<Cube>(&shader));

        EM.AddGameObject(std::move(cam));
        EM.AddGameObject(std::move(cube));
    }

    FrameLimiter limiter(120);
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
#ifdef __APPLE__
    bool hasWindowBeenFixed = false;
#endif
    while (!glfwWindowShouldClose(window))
    {
        // Black background
        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        EntityManager::instance().Update();

        glfwSwapBuffers(window);
        glfwPollEvents();
#ifdef __APPLE__
        if (!hasWindowBeenFixed)
        {
            hasWindowBeenFixed = true;
            glfwSetWindowPos(window, 50, 50);
        }
#endif

        limiter.next_frame();
    }

    glfwTerminate();
    return 0;
}