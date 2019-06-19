#pragma once
#include "cScreen.h"


class Screen_0 : public cScreen
{
public:
	Screen_0(void);
	~Screen_0();
	virtual int Run(sf::RenderWindow &App);
	int get_level() { return level; }

private:
	bool playing;
	int level = 0;

	sf::Text Menu1;
	sf::Text Menu2;
	sf::Text Menu3;
	sf::Text level_text;

	sf::FloatRect Menu1Bounds;
	sf::FloatRect Menu2Bounds;
	sf::FloatRect Menu3Bounds;

	std::vector<sf::Text> levelMenu;
};

