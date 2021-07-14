#include "Rectangle.h"


void Rectangle::drawRectangle(uint32_t buffer[][SCREEN_WIDTH], uint32_t color) const {
	for (int i = leftUp.row; i < rightDown.row; i++) {
		for (int j = leftUp.column; j < rightDown.column; j++) {
			buffer[i][j] = color;
		}
	}

}