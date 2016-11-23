#pragma once

#include "SFML\Graphics\RenderWindow.hpp"

class Window:
	public sf::RenderWindow{

private:

public:

	Window(const unsigned int& width, const unsigned int& height, const std::string& title){
		create(sf::VideoMode(width, height), title);
	}

	~Window(){

	}

};
