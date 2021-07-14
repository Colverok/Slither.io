#pragma once

struct Position {
	int row;
	int column;
	friend Position operator+(const Position& left, const Position& right);
	friend Position operator-(const Position& left, const Position& right);
	friend Position operator*(const int& value, const Position& position);
	friend Position operator/(const Position& position, const int& value);
	friend Position operator+(const Position& position, const int& value);
	friend bool operator==(const Position& left, const Position& right);
	friend bool operator!=(const Position& left, const Position& right);
};

Position operator+(const Position& left, const Position& right);
Position operator-(const Position& left, const Position& right);
Position operator*(const int& value, const Position& position);
Position operator/(const Position& position, const int& value);
bool operator==(const Position& left, const Position& right);
bool operator!=(const Position& left, const Position& right);
Position operator+(const Position& position, const int& value);