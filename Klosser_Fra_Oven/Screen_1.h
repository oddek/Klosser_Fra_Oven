#pragma once
#include "cScreen.h"
#include <fstream>

#include <chrono>
#include "Board.h"
class Screen_1 : public cScreen
{
public:
	Screen_1(int _level);
	virtual ~Screen_1();
	
	virtual int Run(sf::RenderWindow& App);

private:
	void update_window(sf::RenderWindow& App);
	void check_time_and_drop();
	
	std::vector<sf::Text*> texts;
	std::vector<sf::RectangleShape*> shapes;
	const int box_width{ 200 };
	const int box_height{ 90 };
	const int box_text_size{ 30 };

	bool move_right = false;
	bool move_left = false;
	bool move_down = false;

	const int init_das{ 266 };
	const int active_das { 100 };
	int current_das;

	sf::RectangleShape level_box;
	sf::RectangleShape next_box;
	sf::RectangleShape point_box;
	sf::RectangleShape row_box;
	sf::RectangleShape high_box;

	sf::Text level_text;
	sf::Text next_text;
	sf::Text point_text;
	sf::Text row_text;
	sf::Text high_text;

	std::vector<sf::Text> high_score_texts;
	
	Board board;
	
	std::chrono::time_point<std::chrono::high_resolution_clock> t1 = std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::high_resolution_clock> t2 = std::chrono::high_resolution_clock::now();

	
};

