// Copyright (c) Miika Pelkonen. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "apidef.h"

#include <ext/vector_int2.hpp>

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
    MIPE3D_API bool isKeyDown(Key key) const;

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
    MIPE3D_API void setCursorVisible(bool visible);
    MIPE3D_API void setCursorPosition(glm::ivec2 position);
    MIPE3D_API glm::ivec2 getCursorPosition() const;
    MIPE3D_API bool isLeftButtonDown() const;
    MIPE3D_API bool isRightButtonDown() const;

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
    MIPE3D_API Mouse& mouse() const;

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

MIPE3D_API Input& input();

} // namespace mipe3d