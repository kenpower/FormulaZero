#pragma once
#include "SFML/Graphics.hpp" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 
const float SCREEN_WIDTH = 1500;   // the size of the screen in pixels used in the game
const float SCREEN_HEIGHT = 800;

class Window
{
	sf::Font m_font;  // font for writing text
	sf::Text m_message;  // text to write on the screen
	sf::RenderWindow window;
public:
	Window():window(sf::VideoMode(static_cast<int>(SCREEN_WIDTH), static_cast<int>(SCREEN_HEIGHT)), "Joint Project Game", sf::Style::Default)
	{}

	void beginFrame() { window.clear(); }
	void displayFrame() { window.display(); }

	sf::RenderWindow* getWindow() { return &window; };

};

/*
	if (!m_font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "error with font file file";
	}

	// set up the message string
	m_message.setFont(m_font);  // set the font for the text
	m_message.setCharacterSize(24); // set the text size
	m_message.setFillColor(sf::Color::White); // set the text colour
	m_message.setPosition(10, 10);  // its position on the screen*/

