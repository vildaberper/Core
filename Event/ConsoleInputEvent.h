#pragma once

#include <vector>

#include "System\StringUtils.h"

#include "Event\Event.h"
#include "Event\TextEvent.h"
#include "Event\Cancellable.h"

class ConsoleInputEvent:
	public virtual Event,
	public virtual TextEvent,
	public virtual CancellableEvent{

protected:

	const std::vector<std::string> args;

public:

	ConsoleInputEvent(const std::string& text):
		args(splitAsCommand(text)),
		Event(),
		TextEvent(text),
		CancellableEvent(){

	}

	virtual ~ConsoleInputEvent(){

	}

	std::vector<std::string> getArgs(){
		return args;
	}

};
