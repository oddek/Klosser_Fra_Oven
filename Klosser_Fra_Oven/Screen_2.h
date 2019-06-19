#pragma once
#include "cScreen.h"
class Screen_2 : public cScreen
{
public:
	Screen_2(void);
	~Screen_2();

	virtual int Run(sf::RenderWindow& App);
	std::string get_name();
private:
	sf::Text message;
	sf::FloatRect message_bounds;
	std::vector<sf::Text> name;
};

