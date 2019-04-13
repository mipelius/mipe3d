#include "Mipe3DTime.h"
#include "Mipe3DEngine.h" 
#include "Mipe3DLog.h"

#include <SDL.h>

namespace mipe3d
{

float Time::getTime() const
{
    return SDL_GetTicks() / 1000.0f;
}

float Time::getDeltaTime() const
{
    return m_deltaTime;
}

bool Time::startUp()
{
    if (SDL_Init(SDL_INIT_TIMER) < 0)
    {
        MIPE3D_LOG_ERROR(
            std::string("Unable to initialize SDL timer! SDL error: ") +
            SDL_GetError());
        
        return false;
    }
    Uint32 m_timeStampOnLastUpdate = SDL_GetTicks();
    return true;
}
bool Time::shutDown()
{
    SDL_QuitSubSystem(SDL_INIT_TIMER);
    return true;
}

void Time::update()
{
    Uint32 timeStamp = SDL_GetTicks();
    m_deltaTime = (timeStamp - m_timeStampOnLastUpdate) / 1000.0f;
    m_timeStampOnLastUpdate = timeStamp;
}

// ---- singleton accessor ----

const Time& time()
{
    return *(engine().m_time);
}

} // namespace mipe3d