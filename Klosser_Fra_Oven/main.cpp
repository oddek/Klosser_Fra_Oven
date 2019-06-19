#include <SFML/Graphics.hpp>
#include <vector>
#include <Windows.h>
#include "Screen_0.h"
#include "Screen_1.h"
#include "Screen_2.h"
//#include "Screens.h"

int width = 1200;
int height = 1100;




int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	try 
	{
		srand(time(0));
		std::vector<cScreen*> Screens;
		int screen = 0;
	
		cScreen* s0 = new Screen_0();
		Screens.push_back(s0);
		

		sf::RenderWindow App(sf::VideoMode(s0->get_width(), s0->get_height()), "Klosser fra oven");
		App.setMouseCursorVisible(false);
		sf::Image icon;
		icon.loadFromFile("img/icon.png");
		App.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		while (screen >= 0)
		{
			screen = Screens[screen]->Run(App);
			if (screen == 3)
			{
				Screen_1* s = new Screen_1(Screens[0]->get_level());
				if (Screens.size() > 1)
				{
					delete Screens[1];
					Screens[1] = s;
				}
				else Screens.push_back(s);

				screen = 1;
			}
			else if (screen == 4)
			{
				delete Screens[0];
				Screens[0] = new Screen_0();
				
			}
			else if (screen > 4)
			{
				int i = Screens[0]->check_highscore(screen);
				if (i != -1)
				{
					Screen_2* s = new Screen_2();
					s->Run(App);

					auto t = std::make_tuple(s->get_name(), screen);
					Screens[0]->highscores.insert(Screens[0]->highscores.begin() + i, t);
					Screens[0]->highscores.pop_back();
					Screens[0]->save_highscores();
					delete s;
				}
				delete Screens[0];
				Screens[0] = new Screen_0();
				screen = 0;
			}
		
			
		}
		return 0;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		char ch;
		std::cin >> ch;
		return 1;
	}
	catch (...)
	{
		return 2;
	}
	
}


