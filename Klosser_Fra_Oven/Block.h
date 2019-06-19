#pragma once
#include "SFML/Graphics.hpp"
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>

class Board;

class Block : public sf::RectangleShape
{
public:
	Block();
	Block(sf::Color _color, int _size);
	~Block();
	sf::Color color;

	int x;
	int y;

	int size;

private:
	
};


///Fant feilen!!!!!!!!!!!! Du sletter de, men lager de på nytt i update_grid.
//Du må slette Tetrominodelene også.
