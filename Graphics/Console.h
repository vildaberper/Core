#pragma once

#include "SFML\Graphics\Color.hpp"
#include "SFML\Graphics\Font.hpp"
#include "SFML\Graphics\Text.hpp"
#include "SFML\Window.hpp"

#include <string>
#include <vector>
#include <mutex>

#include "Graphics\ConsoleListener.h"
#include "Graphics\Window.h"

#include "File\File.h"

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
	bool newLine = false;

	sf::Font font;
	sf::Color background;

	sf::Text text;
	Window* window;

	sf::Clock clock;

	void run(const sf::Font& font,
		const std::string& title,
		ConsoleListener* consoleListener,
		const unsigned int& fontSize,
		const unsigned int& width,
		const unsigned int& height,
		const sf::Color& background,
		const sf::Color& fontColor);

public:

	static bool loadDefaultFont(sf::Font& font);

	Console(
		const std::string& title = "Console",
		ConsoleListener* consoleListener = nullptr,
		const unsigned int& fontSize = 16,
		const unsigned int& width = 800,
		const unsigned int& height = 600,
		const sf::Color& background = sf::Color::Black,
		const sf::Color& fontColor = sf::Color::White
	);

	Console(
		const File& fontFile,
		const std::string& title = "Console",
		ConsoleListener* consoleListener = nullptr,
		const unsigned int& fontSize = 16,
		const unsigned int& width = 800,
		const unsigned int& height = 600,
		const sf::Color& background = sf::Color::Black,
		const sf::Color& fontColor = sf::Color::White
		);

	~Console();

	bool isOpen();

	void close();

	void print(const std::string& string);

	void println(const std::string& string = "");

	std::vector<std::string> getHistory();

	void clear();

};
