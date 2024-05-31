#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "frame_limiter.h"
#include "CGConfig.h"
#include "shader.h"
#include "game_object.h"
#include "input.h"

#define WIDTH 800
#define HEIGHT 600

static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

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
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

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
        Input::instance().ClearOnceKeys();
        limiter.next_frame();
    }

    glfwTerminate();
    return 0;
}

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