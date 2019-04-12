#include "Mipe3DInput.h"
#include "Mipe3DEngine.h"
#include "Mipe3DLog.h"
#include "Mipe3DRenderSystem.h"

#include <cassert>
#include <SDL_keyboard.h>
#include <SDL_keycode.h>
#include <SDL_mouse.h>
#include <SDL_events.h>

namespace mipe3d
{

// ------------------------ keyboard ------------------------

static SDL_Keycode convertKeyToSDLScancode(Key key)
{
    switch (key)
    {
    case Key::UP: return SDL_SCANCODE_UP;
    case Key::DOWN: return SDL_SCANCODE_DOWN;
    case Key::LEFT: return SDL_SCANCODE_LEFT;
    case Key::RIGHT: return SDL_SCANCODE_RIGHT;
    case Key::W: return SDL_SCANCODE_W;
    case Key::S: return SDL_SCANCODE_S;
    case Key::A: return SDL_SCANCODE_A;
    case Key::D: return SDL_SCANCODE_D;
    case Key::SPACE: return SDL_SCANCODE_SPACE;
    case Key::ESC: return SDL_SCANCODE_ESCAPE;
    default:
        return SDL_SCANCODE_UNKNOWN;
    }
}

Keyboard::Keyboard()
{
}
Keyboard::~Keyboard()
{
}

bool Keyboard::isKeyDown(Key key) const
{
    auto scancode = convertKeyToSDLScancode(key);

    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (scancode == SDL_SCANCODE_UNKNOWN)
    {
        return false;
    }
    else
    {
        return state[scancode];
    }
}

// ------------------------ mouse ------------------------

Mouse::Mouse() 
{
}
Mouse::~Mouse() 
{
}

void Mouse::setCursorVisible(bool visible)
{
    SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
}

void Mouse::setCursorPosition(glm::ivec2 position)
{
    SDL_WarpMouseInWindow(
        renderSystem().m_window,
        position.x,
        position.y);
}

glm::ivec2 Mouse::getCursorPosition() const
{
    glm::ivec2 result;
    SDL_GetMouseState(&result.x, &result.y);

    return result;
}

bool Mouse::isLeftButtonDown() const
{
    auto state = SDL_GetMouseState(NULL, NULL);

    return state & SDL_BUTTON(SDL_BUTTON_LEFT);
}

bool Mouse::isRightButtonDown() const
{
    auto state = SDL_GetMouseState(NULL, NULL);

    return state & SDL_BUTTON(SDL_BUTTON_RIGHT);
}


// ------------------------ input ------------------------

Input::Input()
{
    m_keyboard = new Keyboard();
    m_mouse = new Mouse();
}

Input::~Input()
{
    delete m_keyboard;
    delete m_mouse;
}


bool Input::startUp()
{
    return true;
}
bool Input::shutDown()
{
    return true;
}
void Input::update()
{
}

const Keyboard& Input::keyboard() const
{
    return *m_keyboard;
}
Mouse& Input::mouse() const
{
    return *m_mouse;
}

Input& input()
{
    return *(engine().m_input);
}


} // namespace mipe3d