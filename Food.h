#pragma once
#include "Position.h"
#include "Engine.h"

class Food {
public:
	Food(const Position& new_position, int new_size, uint32_t new_color);
	Food();
	void drawFood(uint32_t buffer[][SCREEN_WIDTH]) const;
	Position getPosition() const;
	int getSize() const;
	uint32_t getColor() const;
private:
	//position of food object (left up point)
	Position position;
	//size of the square of food object
	int size;
	uint32_t color;
};