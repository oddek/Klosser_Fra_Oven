#pragma once
#include "Tetromino.h"


class Board
{
public:
	Board();
	~Board();
	int time[29] = { 800, 720, 630,550,466,383,300,216,130,100,83, 83, 83, 66, 66, 66,50, 50, 50,33, 33,33,33,33,33,33,33,33, 16};
	int level = 6;
	int points = 0;
	int rows = 0;
	bool game_over = false;
	void gen_piece();
	Tetromino* current = nullptr;
	Tetromino* next = nullptr;

	sf::Sprite get_sprite();
	std::vector<std::vector<Block*>> grid;

	void print_grid();
	void rotate_current(char dir);
	void move_current(char dir);
	void update_current_pixel();
	void update_pixel_positions();
	void update_pixel_next_piece(sf::RectangleShape next_box);

	int get_grid_height() { return grid_height; }
	int get_grid_width() { return grid_width; }
	int get_width() { return width; }
	int get_height() { return height; }
	int get_offset_x() { return offset_x; }
	int get_offset_y(){return offset_y;}
private:

	void add_current_to_grid();
	void check_line();
	void delete_row(int row);

	int block_size = 40;
	int grid_width = 10;
	int grid_height = 24;
	int width = block_size * grid_width;
	int height = block_size * (grid_height-4);
	int offset_x = 400;
	int offset_y = 200;

	sf::Image img;
	sf::Texture tex;
	sf::Sprite sprite;
};

