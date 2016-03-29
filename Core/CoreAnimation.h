#pragma once

#include "SFML\Graphics\Texture.hpp"
#include "SFML\Graphics\Rect.hpp"
#include "SFML\System\Time.hpp"

class CoreAnimation{

public:

	CoreAnimation(const sf::Texture& texture, const sf::Time& frameTime, const unsigned int& x, const unsigned int& y, const unsigned int& exclude = 0):
		frameTime(frameTime), texture(texture), x(x), y(y), exclude(exclude),
		width(texture.getSize().x / x), height(texture.getSize().y / y), numFrames(x * y - exclude){

	}

	~CoreAnimation(){

	}

	// Returns the texture atlas used by this animation.
	const sf::Texture& getTexture() const{
		return texture;
	}

	// Returns the width of this animation.
	unsigned int getWidth() const{
		return width;
	}

	// Returns the height of this animation.
	unsigned int getHeight() const{
		return height;
	}

	// Returns number of frames in this animation.
	unsigned int getNumFrames() const{
		return numFrames;
	}

	// Returns the time between frames in this animation.
	sf::Time getFrameTime() const{
		return frameTime;
	}

	// Returns number of frames in the x-axis.
	unsigned int getX() const{
		return x;
	}

	// Returns number of frames in the y-axis.
	unsigned int getY() const{
		return y;
	}

	// Returns number of frames to exclude in the end.
	unsigned int getExclude() const{
		return exclude;
	}

	// Returns the frame number based on time and startTime.
	unsigned int getFrame(const sf::Time& time, const sf::Time& startTime = sf::Time::Zero) const{
		return ((unsigned int) ((time - startTime) / getFrameTime())) % getNumFrames();
	}

	// Returns the texture rect based on time and startTime.
	sf::IntRect getFrameRect(const sf::Time& time, const sf::Time& startTime = sf::Time::Zero) const{
		return getFrameRect(getFrame(time, startTime));
	}

	// Returns the texture rect based on frame.
	sf::IntRect getFrameRect(unsigned int frame) const{
		return sf::IntRect((frame % getX()) * getWidth(), (frame / getX()) * getHeight(), getWidth(), getHeight());
	}

private:

	const sf::Texture& texture;
	const unsigned int width;
	const unsigned int height;
	const unsigned int numFrames;
	const sf::Time frameTime;
	const unsigned int x;
	const unsigned int y;
	const unsigned int exclude;

};
