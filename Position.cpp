#include "Position.h"

Position operator+(const Position& left, const Position& right) {
	return { left.row + right.row, left.column + right.column };
}

Position operator-(const Position& left, const Position& right) {
	return { left.row - right.row, left.column - right.column };
}

Position operator*(const int& value, const Position& position) {
	return { value * position.row, value * position.column };
}

Position operator/(const Position& position, const int& value) {
	return {position.row / value, position.column / value};

}

bool operator==(const Position& left, const Position& right) {
	return (( left.row == right.row) && (left.column == right.column));
}

bool operator!=(const Position& left, const Position& right) {
	return !(left == right);
}

Position operator+(const Position& position, const int& value) {
	return {position.row + value, position.column + value};
}