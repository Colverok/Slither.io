#include "ComputerSnake.h"
#include <cmath>

ComputerSnake::ComputerSnake():Snake(){
	foodPosition = { 0, 0 };
};
ComputerSnake::ComputerSnake(const Position& new_position, uint32_t new_color, uint32_t new_head_color)
	:Snake(new_position, new_color, new_head_color){
	foodPosition = { 0, 0 };
};

void ComputerSnake::setFoodPosition(const Position& new_food_position){
	foodPosition = new_food_position;
}

void ComputerSnake::goToFood() {
	// calculate the difference between snake's and food row positions
	int row_diff = foodPosition.row - getHeadPosition().row;

	//calculate the difference between snake's and food column positions
	int column_diff = foodPosition.column - getHeadPosition().column;
	if (abs(row_diff) >= 7) {
		Position newDirection = {row_diff / abs(row_diff), 0};
		//if new direction is opposite to the previous
		if (newDirection.row == (-1) * getDirection().row ) {
			newDirection = Position({0, 1});
		}
		moveSnake(newDirection);
	}
	else if (abs(column_diff) >= 7) {
		Position newDirection = { 0, column_diff / abs(column_diff) };
		//if new direction is opposite to the previous
		if (newDirection.column == (-1) * getDirection().column) {
			newDirection = Position({ 1, 0 });
		}
		moveSnake(newDirection);
	}
	else {
		//if the snake has gone, it needs new food position(set it to 0)
		foodPosition = {0, 0};
	}
}

bool ComputerSnake::IfAimed() const{
	return (foodPosition != Position({0, 0}));
}