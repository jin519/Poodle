#pragma once

class GLWindowEventHandler abstract
{
public:
	/* member function */
	virtual void onResize(const int width, const int height) = 0;
	virtual void onKey(const int key, const int scancode, const int action, const int mods) = 0;
	virtual void onIdle(const float deltaTime) = 0;
};