#include "Tetromino.h"
#include "Board.h"


Tetromino::Tetromino(char _symbol, int _size): 
	symbol(_symbol)
{	
	upper_left_x = 3;
	upper_left_y = 0;
	switch (symbol)
	{
	case 'I':
	{
		for (int i = 0; i < 4; i++)
		{
			std::vector<Block*> vec(4, nullptr);
			piece_grid.push_back(vec);
		}
		for (int i = 0; i < 4; i++)
		{
			piece_grid[2][i] = new Block(sf::Color::Cyan, _size);

		}
		break;
	}
	case 'O':
	{
		for (int i = 0; i < 2; i++)
		{
			std::vector<Block*> vec(2, nullptr);
			piece_grid.push_back(vec);
		}
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				piece_grid[i][j] = new Block(sf::Color::Yellow, _size);
		break;
	}
	case 'S':
	{
		for (int i = 0; i < 3; i++)
		{
			std::vector<Block*> vec(3, nullptr);
			piece_grid.push_back(vec);
		}
		piece_grid[2][0] = new Block(sf::Color::Green, _size);
		piece_grid[2][1] = new Block(sf::Color::Green, _size);
		piece_grid[1][1] = new Block(sf::Color::Green, _size);
		piece_grid[1][2] = new Block(sf::Color::Green, _size);
		break;
	}
	case 'Z':
	{
		for (int i = 0; i < 3; i++)
		{
			std::vector<Block*> vec(3, nullptr);
			piece_grid.push_back(vec);
		}
		piece_grid[1][0] = new Block(sf::Color::Red, _size);
		piece_grid[1][1] = new Block(sf::Color::Red, _size);
		piece_grid[2][1] = new Block(sf::Color::Red, _size);
		piece_grid[2][2] = new Block(sf::Color::Red, _size);
		break;
	}
	case 'J':
	{
		for (int i = 0; i < 3; i++)
		{
			std::vector<Block*> vec(3, nullptr);
			piece_grid.push_back(vec);
		}
		piece_grid[1][0] = new Block(sf::Color::Blue, _size);
		piece_grid[2][0] = new Block(sf::Color::Blue, _size);
		piece_grid[2][1] = new Block(sf::Color::Blue, _size);
		piece_grid[2][2] = new Block(sf::Color::Blue, _size);
		break;
	}
	case 'L':
	{
		for (int i = 0; i < 3; i++)
		{
			std::vector<Block*> vec(3, nullptr);
			piece_grid.push_back(vec);
		}
		piece_grid[2][0] = new Block(sf::Color(0xFF8C00ff), _size);
		piece_grid[2][1] = new Block(sf::Color(0xFF8C00ff), _size);
		piece_grid[2][2] = new Block(sf::Color(0xFF8C00ff), _size);
		piece_grid[1][2] = new Block(sf::Color(0xFF8C00ff), _size);
		break;
	}
	case 'T':
	{
		for (int i = 0; i < 3; i++)
		{
			std::vector<Block*> vec(3, nullptr);
			piece_grid.push_back(vec);
		}
		piece_grid[2][0] = new Block(sf::Color(0x800080ff), _size);
		piece_grid[2][1] = new Block(sf::Color(0x800080ff), _size);
		piece_grid[2][2] = new Block(sf::Color(0x800080ff), _size);
		piece_grid[1][1] = new Block(sf::Color(0x800080ff), _size);
		break;
	}
	}
}

Tetromino::Tetromino(const Tetromino& old_t)
{
	symbol = old_t.symbol;
	upper_left_x = old_t.upper_left_x;
	upper_left_y = old_t.upper_left_y;
	for (int i = 0; i < old_t.piece_grid.size(); i++)
	{
		std::vector<Block*> vec(old_t.piece_grid.size(), nullptr);
		piece_grid.push_back(vec);
	}

	for (int i = 0; i < old_t.piece_grid.size(); i++)
	{
		for (int j = 0; j < old_t.piece_grid[i].size(); j++)
		{
			if (old_t.piece_grid[i][j] == nullptr) continue;
			else
			{
				Block* b = new Block(old_t.piece_grid[i][j]->color, old_t.piece_grid[i][j]->size);
				b->x = old_t.piece_grid[i][j]->x;
				b->y = old_t.piece_grid[i][j]->y;
				piece_grid[i][j] = b;
			}
		}
		
	}
}


Tetromino::~Tetromino()
{
	for (int i = 0; i < piece_grid.size(); i++)
	{
		for (int j = 0; j < piece_grid[i].size(); j++)
		{
			delete piece_grid[i][j];
		}
	}
}

bool Tetromino::move(char dir, Board& board)
{
	//Hvis mulig:
	if (!in_bounds(dir, board)) return false;
	if (occupied(dir, board)) return false;
	switch (dir)
	{
	case 'd':
		upper_left_y += 1;
		break;
	case 'l':
		upper_left_x -= 1;
		break;
	case 'r':
		upper_left_x += 1;
		break;
	}
	return true;
}




bool Tetromino::in_bounds(char dir, Board& board)
{
	
	switch (dir)
	{
	case 'd':
		if (get_lowest_row_with_block() + upper_left_y >= board.get_grid_height()-1) return false;
		break;
	case 'l':
		if (get_leftmost_col_with_block() + upper_left_x <= 0) return false;
		break;
	case 'r':
		if (get_rightmost_col_with_block() + upper_left_x >= board.get_grid_width() - 1) return false;
		break;
	default:
		return false;
	}
	return true;

}

int Tetromino::get_lowest_row_with_block()
{
	for (int row = piece_grid.size() - 1; row >= 0; row--)
		for (int collumn = 0; collumn < piece_grid[row].size(); collumn++)
			if (piece_grid[row][collumn] != nullptr) return row;
}

int Tetromino::get_rightmost_col_with_block()
{
	for (int collumn = piece_grid[0].size() - 1; collumn >= 0; collumn--)
		for (int row = 0; row < piece_grid.size(); row++)
			if (piece_grid[row][collumn] != nullptr) return collumn;
}

int Tetromino::get_leftmost_col_with_block()
{
	for (int collumn = 0; collumn < piece_grid[0].size(); collumn++)
		for (int row = 0; row < piece_grid.size(); row++)
			if (piece_grid[row][collumn] != nullptr) return collumn;
}

bool Tetromino::occupied(char dir, Board& board)
{
	switch (dir)
	{
	case 'd':
	{
		for (int row = 0; row < piece_grid.size(); row++)
		{
			for (int collumn = 0; collumn < piece_grid[row].size(); collumn++)
			{
				if (piece_grid[row][collumn] == nullptr) continue;
				if (board.grid[upper_left_y + row + 1][upper_left_x + collumn] != nullptr) return true;
			}
		}
		return false;
	}
	case 'l':
	{
		for (int row = 0; row < piece_grid.size(); row++)
		{
			for (int collumn = 0; collumn < piece_grid[row].size(); collumn++)
			{
				if (piece_grid[row][collumn] == nullptr) continue;
				//Ligger kun inne for å hindre sjekk på I-brikke, som gir error.
				if (upper_left_x + get_rightmost_col_with_block() > board.get_grid_width()) return true;
				if (board.grid[upper_left_y + row][upper_left_x + collumn - 1] != nullptr) return true;
			}
		}
		return false;
	}
	case 'r':
	{
		for (int row = 0; row < piece_grid.size(); row++)
		{
			for (int collumn = 0; collumn < piece_grid[row].size(); collumn++)
			{
				if (piece_grid[row][collumn] == nullptr) continue;
				if (board.grid[upper_left_y + row][upper_left_x + collumn + 1] != nullptr) return true;
			}
		}
		return false;
	}
	}
	
}

Tetromino* Tetromino::rotate(char dir, Board& board)
{
	Tetromino* t = new Tetromino(*this);

	int n = piece_grid.size();
	if (dir == 'l')
	{
		for (int i = 0; i < n/2; i++)
		{
			for (int j = i; j < (n - i - 1); j++)
			{
				Block* tmp = t->piece_grid[i][j];
				t->piece_grid[i][j] = t->piece_grid[j][n-1-i];
				t->piece_grid[j][n-1-i] = t->piece_grid[n - 1 - i][n - 1 - j];
				t->piece_grid[n - 1 - i][n - 1 - j] = t->piece_grid[n-1-j][i];
				t->piece_grid[n-1-j][i] = tmp;
			}
		}
		
	}
	else if (dir == 'r')
	{
		for (int i = 0; i < n / 2; i++)
		{
			for (int j = i; j < n - i - 1; j++)
			{
				Block* tmp = t->piece_grid[n-1-j][i];
				t->piece_grid[n-1-j][i] = t->piece_grid[n - 1 - i][n-1-j];
				t->piece_grid[n - 1 - i][n-1-j] = t->piece_grid[j][n - 1 - i];
				t->piece_grid[j][n - 1 - i] = t->piece_grid[i][j];
				t->piece_grid[i][j] = tmp;
			}
		}
	}
	if (rot_in_bounds(*t, board)) return t;

	if (t->move('l', board)) { if (rot_in_bounds(*t, board)) return t; }
	if (t->move('r', board)) { if (rot_in_bounds(*t, board)) return t; }
	
	delete t;
	return nullptr;
}

bool Tetromino::rot_in_bounds(Tetromino& t, Board& board)
{
	for (int i = 0; i < t.piece_grid.size(); i++)
	{
		for (int j = 0; j < t.piece_grid[i].size(); j++)
		{
			if (t.piece_grid[i][j] == nullptr) continue;
			if (t.upper_left_x < 0 ||
				t.get_rightmost_col_with_block() + t.upper_left_x > 9 || t.get_lowest_row_with_block()+t.upper_left_y >= board.get_grid_height())
				return false;
			/*if (board.grid[i + t.upper_left_y][j + upper_left_y] != nullptr)
				return false;
				*/
		}
	}
	return true;
}

