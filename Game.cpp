#include "Engine.h"
#include <stdlib.h>
#include <memory.h>
#include <map>
#include "Colors.h"
#include "ComputerSnake.h"
#include "Numbers.h"

using namespace std;
//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()


static map<int, uint32_t> ColorId{ {
	{0, COLOR_WHITE},
	{1, COLOR_BROWN},
	{2, COLOR_PINK},
	{3, COLOR_GREEN},
	{4, COLOR_RED},
	{5, COLOR_PURPLE},
	{6, COLOR_BLUE}}
};
// Player's snake
static Snake mySnake;
// Computer snakes
static vector<ComputerSnake> CompSnakes(3);
// Food objects
static vector<Food> myFood(5);
// Time when new food objects are created
static float nextLaunchTime;
// Time in game
static float time;
// frequency of motion
static int nextmove;

// the value of screen boarder
const int boarderValue = 5;
// the value of screen boarder for Score
const int boarderScoreValue = 50;
// the size of max object food 
const int maxFoodValue = 25;

//creates food (called when snake is dead)
void createFoodAfterDeath(const Snake& death_snake) {
	for (int k = 0; k < death_snake.getLength(); k++) {
		Position new_food_pos = death_snake.getHeadPosition() + 2 * k;
		//don't creating food if out of boardrs
		if ((new_food_pos.row >= (SCREEN_HEIGHT - boarderValue)) || (new_food_pos.row <= boarderScoreValue) ||
			(new_food_pos.column <= boarderValue) || (new_food_pos.column >= (SCREEN_WIDTH - boarderValue))) {
			break;
		}
		myFood.push_back(Food(new_food_pos, 10, ColorId[rand() % 6]));
	}
}

// initialize game data in this function
void initialize()
{
	//initialize food objects
	for (auto& food : myFood) {
		food = Food({rand() % (SCREEN_HEIGHT - boarderScoreValue -boarderValue - maxFoodValue) + boarderScoreValue,
					rand() % (SCREEN_WIDTH - boarderValue * 2 - maxFoodValue) + boarderValue},
					(rand() % 4 + 1) * 5, //5, 10, 15, 20
					ColorId[rand() % 7]); //0 ... 6
	}

	nextmove = 0;
	nextLaunchTime = rand() % 20;

	//initialize player's snake
	mySnake = Snake({100, 100 }, COLOR_PURPLE, COLOR_BLUE);

	//initialize computer snakes
	for (int i = 0; i < CompSnakes.size(); i++) {
		CompSnakes[i] = ComputerSnake( (i + 3) * mySnake.getHeadPosition(), COLOR_WHITE, ColorId[i + 1]);
		CompSnakes[i].setFoodPosition(myFood[rand() % (myFood.size())].getPosition());
	}

}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
	nextmove++;

	if (is_key_pressed(VK_ESCAPE))
		schedule_quit_game();

	//if the keys of motion are pressed, change direction
	mySnake.setDirectionByKey(VK_UP, {-1, 0});
	mySnake.setDirectionByKey(VK_DOWN, {1, 0});
	mySnake.setDirectionByKey(VK_LEFT, {0, -1});
	mySnake.setDirectionByKey(VK_RIGHT, {0, 1});

	//if snakes are dead, reviving it 
	if (!mySnake.getIsAlive()) {
		mySnake.setIsAlive(true);
		mySnake = Snake({ 100, 100 }, COLOR_PURPLE, COLOR_BLUE);
	}
	//check if snake won
	if (mySnake.win) {
		if (mySnake.winDelay <= 0) {
			schedule_quit_game();
		}
		mySnake.winDelay--;
	}

	for (auto& comp_snake : CompSnakes) {
		if (!comp_snake.getIsAlive()) {
			comp_snake.setIsAlive(true);
			comp_snake = ComputerSnake({ rand() % (SCREEN_HEIGHT - boarderScoreValue) + boarderScoreValue, rand() % SCREEN_WIDTH }, 
										COLOR_WHITE,
										comp_snake.getHeadColor());
		}
		//if there is no food to go, set it
		if (!comp_snake.IfAimed()) {
			comp_snake.setFoodPosition(myFood[rand() % (myFood.size())].getPosition());
		}
		//check if snakes won
		if (comp_snake.win) {
			if (comp_snake.winDelay <= 0) {
				schedule_quit_game();
			}
			comp_snake.winDelay--;
		}
	}

	//moving snakes
	if (nextmove >= 100) {
		nextmove = 0;
		//move player's snake
		mySnake.moveSnake(mySnake.getDirection());
		mySnake.onBordersCollision(boarderValue, boarderScoreValue);
		//move computer snakes
		for (auto& comp_snake : CompSnakes) {
			comp_snake.goToFood();
			mySnake.onBordersCollision(boarderValue, boarderScoreValue);
		}
	}

	// Checking for all food objects collision with snakes;
	// Destroying the food if snake has eaten it
	for (int i = 0; i < myFood.size(); i++) {
		if (mySnake.onCollision(myFood[i])) {
			myFood.erase(myFood.begin() + i);
			break;
		}
		for (auto& comp_snake : CompSnakes) {
			if (comp_snake.onCollision(myFood[i])) {
				myFood.erase(myFood.begin() + i);
				break;
			}
		}
	}

	// Collisions between snakes
	for (int i = 0; i < CompSnakes.size(); i++){
		if (mySnake.onCollision(CompSnakes[i])) {
			createFoodAfterDeath(CompSnakes[i]);
			CompSnakes[i].setIsAlive(false);
			break;
		}
		if (CompSnakes[i].onCollision(mySnake)) {
			createFoodAfterDeath(mySnake);
			mySnake.setIsAlive(false);
			break;
		}
		for (int j = 0; j < CompSnakes.size(); j++) {
			if ((i != j) && (CompSnakes[i].onCollision(CompSnakes[j]))){
				createFoodAfterDeath(CompSnakes[j]);
				CompSnakes[j].setIsAlive(false);
				break;
			}
		}
	}

	time += dt;
	//Creating new food objects
	if ((time >= nextLaunchTime) && (myFood.size() <= 10)) {
		time = 0;
		nextLaunchTime = rand() % 20; 
		for (int i = 0; i < 5; i++) {
			myFood.push_back(
				Food({ rand() % (SCREEN_HEIGHT - boarderScoreValue - boarderValue - maxFoodValue) + boarderScoreValue,
					rand() % (SCREEN_WIDTH - boarderValue * 2 - maxFoodValue) + boarderValue },
					(rand() % 4 + 1) * 5, //5, 10, 15, 20
					ColorId[rand() % 7])); //0 ... 6
		}
	}

	//Creating new computer snakes
	if (CompSnakes.size() < 3) {
		CompSnakes.push_back(ComputerSnake({ rand() % (SCREEN_HEIGHT - boarderScoreValue) + boarderScoreValue, rand() % SCREEN_WIDTH }, COLOR_WHITE, COLOR_BROWN));
		CompSnakes[CompSnakes.size() - 1].setFoodPosition(myFood[rand() % (myFood.size())].getPosition());
	}

}

//draws the rectangle of the snake and it's length(score)
void drawScore(Position score_pos, int score, uint32_t snake_color, uint32_t snake_head_color) {
	Rectangle ScoreRectHead = {score_pos, score_pos + 10};
	Rectangle ScoreRectTail= {{score_pos.row + 10, score_pos.column}, {score_pos.row + 30, score_pos.column + 10}};
	ScoreRectHead.drawRectangle(buffer, snake_head_color);
	ScoreRectTail.drawRectangle(buffer, snake_color);
	drawNumber(score / 100, {score_pos.row + 5, score_pos.column + 20}, COLOR_WHITE);
	drawNumber((score % 100) / 10, { score_pos.row + 5, score_pos.column + 35 }, COLOR_WHITE);
	drawNumber((score % 100) % 10, { score_pos.row + 5, score_pos.column + 50}, COLOR_WHITE);
}


// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
	// clear backbuffer
	memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));

	// drawing boarders
	vector<Rectangle> boarders;
	boarders.push_back({{0,0}, {boarderScoreValue, SCREEN_WIDTH}});
	boarders.push_back({ {0,0}, {SCREEN_HEIGHT, boarderValue} });
	boarders.push_back({ {SCREEN_HEIGHT - boarderValue, 0}, {SCREEN_HEIGHT, SCREEN_WIDTH} });
	boarders.push_back({ { 0, SCREEN_WIDTH - boarderValue}, {SCREEN_HEIGHT, SCREEN_WIDTH} });
	for (const auto& rect_boarder:boarders) {
		rect_boarder.drawRectangle(buffer, COLOR_RED);
	}

	//draw player's snake and scores
	mySnake.drawSnake(buffer, boarderValue, boarderScoreValue);
	drawScore({10, boarderValue + 25}, mySnake.getLength(), mySnake.getColor(), mySnake.getHeadColor());
	//draw food
	for (auto& food : myFood) {
		food.drawFood(buffer);
	}


	//draw computer snakes and scores
	for (int i = 0; i < CompSnakes.size();i++) {
		CompSnakes[i].drawSnake(buffer, boarderValue, boarderScoreValue);
		drawScore({ 10, boarderValue + 25 + 241 * (i + 1) }, CompSnakes[i].getLength(), 
				 CompSnakes[i].getColor(), CompSnakes[i].getHeadColor());
		//if snake win, draw win page
		if (CompSnakes[i].win) {
			clear_buffer();
			drawScore({ SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 }, CompSnakes[i].getLength(),
				CompSnakes[i].getColor(), CompSnakes[i].getHeadColor());
			break;
		}
	}

	//if snake win, draw win page
	if (mySnake.win) {
		clear_buffer();
		drawScore({ SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 }, mySnake.getLength(),
			mySnake.getColor(), mySnake.getHeadColor());
	}

}

// free game data in this function
void finalize()
{
}

