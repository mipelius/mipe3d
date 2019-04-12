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

Keyboard::Keyboard()
{
}
Keyboard::~Keyboard()
{
}

bool Keyboard::isKeyDown(Key key) const
{
    return false;
}

bool Keyboard::keyPressed(Key key) const
{
    return false;
}

bool Keyboard::keyReleased(Key key) const
{
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