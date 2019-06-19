#include "Block.h"

Block::Block()
{}

Block::Block(sf::Color _color, int _size): color(_color), size(_size)
{
	setOutlineColor(sf::Color::Black);
	setOutlineThickness(-2);

	setSize(sf::Vector2f(size, size));
	
	setFillColor(_color);

	
}


Block::~Block()
{
}
