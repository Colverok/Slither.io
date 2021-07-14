#include "Food.h"

Food::Food(const Position& new_position, int new_size, uint32_t new_color) {
	position = new_position;
	size = new_size;
	color = new_color;
}

Food::Food() {
	position = {0,0};
	size = 0;
	color = 0;
}

void Food::drawFood(uint32_t buffer[][SCREEN_WIDTH]) const{
	for (int i = position.row; i < position.row + size; i++) {
		for (int j = position.column; j < position.column + size; j++) {
			buffer[i][j] = color;
		}
	}
}

Position Food::getPosition() const{
	return position;

}

int Food::getSize() const{
	return size;
}


uint32_t Food::getColor() const{
	return color;
}