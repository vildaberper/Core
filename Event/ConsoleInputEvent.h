#pragma once

#include "Event\Event.h"
#include "Event\TextEvent.h"

class ConsoleInputEvent:
	public virtual Event,
	public virtual TextEvent{

public:

	ConsoleInputEvent(const std::string& text):
		Event(),
		TextEvent(text){

	}

	virtual ~ConsoleInputEvent(){

	}

};
