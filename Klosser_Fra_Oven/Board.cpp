#include "Board.h"



Board::Board()
{
	//Draw field
	img.create(width, height);
	tex.loadFromImage(img);
	sprite.setTexture(tex);
	sprite.setColor(sf::Color::Black);
	sprite.setPosition(sf::Vector2f(offset_x, offset_y));

	grid.resize(grid_height, std::vector<Block*>(grid_width));
	for(int i = 0; i < grid.size(); i++)
		for (auto i : grid[i])
		{
			i = nullptr;
		}

	gen_piece();
	gen_piece();
	update_current_pixel();

}


Board::~Board()
{
	for (int i = 0; i < grid.size(); i++)
	{
		for(int j = 0; j < grid[i].size(); j++)
		delete (grid[i][j]);
	}
	delete current;
	delete next;
}

sf::Sprite Board::get_sprite()
{
	return sprite;
}


void Board::gen_piece()
{
	char sym[] = { 'I', 'O', 'S','Z','J','L','T' };
	int i = rand() % 7;
	Tetromino* t = new Tetromino(sym[i], block_size);
	if (current == nullptr) current = t;
	else next = t;
}

void Board::update_pixel_next_piece(sf::RectangleShape next_box)
{
	int offset_x = (next_box.getSize().x - next->piece_grid.size()*block_size) / 2;
	int offset_y = (next_box.getSize().y - next->piece_grid.size()*block_size) / 2;
	for (int i = 0; i < next->piece_grid.size(); i++)
	{
		for (int j = 0; j < next->piece_grid[i].size(); j++)
		{
			if (next->piece_grid[i][j] == nullptr) continue;
			//if (next->piece_grid.size() == 3)
			{
				next->piece_grid[i][j]->setPosition(next_box.getPosition().x - next_box.getOrigin().x + offset_x + block_size*j
					, next_box.getPosition().y - next_box.getOrigin().y + offset_y + block_size * i);
				
			}
			
			//next->piece_grid[i][j]->setPosition();
		}
	}
}


void Board::rotate_current(char dir)
{
	Tetromino* tmp = current->rotate(dir, *this);
	if (tmp != nullptr) 
	{
		delete current;
		current = tmp;
	}
	update_current_pixel();
}

void Board::move_current(char dir)
{
	bool moved = current->move(dir, *this);
	update_current_pixel();
	if (!moved && dir == 'd')
	{
		add_current_to_grid();
		if (current->upper_left_y < 4) game_over = true;
		check_line();
		current = next;
		current->upper_left_x = 3;
		current->upper_left_y = 0;
		update_current_pixel();
		gen_piece();

	}
}

void Board::add_current_to_grid()
{
	for (int row = 0; row < current->piece_grid.size(); row++)
	{
		for (int collumn = 0; collumn < current->piece_grid[row].size(); collumn++)
		{
			if (current->piece_grid[row][collumn] == nullptr) continue;
			grid[current->upper_left_y + row][current->upper_left_x + collumn] = current->piece_grid[row][collumn];
		}
	}
}

void Board::check_line()
{
	int lines = 0; 
	for (int row = 0; row < grid.size(); row++)
	{
		bool hole = false;
		for (int collumn = 0; collumn < grid[row].size(); collumn++)
		{
			if (grid[row][collumn] == nullptr)
			{
				hole = true;
				break;
			}
		}
		if (hole == false)
		{
			delete_row(row);
			update_pixel_positions();
			lines++;
		}
	}
	switch (lines)
	{
	case 1:
		points += 40 * (level + 1);
		break;
	case 2:
		points += 100 * (level + 1);
		break;
	case 3:
		points += 300 * (level + 1);
		break;
	case 4:
		points += 1200 * (level + 1);
		break;
	}
	rows += lines;
	if (rows / 10 > level) level = rows / 10;
}

void Board::delete_row(int row)
{
	std::vector<Block*> vec(10, nullptr);
	
	for (int i = 0; i < grid[row].size(); i++) delete grid[row][i];
	grid.erase(grid.begin() + row);
	grid.insert(grid.begin(), vec);
	for (int i = 0; i <= row; i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			if(grid[i][j] != nullptr) grid[i][j]->y += 1;
		}
	}
}

void Board::print_grid()
{
	for (int row = 0; row < grid.size(); row++)
	{
		for (int collumn = 0; collumn < grid[row].size(); collumn++)
		{
			std::cout << " " << ((grid[row][collumn] == nullptr) ? "0" : "1") << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Board::update_current_pixel()
{
	
	sf::Vector2f pos( offset_x + block_size * current->upper_left_x,
		offset_y + block_size * (current->upper_left_y-4) );
	for (int row = 0; row < current->piece_grid.size(); row++)
	{
		for (int collumn = 0; collumn < current->piece_grid[row].size(); collumn++)
		{
			if (current->piece_grid[row][collumn] != nullptr)
				current->piece_grid[row][collumn]->setPosition(pos);
			pos.x += block_size;
		}
		pos.x = offset_x + block_size * current->upper_left_x;
		pos.y += block_size;
	}
}

void Board::update_pixel_positions()
{
	sf::Vector2f pos(offset_x, offset_y);
	for (int row = 4; row < grid.size(); row++)
	{
		for (int collumn = 0; collumn < grid[row].size(); collumn++)
		{
			if (grid[row][collumn] != nullptr)
			{

				grid[row][collumn]->setPosition(pos);
			}
			pos.x += block_size;
		}
		pos.x = offset_x;
		pos.y += block_size;
	}
}
