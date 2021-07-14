#include "Snake.h"
#include "Rectangle.h"
#include <cmath>

Snake::Snake(const Position& new_position, uint32_t new_color, uint32_t new_head_color) {
	length = 3;
	size = 10;
	direction = {0, 1};
	for (int i = 0; i < length; i++) {
		position.push_back({ new_position.row, new_position.column - i * size });
	}
	color = new_color;
	headColor =  new_head_color;
	isAlive = true;
	win = false;
	winDelay = 250;
}

Snake::Snake() {
	length = 0;
	size = 0;
	direction = { 0, 0 };
	color = 0;
	headColor = 0;
	isAlive = true;
	win = false;
	winDelay = 250;
}

void Snake::drawSnake(uint32_t buffer[][SCREEN_WIDTH], int boarderValue, int boarderScoreValue) const {
	for (int k = position.size() - 1; k >= 0; k--) {
		for (int i = position[k].row; i < position[k].row + size; i++) {
			for (int j = position[k].column; j < position[k].column + size; j++) {
				if (k == 0) {
					buffer[i][j] = headColor;
				}
				else {
					if ((i < (SCREEN_HEIGHT - boarderValue)) && (i > boarderScoreValue) &&
						(j > boarderValue) && (j < (SCREEN_WIDTH - boarderValue))) {
						buffer[i][j] = color;
					}
				}
			}
		}
	}
}

void Snake::moveSnake(const Position& new_direction) {
	for (int i = position.size() - 1; i > 0; i--) {
		position[i] = position[i - 1];
	}
	direction = new_direction;
	position[0] = position[0] +  size * direction;
}

void Snake::grow(int new_size) {
	for (int i = length; i < length + new_size; i++) {
		Position new_position = 2 * position[i - 1] - position[i - 2];
		position.push_back(new_position);		
	}
	length += new_size;
	if (length >= 150) {
		win = true;
	}
}

void Snake::setDirection(const Position& new_direction){
	direction = new_direction;
}

void Snake::setDirectionByKey(int key, const Position& new_direction) {
	if (is_key_pressed(key) && (direction != (-1) * new_direction)) {
		setDirection(new_direction);
	}
}

void Snake::setIsAlive(bool value) {
	isAlive = value;
};

//returns if rectangles have intersections
bool onRectCollision(const Rectangle& first, const Rectangle& second) {
	bool collisionR = (first.rightDown.row >= second.leftUp.row) && (second.rightDown.row >= first.leftUp.row);
	bool collisionC = (first.rightDown.column >= second.leftUp.column) && (second.rightDown.column >= first.leftUp.column);
	return collisionC && collisionR;
}

//goes along snake from the position of some square of snake and finds last square of the rectangle
//first_pos -- first position of needed rectangle
//go_direction -- direction in which the rectangle will be built
//returns last position of rectangle, but the first and last positions of rectangle may be inverted because of direction
int Snake::goAlongRect(int first_pos, const Position& go_direction) const{
	int last_pos = first_pos;
	Position diff;
	// do while the squares are in one line and until the end of snake
	do {
		last_pos++;
		diff = position[last_pos] - position[last_pos - 1];
	} while(((diff.row * go_direction.row + diff.column * go_direction.column) == size) && (last_pos < position.size() - 1));
	
	return last_pos;
}

bool Snake::onCollision(const Snake& other_snake) const{
	Rectangle other_head_rect = Rectangle({other_snake.getHeadPosition(), other_snake.getHeadPosition() + other_snake.getSize()});
	Rectangle CollisionArea = Rectangle({ position[0] + (-1) * size * length, position[0] + size  * (length + 1) });
	//to reduce cycle check collision with collision area
	if (!onRectCollision(CollisionArea, other_head_rect)) {
		return false;
	}
	Rectangle snake_part;
	int firstPoint = 1;
	int lastPoint;
	while (firstPoint < position.size() - 1){
		//calculate direction in which we go while finding rectangle
		Position rect_direction = (position[firstPoint + 1] - position[firstPoint]) / size;
		//
		lastPoint = goAlongRect(firstPoint, rect_direction);
		int newFirstPoint = firstPoint;
		int newLastPoint = lastPoint;
		//if direction was negative, change corners of rectangle 
		if ((rect_direction.row < 0) || (rect_direction.column < 0)) {
			newFirstPoint = lastPoint;
			newLastPoint = firstPoint;
		}
		//finded new snake's rectangle
		snake_part = Rectangle({ position[newFirstPoint], position[newLastPoint] + size });
		// check collision with this rectangle and other snake's head
		if (onRectCollision(snake_part, other_head_rect)) {
			return true;
		}
		//go to the next rectangle
		firstPoint = lastPoint + 1;
	}
	return false;
};

bool Snake::onCollision(const Food& food){
	int food_size = food.getSize();
	//Rectangle of snake head
	Rectangle snakeHeadRect = Rectangle({position[0],  position[0] + size});
	//Rectangle of food object
	Rectangle foodRect = Rectangle({food.getPosition(), food.getPosition() + food_size});
	if (onRectCollision(snakeHeadRect, foodRect)) {
		grow(food_size / 5);
		return true;
	}
	return false;
};

void Snake::onBordersCollision(int boarderValue, int boarderScoreValue) {
	if ((position[0].row >= (SCREEN_HEIGHT - boarderValue)) || (position[0].row <= boarderScoreValue) ||
		(position[0].column <= boarderValue) || (position[0].column >= (SCREEN_WIDTH - boarderValue))) {
		isAlive = false;
	}
}

Position Snake::getHeadPosition() const {
	return position[0];
}

Position Snake::getDirection() const {
	return direction;
}

int Snake::getSize() const {
	return size;
}

int Snake::getLength() const {
	return length;
}

bool Snake::getIsAlive() const {
	return isAlive;
}

uint32_t Snake::getColor() const {
	return color;
}

uint32_t Snake::getHeadColor() const {
	return headColor;
}
