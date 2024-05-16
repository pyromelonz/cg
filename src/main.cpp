#include <iostream>

#include "global_includes.h"
#include "frame_limiter.h"
#include "CGConfig.h"
#include "object_manager.h"
#include "shader.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(800, 600, "Super fancy window", NULL, NULL);
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

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader shader("assets/shaders/basic.vs", "assets/shaders/basic.fs", nullptr);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f,  // right
        0.0f, 0.5f, 0.0f    // top
    };

    ObjectManager object_manager;
    object_manager.add_object(GFX_Object(vertices,9));

    object_manager.initialise_objects();

    FrameLimiter limiter;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
#ifdef __APPLE__
    bool hasWindowBeenFixed = false;
#endif
    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        shader.Use();
        object_manager.bind_current_vao();
        //glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);

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