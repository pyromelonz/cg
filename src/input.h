#pragma once
#include <GLFW/glfw3.h>

enum KeyCode
{
    Backspace = 8,
    Tab = 9,
    Enter = 13,
    Pause = 19,
    CapsLock = 20,
    Esc = 27,
    Spacebar = 32,
    PageUp = 33,
    PageDown = 34,
    End = 35,
    Home = 36,
    Left = 37,
    Up = 38,
    Right = 39,
    Down = 40,
    Insert = 45,
    Delete = 46,
    Key_0 = 48,
    Key_1 = 49,
    Key_2 = 50,
    Key_3 = 51,
    Key_4 = 52,
    Key_5 = 53,
    Key_6 = 54,
    Key_7 = 55,
    Key_8 = 56,
    Key_9 = 57,
    Key_a = 65,
    Key_b = 66,
    Key_c = 67,
    Key_d = 68,
    Key_e = 69,
    Key_f = 70,
    Key_g = 71,
    Key_h = 72,
    Key_i = 73,
    Key_j = 74,
    Key_k = 75,
    Key_l = 76,
    Key_m = 77,
    Key_n = 78,
    Key_o = 79,
    Key_p = 80,
    Key_q = 81,
    Key_r = 82,
    Key_s = 83,
    Key_t = 84,
    Key_u = 85,
    Key_v = 86,
    Key_w = 87,
    Key_x = 88,
    Key_y = 89,
    Key_z = 90,
    Windows = 91,
    ApplicationKey = 93,
    Numpad_0 = 96,
    Numpad_1 = 97,
    Numpad_2 = 98,
    Numpad_3 = 99,
    Numpad_4 = 100,
    Numpad_5 = 101,
    Numpad_6 = 102,
    Numpad_7 = 103,
    Numpad_8 = 104,
    Numpad_9 = 105,
    Asterisk = 106,
    PlusSign = 107,
    MinusSign = 109,
    Numpad_Period = 110,
    Numpad_Slash = 111,
    F1 = 112,
    F2 = 113,
    F3 = 114,
    F4 = 115,
    F5 = 116,
    F6 = 117,
    F7 = 118,
    F8 = 119,
    F9 = 120,
    F10 = 121,
    F11 = 122,
    F12 = 123,
    NumLock = 144,
    ScrollLock = 145,
    Semicolon = 186,
    EqualsSign = 187,
    Comma = 188,
    Hyphen = 189,
    Period = 190,
    Slash = 191,
    GraveAccent = 192,
    OpenBracket = 219,
    BackSlash = 220,
    CloseBracket = 221,
    Quotes = 222,
    Escape = GLFW_KEY_ESCAPE, //256
    Shift = GLFW_KEY_LEFT_SHIFT, //340
    LAST_KEY = Shift
};
enum MouseButton
{
    LeftButton = 0,
    RightButton = 1,
    MiddleButton = 2,
    Button_4 = 3,
    Button_5 = 4,
    Button_6 = 5,
    Button_7 = 6,
    Button_8 = 7,
    LAST_BUTTON = Button_8
};

struct Mouse
{
    double x;
    double y;
};

class Input
{
public:
    static Input &instance()
    {
        static Input instance;
        return instance;
    }
    // Get the current mouse position in screenspace
    Mouse GetMousePosition();
    // Clears the keys in the keys_once array since they are supposed to be used only once
    void ClearOnceKeys();
    // Callback for GLFW to set the mouse position
    void SetCursorPosCallback(GLFWwindow *window, double xpos, double ypos);
    // Callback for GLFW to set the key pressed/released
    void SetKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    // Callback for GLFW to set the mouse button pressed/released
    void SetMouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    // Check if a key is pressed once
    bool GetKeyDown(KeyCode key);
    // Check if a key is released once
    bool GetKeyUp(KeyCode key);
    // Check if a key is pressed continuously
    bool GetKey(KeyCode key);
    // Check if a mouse button is pressed once
    bool GetMouseButtonDown(MouseButton button);
    // Check if a mouse button is released once
    bool GetMouseButtonUp(MouseButton button);
    // Check if a mouse button is pressed continuously
    bool GetMouseButton(MouseButton button);

private:
    Input();
    Input(Input const &) = delete;
    void operator=(Input const &) = delete;

    Mouse mouse;
    char mouse_buttons_once[8];
    bool mouse_buttons[8];
    char keys_once[349];
    bool keys[349];
};
