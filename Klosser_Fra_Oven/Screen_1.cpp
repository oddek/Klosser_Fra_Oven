#include "Screen_1.h"



Screen_1::Screen_1(int _level)
{
	//Setting variables:
	board.level = _level;
	move_right = false;
	move_left = false;
	move_down = false;
	
	current_das = init_das;

	//Box for next piece//////////////////////////////////////////////
	next_box.setSize(sf::Vector2f(box_width, box_width));
	next_box.setOrigin(box_width / 2, box_height / 2);
	next_box.setFillColor(sf::Color::Black);
	next_box.setPosition(sf::Vector2f(width - (width - board.get_width() - board.get_offset_x()) / 2, 250));
	shapes.push_back(&next_box);

	next_text.setString("Next:");
	next_text.setFont(digfont);
	next_text.setCharacterSize(box_text_size);
	next_text.setFillColor(sf::Color::Green);

	sf::FloatRect next_rectBounds = next_box.getGlobalBounds();
	sf::FloatRect next_textBounds = next_text.getGlobalBounds();

	next_text.setPosition(
		next_rectBounds.left + (next_rectBounds.width / 2) - (next_textBounds.width / 2),
		next_rectBounds.top + (next_rectBounds.height / 6) - (next_textBounds.height / 2));
	texts.push_back(&next_text);

	//Box for level:
	level_box.setSize(sf::Vector2f(box_width, box_height));
	level_box.setOrigin(box_width/2, box_height/2);
	level_box.setFillColor(sf::Color::Black);
	
	level_box.setPosition(sf::Vector2f(width - (width - board.get_width() - board.get_offset_x()) / 2, 500));
	shapes.push_back(&level_box);

	level_text.setString("Level:\n\n" + std::to_string(board.level));
	level_text.setFont(digfont);
	level_text.setCharacterSize(box_text_size);
	level_text.setFillColor(sf::Color::Green);

	sf::FloatRect level_rectBounds = level_box.getGlobalBounds();
	sf::FloatRect level_textBounds = level_text.getGlobalBounds();

	level_text.setPosition(
		level_rectBounds.left + (level_rectBounds.width / 2) - (level_textBounds.width / 2),
		level_rectBounds.top + (level_rectBounds.height / 2) - (level_textBounds.height / 2));
	texts.push_back(&level_text);

	//Box for points
	point_box.setSize(sf::Vector2f(box_width, box_height));
	point_box.setOrigin(box_width / 2, box_height / 2);
	point_box.setFillColor(sf::Color::Black);
	point_box.setPosition(sf::Vector2f(width - (width - board.get_width() - board.get_offset_x()) / 2, 650));
	shapes.push_back(&point_box);

	point_text.setString("Points:\n\n" + std::to_string(board.points));
	point_text.setFont(digfont);
	point_text.setCharacterSize(box_text_size);	
	point_text.setFillColor(sf::Color::Green);

	sf::FloatRect point_rectBounds = point_box.getGlobalBounds();
	sf::FloatRect point_textBounds = point_text.getGlobalBounds();

	point_text.setPosition(
		point_rectBounds.left + (point_rectBounds.width / 2) - (point_textBounds.width / 2),
		point_rectBounds.top + (point_rectBounds.height / 2) - (point_textBounds.height / 2));
	texts.push_back(&point_text);

	//Box for row
	row_box.setSize(sf::Vector2f(box_width, box_height));
	row_box.setOrigin(box_width / 2, box_height / 2);
	row_box.setFillColor(sf::Color::Black);
	row_box.setPosition(sf::Vector2f(width - (width - board.get_width() - board.get_offset_x()) / 2, 800));
	shapes.push_back(&row_box);

	row_text.setString("Lines:\n\n" + std::to_string(board.rows));
	row_text.setFont(digfont);
	row_text.setCharacterSize(box_text_size);
	row_text.setFillColor(sf::Color::Green);

	sf::FloatRect row_rectBounds = row_box.getGlobalBounds();
	sf::FloatRect row_textBounds = row_text.getGlobalBounds();

	row_text.setPosition(
		row_rectBounds.left + (row_rectBounds.width / 2) - (row_textBounds.width / 2),
		row_rectBounds.top + (row_rectBounds.height / 2) - (row_textBounds.height / 2));
	texts.push_back(&row_text);

	//Box for HighScore
	high_box.setSize(sf::Vector2f(board.get_width()*2/3, board.get_height()));
	high_box.setOrigin(board.get_width() / 3, board.get_height() / 2);
	high_box.setFillColor(sf::Color::Black);

	high_box.setPosition(sf::Vector2f((width - board.get_width() - board.get_offset_x()) / 2, board.get_offset_y() + board.get_height()/2));
	shapes.push_back(&high_box);

	high_text.setString("HighScores");
	high_text.setFont(digfont);
	high_text.setCharacterSize(box_text_size);
	high_text.setFillColor(sf::Color::Green);

	sf::FloatRect high_rectBounds = high_box.getGlobalBounds();
	sf::FloatRect high_textBounds = high_text.getGlobalBounds();

	high_text.setPosition(
		high_rectBounds.left + (high_rectBounds.width / 2) - (high_textBounds.width / 2),
		board.get_offset_y() + high_textBounds.height /2);
	texts.push_back(&high_text);

	for (int i = 0; i < highscores.size(); i++)
	{
		sf::Text t;
		t.setFont(digfont);
		t.setCharacterSize(40);
		t.setString(std::to_string(i+1) + ". " + std::get<0>(highscores[i]) + " " + std::to_string(std::get<1>(highscores[i])));
		int pixelinc = 40;
		t.setPosition(70, 250 + 40*i);
		high_score_texts.push_back(t);
	}
}

Screen_1::~Screen_1()
{
	for (auto i : texts) delete i;
	for (auto i : shapes) delete i;
}



int Screen_1::Run(sf::RenderWindow& App)
{ 
	sf::Event event;
	bool Running = true;
	while (Running)
	{
		while (App.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				return -1;
			if (event.type == sf::Event::KeyReleased)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Down:
					move_down = false;
					current_das = init_das;
					break;
				case sf::Keyboard::Left:
					move_left = false;
					current_das = init_das;
					break;
				case sf::Keyboard::Right:
					move_right = false;
					current_das = init_das;
					break;
				}
			}
			if(event.type == sf::Event::KeyPressed)
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
				{	
					return (0);
					break;
				}
				case sf::Keyboard::Down:
				{
					board.move_current('d');
					t1 = std::chrono::high_resolution_clock::now();
					break;
				}
				case sf::Keyboard::Left:
				{
					board.move_current('l');
					t1 = std::chrono::high_resolution_clock::now();
					move_left = true;

					break;
				}
				case sf::Keyboard::Right:
				{
					board.move_current('r');
					t1 = std::chrono::high_resolution_clock::now();
					move_right = true;
					break;
				}
				case sf::Keyboard::F: case sf::Keyboard::Up: 
				{
					board.rotate_current('r');
					break;
				}
				case sf::Keyboard::D:
				{
					board.rotate_current('l');
					break;
				}
				}
		}

		if (move_left)
		{
			auto t2 = std::chrono::high_resolution_clock::now();
			auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);;
			if (milliseconds.count() > current_das)
			{
				board.move_current('l');
				t1 = std::chrono::high_resolution_clock::now();
				current_das = active_das;
			}
		}
		if (move_right)
		{
			auto t2 = std::chrono::high_resolution_clock::now();
			auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);;
			if (milliseconds.count() > current_das)
			{
				board.move_current('r');
				t1 = std::chrono::high_resolution_clock::now();
				current_das = active_das;
			}
		}
		if (move_down)
		{
			auto t2 = std::chrono::high_resolution_clock::now();
			auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);;
			if (milliseconds.count() > current_das)
			{
				board.move_current('d');
				t1 = std::chrono::high_resolution_clock::now();
				current_das = active_das;
			}
		}

		//Draw stuff
		check_time_and_drop();
		update_window(App);
		if (board.game_over)
		{
			if (board.points <= 4) return 3;
			else return board.points;
		}
	}
	return -1;
}

void Screen_1::update_window(sf::RenderWindow& App)
{
	App.clear();
	//Draw background
	App.draw(back_sprite);
	//Draw board
	App.draw(board.get_sprite());
	//Draw headline
	App.draw(headline);
	//Draw textboxes and stuff
	point_text.setString("Points:\n\n" + std::to_string(board.points));
	row_text.setString("Lines:\n\n" + std::to_string(board.rows));
	level_text.setString("Level:\n\n" + std::to_string(board.level));
	
	for (auto i : shapes) App.draw(*i);
	for (auto i : texts) App.draw(*i);
	for (auto i : high_score_texts) App.draw(i);
	//Draw next piece
	board.update_pixel_next_piece(next_box);
	for (int i = 0; i < board.next->piece_grid.size(); i++)
	{
		for (int j = 0; j < board.next->piece_grid[i].size(); j++)
		{
			if (board.next->piece_grid[i][j] != nullptr)
				App.draw(*board.next->piece_grid[i][j]);
		}
	}
	//Draw current piece
	for (int i = 0; i < board.current->piece_grid.size(); i++)
	{
		for (int j = 0; j < board.current->piece_grid[i].size(); j++)
		{
			if (board.current->upper_left_y + i > 3 && board.current->piece_grid[i][j] != nullptr)
				App.draw(*board.current->piece_grid[i][j]);
		}
	}
	//Draw pieces in grid (already landed)
	for (int i = 4; i < board.grid.size(); i++)
		for (auto j : board.grid[i])
			if (j != nullptr) App.draw(*j);

	
	App.display();
}

void Screen_1::check_time_and_drop()
{
	static auto t1 = std::chrono::high_resolution_clock::now();
	auto t2 = std::chrono::high_resolution_clock::now();
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);;
	if (milliseconds.count() > board.time[board.level])
	{
		board.move_current('d');
		t1 = std::chrono::high_resolution_clock::now();
	}
}
