#pragma once

#include "Network\ClientId.h"
#include "Event\Event.h"

class ClientIdEvent:
	public virtual Event{

protected:

	const ClientId id;

	ClientIdEvent(const ClientId& id):
		id(id),
		Event(){

	}

public:

	virtual ~ClientIdEvent(){

	}

	ClientId getId() const{
		return id;
	}

};
