#pragma once

#include "Event\Event.h"

class CancellableEvent:
	public virtual Event{

protected:

	bool cancelled = false;

	CancellableEvent():
		Event(){

	}

public:

	virtual ~CancellableEvent(){

	}

	void setCancelled(const bool& cancelled){
		CancellableEvent::cancelled = cancelled;
	}

	bool isCancelled() const{
		return cancelled;
	}

};
