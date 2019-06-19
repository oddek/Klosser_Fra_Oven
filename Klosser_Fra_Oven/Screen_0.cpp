#include "Screen_0.h"

Screen_0::Screen_0(void)
{
	
	playing = false;

	Menu1.setFont(summit_font);
	Menu1.setCharacterSize(60);
	Menu1.setString("New Game");
	Menu1Bounds = Menu1.getGlobalBounds();
	Menu1.setPosition({ (width - Menu1Bounds.width) / 2, 250 });

	Menu2.setFont(summit_font);
	Menu2.setCharacterSize(60);
	Menu2.setString("Exit");
	Menu2Bounds = Menu2.getGlobalBounds();
	Menu2.setPosition({ (width - Menu2Bounds.width) / 2, 350 });

	Menu3.setFont(summit_font);
	Menu3.setCharacterSize(60);
	Menu3.setString("Continue");
	Menu3Bounds = Menu3.getGlobalBounds();
	Menu3.setPosition({ (width - Menu3Bounds.width) / 2, 250 });

	level_text.setFont(summit_font);
	level_text.setCharacterSize(40);
	level_text.setString("Choose Level:");
	sf::FloatRect level_text_bounds = level_text.getGlobalBounds();
	level_text.setPosition({ (width - level_text_bounds.width) / 2, 700 });

	for (int i = 0; i < 19; i++)
	{
		sf::Text t;
		t.setFont(summit_font);
		t.setCharacterSize(20);
		t.setString(std::to_string(i));
		int pixelinc = 800 / 19;
		t.setPosition(((width - 800) / 2) + pixelinc * i, 800);
		levelMenu.push_back(t);
	}

}


Screen_0::~Screen_0()
{
}

int Screen_0::Run(sf::RenderWindow &App)
{
	sf::Event Event;
	bool Running = true;
	int menu = 0;

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
					if (menu > 0) menu--;
					break;
				case sf::Keyboard::Down:
					if (menu < 2) menu++;
					else if (menu < 3 && playing) menu++;
					break;
				case sf::Keyboard::Left:
					if (menu == 2 && level > 0 && !playing) level--;
					if (menu == 3 && level > 0 && playing) level--;
					break;
				case sf::Keyboard::Right:
					if (menu == 2 && level < 18 && !playing) level++;
					if (menu == 3 && level < 18 && playing) level++;
					break;
				case sf::Keyboard::Return:
					if (menu == 0 && playing)
					{
						playing = true;
						return (1);
					}
					else if (menu == 2 && playing || menu == 0 && !playing)
					{
						playing = true;
						return (3);
					}
					else if (menu == 3 && playing || menu == 2 && !playing)
					{
						
					}
					else
					{
						return (-1);
					}
					break;
				default:
					break;
				}
			}
		}
		if (menu == 0 && !playing)
		{
			Menu1.setFillColor(sf::Color(255, 0, 0, 255));
			Menu2.setFillColor(sf::Color(255, 255, 255, 255));
			Menu3.setFillColor(sf::Color(255, 0, 0, 255));
			level_text.setFillColor(sf::Color(255, 255, 255, 255));
		}
		else if (menu == 0 && playing)
		{
			Menu1.setFillColor(sf::Color(255, 255, 255, 255));
			Menu2.setFillColor(sf::Color(255, 255, 255, 255));
			Menu3.setFillColor(sf::Color(255, 0, 0, 255));
			level_text.setFillColor(sf::Color(255, 255, 255, 255));
		}
		else if(menu == 1)
		{
			Menu1.setFillColor(sf::Color(255, 255, 255, 255));
			Menu2.setFillColor(sf::Color(255, 0, 0, 255));
			Menu3.setFillColor(sf::Color(255, 255, 255, 255));
			level_text.setFillColor(sf::Color(255, 255, 255, 255));
		}
		else  if (menu == 2 && playing)
		{
			Menu1.setFillColor(sf::Color(255, 0, 0, 255));
			Menu2.setFillColor(sf::Color(255, 255, 255, 255));
			Menu3.setFillColor(sf::Color(255, 255, 255, 255));
			level_text.setFillColor(sf::Color(255, 255, 255, 255));
		}
		else if ((menu == 3 && playing) || (menu == 2 && !playing))
		{
			Menu1.setFillColor(sf::Color(255, 255, 255, 255));
			Menu2.setFillColor(sf::Color(255, 255, 255, 255));
			Menu3.setFillColor(sf::Color(255, 255, 255, 255));
			level_text.setFillColor(sf::Color(255, 0, 0, 255));
		}
		for (int i = 0; i < levelMenu.size(); i++)
		{
			if (i == level) levelMenu[i].setFillColor(sf::Color(255, 0, 0, 255));
			else levelMenu[i].setFillColor(sf::Color(255, 255, 255, 255));
		}

		//Clearing screen
		App.clear();
		//Drawing
		App.draw(back_sprite);
		App.draw(headline);

		if (playing)
		{
			App.draw(Menu3);
			Menu1.setPosition({ (width - Menu1Bounds.width) / 2, 600 });
			App.draw(Menu1);
		}
		else
		{
			Menu1.setPosition({ (width - Menu1Bounds.width) / 2, 250 });
			App.draw(Menu1);
		}
		App.draw(Menu2);
		
		App.draw(level_text);
		for (auto i : levelMenu) App.draw(i);
		App.display();
	}
	return -1;
}
