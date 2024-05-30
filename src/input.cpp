#include "input.h"

void Input::SetCursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
    mouse.x = xpos;
    mouse.y = ypos;
}