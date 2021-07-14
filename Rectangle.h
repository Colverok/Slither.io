#pragma once
#include "Position.h"
#include "Engine.h"

struct Rectangle {
	//left up point of rectangle
	Position leftUp;
	//left down point of rectangle
	Position rightDown;
	void drawRectangle(uint32_t buffer[][SCREEN_WIDTH], uint32_t color) const;
};

