#pragma once
#include <string>
#include <vector>
#include "Position.h"
#include "Engine.h"
#include "Food.h"

class Snake {

public:
	Snake(const Position& new_position, uint32_t new_color, uint32_t new_head_color);
	Snake();

	//this value is true if the snake has won
	bool win;
	int winDelay;

	void drawSnake(uint32_t buffer[][SCREEN_WIDTH], int boarderValue, int boarderScoreValue) const;
	//moves the snake according to the new_direction
	void moveSnake(const Position& new_direction);
	//add to the snake a tail with length of given size
	void grow(int size);
	//sets new direction
	void setDirection(const Position& new_direction);
	//sets new direction depending on what key is pressed
	void setDirectionByKey(int key, const Position& new_direction);
	//sets if snake is alive
	void setIsAlive(bool value);
	//checks collision between this snake and the head of another one
	bool onCollision(const Snake& other_snake) const;
	//checks collision between snake and food object 
	bool onCollision(const Food& food);
	//checks collision between snake and boarders and kill snake if true
	void onBordersCollision(int boarderValue, int boarderScoreValue);

	Position getHeadPosition() const;
	Position getDirection() const;
	int getSize() const;
	int getLength() const;
	bool getIsAlive() const;
	uint32_t getColor() const;
	uint32_t getHeadColor() const;

private:
	//the size of one snake's square 
	int size;
	//the amount of squares of the snake
	int length;
	//vector of positions of squares of the snake
	std::vector<Position> position;
	Position direction;
	//color of snake's tail
	uint32_t color;
	//color of snake's head
	uint32_t headColor;
	//this value is true if the snake is alive 
	bool isAlive;
	//meths that goes along the rects (see OnCollision(const Snake& other_snake))
	int goAlongRect(int first_pos, const Position& go_direction) const;
};

