#pragma once
#include <SFML/Graphics.hpp>
#include <exception>
#include <fstream>
#include <iostream>
#include <tuple>
class cScreen
{
public:

	cScreen();
	//virtual ~cScreen() = 0;
	virtual int Run(sf::RenderWindow &App) = 0;
	
	int get_width() { return width; }
	int get_height() { return height; }
	virtual int get_level() { return 0; }
	static std::vector<std::tuple<std::string, int>> highscores;
	static void load_highscores();
	static int check_highscore(int score);
	static void save_highscores();
protected:
	//Div vars
	int height = 1100;
	int width = 1200;
	
	//Background
	sf::Image background;
	sf::Texture back_tex;
	sf::Sprite back_sprite;
	//Fonts
	sf::Font open_sans_font;
	sf::Font digfont;
	sf::Font head_font;
	sf::Font summit_font;
	//Headline
	sf::Text headline;
	
};

