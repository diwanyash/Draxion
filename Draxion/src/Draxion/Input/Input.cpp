#include "Input.h"
#include "Draxion/Platform/Windows/OpenGL/WindowsInput.h"

namespace Draxion
{
    Input* Input::s_Instatnce = new WindowsInput();
    
    bool Input::IsKeyPressed(int KeyCode)
    {
        return s_Instatnce->IsKeyPressedImpl( KeyCode );
    }
    bool Input::IsMouseButtonPressed(int Button)
    {
        return s_Instatnce->IsMouseButtonPressedImpl( Button );
    }
    std::pair<float, float> Input::GetMousePosition()
    {
        return s_Instatnce->GetMousePositionImpl();
    }
}