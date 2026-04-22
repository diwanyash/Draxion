#pragma once
#include "../Core/Core.h"
#include <utility>

namespace Draxion
{

	class DRX_API Input
	{
	public:
		static bool IsKeyPressed(int KeyCode);
		static bool IsMouseButtonPressed( int Button );
		static std::pair<float,float> GetMousePosition();
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int Button) = 0;
		virtual std::pair<float,float> GetMousePositionImpl() = 0;
	private:
		static Input* s_Instatnce;
	};

}