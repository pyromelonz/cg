#include "input.h"

Input::Mouse Input::GetMousePosition()
{
    return mouse;
}

void Input::ClearOnceKeys()
{
    for (int i = 0; i < 349; i++)
    {
        keys_once[i] = -1;
    }
}

void Input::SetCursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
    mouse.x = xpos;
    mouse.y = ypos;
}

void Input::SetKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        keys[key] = true;
        keys_once[key] = 1;
    }
    else if (action == GLFW_RELEASE)
    {
        keys[key] = false;
        keys_once[key] = 0;
    }
}

bool Input::GetKeyDown(KeyCode key)
{
    return keys_once[key] == 1;
}

bool Input::GetKeyUp(KeyCode key)
{
    return keys_once[key] == 0;
}

bool Input::GetKey(KeyCode key)
{
    return keys[key];
}
