#pragma once

#include "SFML\Graphics\Texture.hpp"
#include "SFML\Graphics\Rect.hpp"
#include "SFML\System\Time.hpp"

class Animation{

private:

	const sf::Texture& texture;
	const unsigned int width;
	const unsigned int height;
	const unsigned int numFrames;
	const sf::Time frameTime;
	const unsigned int x;
	const unsigned int y;
	const unsigned int exclude;

public:

	Animation(const sf::Texture& texture, const sf::Time& frameTime, const unsigned int& x, const unsigned int& y, const unsigned int& exclude = 0);

	~Animation();

	// Returns the texture atlas used by this animation.
	const sf::Texture& getTexture() const;

	// Returns the width of this animation.
	unsigned int getWidth() const;

	// Returns the height of this animation.
	unsigned int getHeight() const;

	// Returns number of frames in this animation.
	unsigned int getNumFrames() const;

	// Returns the time between frames in this animation.
	sf::Time getFrameTime() const;

	// Returns number of frames in the x-axis.
	unsigned int getX() const;

	// Returns number of frames in the y-axis.
	unsigned int getY() const;

	// Returns number of frames to exclude in the end.
	unsigned int getExclude() const;

	// Returns the frame number based on time and startTime.
	unsigned int getFrame(const sf::Time& time, const sf::Time& startTime = sf::Time::Zero) const;

	// Returns the texture rect based on time and startTime.
	sf::IntRect getFrameRect(const sf::Time& time, const sf::Time& startTime = sf::Time::Zero) const;

	// Returns the texture rect based on frame.
	sf::IntRect getFrameRect(unsigned int frame) const;

};
