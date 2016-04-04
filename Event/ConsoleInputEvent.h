#pragma once

#include "Event\Event.h"
#include "Event\TextEvent.h"
#include "Event\Cancellable.h"

class ConsoleInputEvent:
	public virtual Event,
	public virtual TextEvent,
	public virtual CancellableEvent{

public:

	ConsoleInputEvent(const std::string& text):
		Event(),
		TextEvent(text),
		CancellableEvent(){

	}

	virtual ~ConsoleInputEvent(){

	}

};
