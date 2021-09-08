#pragma once

namespace GLCore 
{
	class GLWindowEventHandler
	{
	public:
		virtual void onResize(
			const int width, 
			const int height) = 0;

		virtual void onKey(
			const int key, 
			const int scancode, 
			const int action, 
			const int mods) = 0;

		virtual void onIdle(const float deltaTime) = 0;

		virtual void onMouseButton(
			const int button, 
			const int action, 
			const int mods) = 0;

		virtual void onMouseMove(
			const double xPos, 
			const double yPos) = 0;

		virtual void onScroll(const double delta) = 0;
	};
}