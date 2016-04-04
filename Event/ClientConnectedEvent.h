#pragma once

#include "Event\ClientIdEvent.h"
#include "Event\Cancellable.h"
#include "Event\IpEvent.h"

class ClientConnectedEvent:
	public virtual Event,
	public virtual CancellableEvent,
	public virtual IpEvent,
	public virtual ClientIdEvent{

public:

	ClientConnectedEvent(const ClientId& id, const sf::IpAddress& ip):
		Event(),
		CancellableEvent(),
		IpEvent(ip),
		ClientIdEvent(id){

	}

	virtual ~ClientConnectedEvent(){

	}

};
