#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "Block.h"
class Tetromino
{
public:
	Tetromino(char _symbol, int _size);
	Tetromino(const Tetromino& old_t);
	~Tetromino();
	char symbol;
	std::vector<std::vector<Block*>> piece_grid;
	sf::Color color;

	int upper_left_x;
	int upper_left_y;

	sf::Vector2f start_pos;

	Tetromino* rotate(char dir, Board& board);
	bool move(char dir, Board& board);

	bool in_bounds(char dir, Board& board);
	bool occupied(char dir, Board& board);

	int get_lowest_row_with_block();
	int get_rightmost_col_with_block();
	int get_leftmost_col_with_block();

	bool rot_in_bounds(Tetromino& t, Board& board);

};

