#include "Animation.h"

Animation::Animation(const sf::Texture& texture, const sf::Time& frameTime, const unsigned int& x, const unsigned int& y, const unsigned int& exclude):
	texture(texture),
	frameTime(frameTime),
	x(x),
	y(y),
	exclude(exclude),
	width(texture.getSize().x / x),
	height(texture.getSize().y / y),
	numFrames(x * y - exclude){

}

Animation::~Animation(){

}

const sf::Texture& Animation::getTexture() const{
	return texture;
}

unsigned int Animation::getWidth() const{
	return width;
}

unsigned int Animation::getHeight() const{
	return height;
}

unsigned int Animation::getNumFrames() const{
	return numFrames;
}

sf::Time Animation::getFrameTime() const{
	return frameTime;
}

unsigned int Animation::getX() const{
	return x;
}

unsigned int Animation::getY() const{
	return y;
}

unsigned int Animation::getExclude() const{
	return exclude;
}

unsigned int Animation::getFrame(const sf::Time& time, const sf::Time& startTime) const{
	return ((unsigned int) ((time - startTime) / getFrameTime())) % getNumFrames();
}

sf::IntRect Animation::getFrameRect(const sf::Time& time, const sf::Time& startTime) const{
	return getFrameRect(getFrame(time, startTime));
}

sf::IntRect Animation::getFrameRect(unsigned int frame) const{
	return sf::IntRect((frame % getX()) * getWidth(), (frame / getX()) * getHeight(), getWidth(), getHeight());
}
