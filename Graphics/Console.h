#pragma once

#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\Color.hpp"
#include "SFML\Graphics\Font.hpp"
#include "SFML\Graphics\Text.hpp"
#include "SFML\Window.hpp"

#include <string>
#include <vector>
#include <mutex>

#include "Graphics\ConsoleListener.h"

class Console{

private:

	ConsoleListener* consoleListener;

	bool open;
	bool shouldClose;
	std::mutex mutex;
	std::mutex openMutex;
	std::thread thread;
	std::vector<std::string> history;
	std::string input;

	const sf::Color background;

	sf::Text text;
	sf::RenderWindow* window;

	sf::Clock clock;

public:

	Console(
		const sf::Font& font,
		const std::string& title = "Console",
		ConsoleListener* consoleListener = nullptr,
		const unsigned int& fontSize = 30,
		const unsigned int& width = 800,
		const unsigned int& height = 600,
		const sf::Color& background = sf::Color::Black,
		const sf::Color& fontColor = sf::Color::White
		);

	~Console();

	bool isOpen();

	void close();

	void print(const std::string& string);

	void println(const std::string& string);

	std::vector<std::string> getHistory();

	void clear();

};
