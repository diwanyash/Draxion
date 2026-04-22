#pragma once

namespace Draxion
{
	using KeyCode = unsigned int;

	namespace Key
	{
		enum : KeyCode
		{
			// KeyBoard Keys
			VK_SPACE = 32,
			
			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90,

			VK_RETURN = 257,
			VK_TAB = 258,
			VK_BACK = 259,
			VK_SHIFT = 340,
			VK_CONTROL = 341,
			VK_MENU = 342,

			VK_RIGHT = 262,
			VK_LEFT = 263,
			VK_UP = 264,
			VK_DOWN = 265,

			VK_ESCAPE = 256,

			// Mouse Keys
			MOUSE_BUTTON_LEFT = 0,
			MOUSE_BUTTON_RIGHT = 1,
			MOUSE_BUTTON_MIDDLE = 2,
		};
	}
}