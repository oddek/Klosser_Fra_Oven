#include "Screen_2.h"



Screen_2::Screen_2(void)
{
	message.setFont(summit_font);
	message.setCharacterSize(60);
	message.setString( "Congrats!\nNew Record!\nPlease enter name:");
	message_bounds = message.getGlobalBounds();
	message.setPosition({ (width - message_bounds.width) / 2, 250 });

	for (int i = 0; i < 3; i++)
	{
		char ch = 'A';
		sf::Text t;
		t.setFont(summit_font);
		t.setCharacterSize(40);
		t.setString(ch);
		int pixelinc = 800 / 20;
		t.setPosition(((width - 800) / 2) + pixelinc * i, 500);
		name.push_back(t);
	}
}


Screen_2::~Screen_2()
{
}


int Screen_2::Run(sf::RenderWindow& App)
{
	sf::Event Event;
	bool Running = true;
	int index = 0;
	char curr;
	while (Running)
	{
		while (App.pollEvent(Event))
		{
			// Window closed
			if (Event.type == sf::Event::Closed)
			{
				return (-1);
			}
			//Key pressed
			if (Event.type == sf::Event::KeyPressed)
			{
				switch (Event.key.code)
				{
				case sf::Keyboard::Up:
					curr = name[index].getString()[0];
					if (curr < '_')
					{
						name[index].setString(++curr);

					}
					break;
				case sf::Keyboard::Down:
					curr = name[index].getString()[0];
					if (curr > 'A')
					{
						name[index].setString(--curr);
					}
					break;
				case sf::Keyboard::Left:
					if (index > 0) index--;
					break;
				case sf::Keyboard::Right:
					if (index < 2) index++;
					break;
				case sf::Keyboard::Return:
					return 1;
					break;
				default:
					break;
				}
			}
		}
		if(index == 0)
		{
			name[0].setFillColor(sf::Color(255, 0, 0, 255));
			name[1].setFillColor(sf::Color(255, 255, 255, 255));
			name[2].setFillColor(sf::Color(255, 255, 255, 255));
		}
		else if (index == 1)
		{
			name[0].setFillColor(sf::Color(255, 255, 255, 255));
			name[1].setFillColor(sf::Color(255, 0, 0, 255));
			name[2].setFillColor(sf::Color(255, 255, 255, 255));
		}
		else if (index == 2)
		{
			name[0].setFillColor(sf::Color(255, 255, 255, 255));
			name[1].setFillColor(sf::Color(255, 255, 255, 255));
			name[2].setFillColor(sf::Color(255, 0, 0, 255));
		}
		App.clear();
		App.draw(back_sprite);
		App.draw(headline);
		App.draw(message);
		for (auto i : name) App.draw(i);
		App.display();
	}
	return -1;
}

std::string Screen_2::get_name()
{
	std::string s;
	for (int i = 0; i < name.size(); i++)
	{
		s += name[i].getString()[0];
	}
	return s;
}