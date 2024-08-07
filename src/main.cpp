#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "frame_limiter.h"
#include "CGConfig.h"
#include "shader.h"
#include "components/camera.h"
#include "input.h"
#include "entity_manager.h"
#include "components/cube.h"
#include "components/transform.h"
#include "components/controller.h"

#define WIDTH 1024
#define HEIGHT 768

#ifndef __APPLE__
#ifndef NDEBUG
void GLAPIENTRY
MessageCallback(GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar *message,
                const void *userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, severity, message);
}
#endif
#endif
static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

int main()
{
    // srand(time(NULL));
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#endif

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifndef NDEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

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
#ifndef __APPLE__
#ifndef NDEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
#endif
#endif
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    auto &EM = EntityManager::instance();

    auto cam = std::make_unique<Entity>(), cube = std::make_unique<Entity>();
    Shader *shader = new Shader("assets/shaders/basic.vs", "assets/shaders/basic.fs");

    cam->addComponent(new Transform(glm::vec3(0.0f, 0.0f, 5.0f)));
    cam->addComponent(new Camera(WIDTH, HEIGHT));
    cam->addComponent(new Controller);
    EM.AddEntity(std::move(cam));

    cube->addComponent(new Transform);
    cube->addComponent(new Cube(shader));

    EM.AddEntity(std::move(cube));

    FrameLimiter limiter(120);
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    EM.Init();

    //lock cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    double delta_t = 0;

#ifdef __APPLE__
    bool hasWindowBeenFixed = false;
#endif
    while (!glfwWindowShouldClose(window))
    {
        // Black background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        EntityManager::instance().Update(delta_t);
        glfwSwapBuffers(window);
        glfwPollEvents();
#ifdef __APPLE__
        if (!hasWindowBeenFixed)
        {
            hasWindowBeenFixed = true;
            glfwSetWindowPos(window, 50, 50);
        }
#endif
        Input::instance().ClearOnceKeys();
        delta_t = limiter.next_frame();
    }

    glfwTerminate();
    return 0;
}

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    Input::instance().SetCursorPosCallback(window, xpos, ypos);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Input::instance().SetKeyCallback(window, key, scancode, action, mods);
}

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    Input::instance().SetMouseButtonCallback(window, button, action, mods);
}