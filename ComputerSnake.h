#pragma once
#include "Snake.h"

class ComputerSnake :
	public Snake {
public:
	ComputerSnake();
	ComputerSnake(const Position& new_position, uint32_t new_color, uint32_t new_head_color);
	// Sets new target food position
	void setFoodPosition(const Position& new_food_position);
	//makes snake go to food position
	void goToFood();
	//returns if snake has food to aim
	bool IfAimed() const;
private:
	//won't rule computer snakes by the key
	using Snake::setDirectionByKey;
	// position of food which snake will go to
	Position foodPosition;
};

