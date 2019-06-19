#include "cScreen.h"

std::vector<std::tuple<std::string, int>> cScreen::highscores;

cScreen::cScreen(void)
{
	//Background
	background.loadFromFile("img/back1.jpg");
	back_tex.loadFromImage(background);
	back_sprite.setTexture(back_tex);
	//Setting up fonts
	if (!open_sans_font.loadFromFile("fonts/OpenSans-Light.ttf"))throw std::exception("Fant ikke OpenSans-Light.ttf");
	if (!digfont.loadFromFile("fonts/digital-7.ttf")) throw std::exception("Fant ikke digital-7.ttf");;
	if (!head_font.loadFromFile("fonts/headfont.ttf")) throw std::exception("Fant ikke headfont.ttf");
	if (!summit_font.loadFromFile("fonts/SummitLight-Display.ttf")) throw std::exception("Fant ikke SummitLight - Display.ttf");
	//Setting up headline:
	headline.setString("Klosser fra oven");
	headline.setFont(summit_font);
	headline.setCharacterSize(80);
	headline.setFillColor(sf::Color::White);
	headline.setStyle(sf::Text::Bold);
	sf::FloatRect textRect = headline.getLocalBounds();
	headline.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	headline.setPosition(sf::Vector2f((width / 2), 100));
	//Loading highscores
	load_highscores();
}

//cScreen::~cScreen(){}

void cScreen::load_highscores()
{
	highscores.clear();
	std::ifstream ist;
	ist.open("highscores.txt");
	std::string name;
	int score;
	while (ist >> name >> score)
	{
		auto t = std::make_tuple(name, score);
		highscores.push_back(t);
	}
	ist.close();
}

int cScreen::check_highscore(int score)
{
	if (score < std::get<1>(highscores.back())) return -1;
	else
	{
		for (int i = 0; i < highscores.size(); i++)
		{
			if (score > std::get<1>(highscores[i])) return i;
		}
	}
}

void cScreen::save_highscores()
{
	std::ofstream ost;
	ost.open("highscores.txt");

	for (int i = 0; i < highscores.size(); i++)
	{
		ost << std::get<0>(highscores[i]) << " " << std::get<1>(highscores[i]) << "\n";
	}
	ost.close();
}