#include "Console.h"

Console::Console(
	const sf::Font& font,
	const std::string& title,
	ConsoleListener* consoleListener,
	const unsigned int& fontSize,
	const unsigned int& width,
	const unsigned int& height,
	const sf::Color& background,
	const sf::Color& fontColor):
	background(background){

	Console::consoleListener = consoleListener;

	text.setFont(font);
	text.setFillColor(fontColor);
	text.setCharacterSize(fontSize);

	open = true;
	shouldClose = false;

	thread = std::thread([this, consoleListener, background, width, height, title]{

		window = new Window(width, height, title);
		window->setFramerateLimit(30);

		while(true){
			openMutex.lock();
			if(!(open = window->isOpen()) || shouldClose){
				window->close();
				open = false;
				openMutex.unlock();
				break;
			}
			openMutex.unlock();

			sf::Event event;
			while(window->pollEvent(event)){
				switch(event.type){

				case sf::Event::Closed:
					window->close();
					break;

				case sf::Event::Resized:
					window->setView(sf::View(sf::FloatRect(0.0f, 0.0f, float(event.size.width), float(event.size.height))));
					break;

				case sf::Event::TextEntered:
				{
					mutex.lock();
					if(event.text.unicode == 13){
						if(input.length() > 0){
							ConsoleInputEvent event(input);

							mutex.unlock();
							if(consoleListener != nullptr) consoleListener->on(event);
							mutex.lock();

							if(!event.isCancelled()){
								input.clear();
							}
						}
					}
					else if(event.text.unicode == '\b'){
						if(input.length() > 0){
							input.pop_back();
						}
					}
					else{
						input.push_back(event.text.unicode);
					}
					mutex.unlock();
					break;
				}

				}
			}

			window->clear(background);

			float x = text.getCharacterSize() / 2.0f;
			float y = window->getSize().y - text.getCharacterSize() / 2.0f;

			mutex.lock();
			if(!input.empty() || window->hasFocus()){
				text.setPosition(x, y -= text.getCharacterSize());
				text.setString(">" + input + (clock.getElapsedTime().asMilliseconds() % 1000 < 500 && window->hasFocus() ? "_" : ""));
				window->draw(text);
			}else{
				y += 5;
			}
			for(size_t i = 1; i <= history.size(); ++i){
				text.setPosition(x, y -= text.getCharacterSize() + 5);

				if(-y > text.getCharacterSize()){
					break;
				}

				text.setString(history[history.size() - i]);
				window->draw(text);
			}
			mutex.unlock();

			window->display();
		}

	});

}

Console::~Console(){
	close();

	thread.join();

	delete window;
}

bool Console::isOpen(){
	openMutex.lock();

	bool open = Console::open;

	openMutex.unlock();

	return open;
}

void Console::close(){
	openMutex.lock();

	shouldClose = true;

	openMutex.unlock();
}

void Console::print(const std::string& string){
	mutex.lock();

	if(newLine || history.empty()){
		history.push_back(string);
	}
	else{
		history[history.size() - 1].append(string.begin(), string.end());
	}
	newLine = false;

	mutex.unlock();
}

void Console::println(const std::string& string){
	mutex.lock();

	if(newLine || history.empty()){
		history.push_back(string);
	}
	else{
		history[history.size() - 1].append(string.begin(), string.end());
	}
	newLine = true;

	if(history.size() > 100){
		history.erase(history.begin(), history.begin() + (history.size() - 100));
	}

	mutex.unlock();
}

std::vector<std::string> Console::getHistory(){
	mutex.lock();

	std::vector<std::string> history(Console::history);

	mutex.unlock();

	return history;
}

void Console::clear(){
	mutex.lock();

	history.clear();

	mutex.unlock();
}
