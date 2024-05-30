#pragma once
#include <GLFW/glfw3.h>

class Input
{
public:
    static Input &instance()
    {
        static Input instance;
        return instance;
    }

    struct Mouse
    {
        double x;
        double y;
    };

    Mouse mouse;

    // Callback for GLFW to set the mouse position
    void SetCursorPosCallback(GLFWwindow *window, double xpos, double ypos);

private:
    Input(){};
    Input(Input const &) = delete;
    void operator=(Input const &) = delete;
};