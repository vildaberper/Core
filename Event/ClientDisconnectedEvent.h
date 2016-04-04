#pragma once

#include "Event\ClientIdEvent.h"
#include "Event\IpEvent.h"

class ClientDisconnectedEvent:
	public virtual Event,
	public virtual IpEvent,
	public virtual ClientIdEvent{

public:

	ClientDisconnectedEvent(const ClientId& id, const sf::IpAddress& ip):
		Event(),
		IpEvent(ip),
		ClientIdEvent(id){

	}

	virtual ~ClientDisconnectedEvent(){

	}

};
