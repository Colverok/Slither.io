#pragma once
#include "Rectangle.h"

//this file contains functions to draw numbers

const int num_width = 10;
const int num_height = 2 * num_width;
const int num_boarder = 2;

//draw big left vectical line
void DrawVertBigLeft(const Position& num_pos, uint32_t num_color) {
	Rectangle rect = { num_pos, {num_pos.row + num_height, num_pos.column + num_boarder} };
	rect.drawRectangle(buffer, num_color);
}
//draw big right vectical line
void DrawVertBigRight(const Position& num_pos, uint32_t num_color) {
	DrawVertBigLeft({ num_pos.row, num_pos.column + num_width - num_boarder }, num_color);
}
//draw upper horizontal line
void DrawHorUp(const Position& num_pos, uint32_t num_color) {
	Rectangle rect = { num_pos, {num_pos.row + num_boarder, num_pos.column + num_width} };
	rect.drawRectangle(buffer, num_color);
}
//draw lower horizontal line
void DrawHorDown(const Position& num_pos, uint32_t num_color) {
	DrawHorUp({ num_pos.row + num_height - num_boarder, num_pos.column }, num_color);
}
//draw medium horizontal line
void DrawHorMed(const Position& num_pos, uint32_t num_color) {
	DrawHorUp({ num_pos.row + (num_height - num_boarder) / 2 , num_pos.column }, num_color);
}
//draw small left vectical line
void DrawVertSmallLeft(const Position& num_pos, uint32_t num_color) {
	Rectangle rect = { num_pos, {num_pos.row + (num_height - num_boarder) / 2, num_pos.column + num_boarder} };
	rect.drawRectangle(buffer, num_color);
}
//draw small left right lower vectical line
void DrawVertSmallRight(const Position& num_pos, uint32_t num_color) {
	DrawVertSmallLeft({ num_pos.row + (num_height - num_boarder) / 2, num_pos.column + num_width - num_boarder }, num_color);
}

//draws figure(from 0 to 9) in position num_pos
void drawNumber(int num, Position num_pos, uint32_t num_color) {
	switch (num) {
	case 0:
		DrawHorUp(num_pos, num_color);
		DrawVertBigLeft(num_pos, num_color);
		DrawHorDown(num_pos, num_color);
		DrawVertBigRight(num_pos, num_color);
		break;
	case 1:
		DrawVertBigLeft({ num_pos.row, num_pos.column + ((num_width - num_boarder) / 2) }, num_color);
		break;
	case 2:
		DrawHorUp(num_pos, num_color);
		DrawHorDown(num_pos, num_color);
		DrawHorMed(num_pos, num_color);
		DrawVertSmallLeft({ num_pos.row, num_pos.column + num_width - num_boarder }, num_color); //vert_small_right_up
		DrawVertSmallLeft({ num_pos.row + (num_height - num_boarder) / 2, num_pos.column }, num_color); //vert_small_left_down
		break;
	case 3:
		DrawHorUp(num_pos, num_color);
		DrawHorDown(num_pos, num_color);
		DrawHorMed(num_pos, num_color);
		DrawVertBigRight(num_pos, num_color);
		break;
	case 4:
		DrawVertSmallLeft(num_pos, num_color);
		DrawHorMed(num_pos, num_color);
		DrawVertBigRight(num_pos, num_color);
		break;
	case 5:
		DrawVertSmallLeft(num_pos, num_color);
		DrawHorUp(num_pos, num_color);
		DrawHorMed(num_pos, num_color);
		DrawHorDown(num_pos, num_color);
		DrawVertSmallRight(num_pos, num_color);
		break;
	case 6:
		DrawVertBigLeft(num_pos, num_color);
		DrawHorUp(num_pos, num_color);
		DrawHorMed(num_pos, num_color);
		DrawHorDown(num_pos, num_color);
		DrawVertSmallRight(num_pos, num_color);
		break;
	case 7:
		DrawVertBigRight(num_pos, num_color);
		DrawHorUp(num_pos, num_color);
		break;
	case 8:
		DrawHorUp(num_pos, num_color);
		DrawHorMed(num_pos, num_color);
		DrawHorDown(num_pos, num_color);
		DrawVertBigLeft(num_pos, num_color);
		DrawVertBigRight(num_pos, num_color);
		break;
	case 9:
		DrawVertBigRight(num_pos, num_color);
		DrawVertSmallLeft(num_pos, num_color);
		DrawHorUp(num_pos, num_color);
		DrawHorMed(num_pos, num_color);
		DrawHorDown(num_pos, num_color);
		break;
	default:
		break;
	}
}