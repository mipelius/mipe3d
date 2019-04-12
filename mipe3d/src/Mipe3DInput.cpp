#include "Mipe3DInput.h"
#include "Mipe3DEngine.h"
#include "Mipe3DLog.h"

#include <cassert>
#include <SDL_keyboard.h>
#include <SDL_keycode.h>
#include <SDL_mouse.h>

namespace mipe3d
{

// ------------------------ keyboard ------------------------

static Key convertSDLScancodeToKey(SDL_Scancode scancode)
{
    switch (scancode)
    {
    case SDL_SCANCODE_UP: return Key::UP;
    case SDL_SCANCODE_DOWN: return Key::DOWN;
    case SDL_SCANCODE_LEFT: return Key::LEFT;
    case SDL_SCANCODE_RIGHT: return Key::RIGHT;
    case SDL_SCANCODE_W: return Key::W;
    case SDL_SCANCODE_S: return Key::S;
    case SDL_SCANCODE_A: return Key::A;
    case SDL_SCANCODE_D: return Key::D;
    case SDL_SCANCODE_SPACE: return Key::SPACE;
    case SDL_SCANCODE_ESCAPE: return Key::ESC;
    default:
        return Key::UNKNOWN;
    }
}

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

bool Keyboard::keyPressed(Key key) const
{
    assert(false && "Keyboard::keyPressed(...) not implemented");
    return false;
}

bool Keyboard::keyReleased(Key key) const
{
    assert(false && "Keyboard::keyReleased(...) not implemented");
    return false;
}

// ------------------------ mouse ------------------------

Mouse::Mouse() 
{
}
Mouse::~Mouse() 
{
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
const Mouse& Input::mouse() const
{
    return *m_mouse;
}

const Input& input()
{
    return *(engine().m_input);
}


} // namespace mipe3d