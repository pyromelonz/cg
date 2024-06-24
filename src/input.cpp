#include <algorithm>

#include "input.h"

Mouse Input::GetMousePosition()
{
    return mouse;
}

void Input::ClearOnceKeys()
{
    std::fill_n(keys_once, sizeof(keys_once), -1);
    std::fill_n(mouse_buttons_once, sizeof(mouse_buttons_once), -1);
}

void Input::SetCursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
    mouse.x = xpos;
    mouse.y = ypos;
}

void Input::SetKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key > 348)
        return; // Some bizzare key was pressed
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

void Input::SetMouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    if (button > LAST_BUTTON)
        return; // Some bizzare button was pressed
    if (action == GLFW_PRESS)
    {
        mouse_buttons[button] = true;
        mouse_buttons_once[button] = 1;
    }
    else if (action == GLFW_RELEASE)
    {
        mouse_buttons[button] = false;
        mouse_buttons_once[button] = 0;
    }
}

bool Input::GetKeyDown(KeyCode key)
{
    return (key <= 348) && (keys_once[(size_t)key] == 1);
}

bool Input::GetKeyUp(KeyCode key)
{
    return (key <= 348) && (keys_once[(size_t)key] == 0);
}

bool Input::GetKey(KeyCode key)
{
    return (key <= 348) && keys[(size_t)key];
}

bool Input::GetMouseButtonDown(MouseButton button)
{
    return (button <= LAST_BUTTON) && (mouse_buttons_once[(size_t)button] == 1);
}

bool Input::GetMouseButtonUp(MouseButton button)
{
    return (button <= LAST_BUTTON) && (mouse_buttons_once[(size_t)button] == 0);
}

bool Input::GetMouseButton(MouseButton button)
{
    return (button <= LAST_BUTTON) && mouse_buttons[(size_t)button];
}

Input::Input()
{
    std::fill_n(keys_once, sizeof(keys_once), -1);
    std::fill_n(mouse_buttons_once, sizeof(mouse_buttons_once), -1);
}