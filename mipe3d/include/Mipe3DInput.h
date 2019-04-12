#pragma once

#include "apidef.h"
#include <map>

struct SDL_KeyboardEvent;

namespace mipe3d
{

// ------------------------ keyboard ------------------------

enum class Key
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    W,
    S,
    A,
    D,
    SPACE,
    ESC,
    // ... implement the rest if necessary
    UNKNOWN
};

class Keyboard
{
    friend class Input;

public:
    // return true, if the key currently down
    MIPE3D_API bool isKeyDown(Key key) const;

    // return true, if the user pressed the key during the frame
    MIPE3D_API bool keyPressed(Key key) const;

    // return true, if the user released the key during the frame
    MIPE3D_API bool keyReleased(Key key) const;

private:
    Keyboard();
    ~Keyboard();
    Keyboard(const Keyboard& other) = delete;
    Keyboard& operator=(const Keyboard& other) = delete;
};

// ------------------------ mouse ------------------------

class Mouse
{
    friend class Input;

public:
    // ...

private:
    Mouse();
    ~Mouse();
    Mouse(const Mouse& other) = delete;
    Mouse& operator=(const Mouse& other) = delete;
};

// ------------------------ input ------------------------
class Input
{
friend class Engine;

public:
    MIPE3D_API const Keyboard& keyboard() const;
    MIPE3D_API const Mouse& mouse() const;

private:
    Input();
    ~Input();
    Input(const Input& other) = delete;
    Input& operator=(const Input& other) = delete;

    Keyboard* m_keyboard;
    Mouse* m_mouse;

    bool startUp();
    bool shutDown();
    void update();
};

// ---- singleton accessor ----

MIPE3D_API const Input& input();

} // namespace mipe3d