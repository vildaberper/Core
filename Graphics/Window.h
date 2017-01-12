#pragma once

#include "SFML\Graphics\RenderWindow.hpp"

class Window:
	public sf::RenderWindow{

private:

	const unsigned int width;
	const unsigned int height;
	const std::string title;

public:

	Window(const std::string& title = "Window", const unsigned int& width = 800, const unsigned int& height = 600):
		title(title),width(width),height(height){
		
	}

	~Window(){

	}

	void createDefault(){
		create(sf::VideoMode(width, height), title);
	}

	void createOpenGL(const unsigned int& antialiasingLevel = 4){
		sf::ContextSettings settings;
		settings.depthBits = 24;
		settings.stencilBits = 8;
		settings.antialiasingLevel = antialiasingLevel;
		settings.majorVersion = 3;
		settings.minorVersion = 0;

		create(sf::VideoMode(width, height), title, sf::Style::Default, settings);
	}

};
