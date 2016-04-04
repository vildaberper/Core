#pragma once

#include <string>

#include "Event\Event.h"

class TextEvent:
	public virtual Event{

protected:

	const std::string text;

	TextEvent(const std::string& text):
		text(text),
		Event(){

	}

public:

	virtual ~TextEvent(){

	}

	std::string getText() const{
		return text;
	}

};
