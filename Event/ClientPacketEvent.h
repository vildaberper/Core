#pragma once

#include "Event\ClientIdEvent.h"
#include "Event\PacketEvent.h"
#include "Event\IpEvent.h"
#include "Event\Event.h"

class ClientPacketEvent:
	public virtual Event,
	public virtual PacketEvent,
	public virtual IpEvent,
	public virtual ClientIdEvent{

public:

	ClientPacketEvent(const ClientId& id, const sf::IpAddress& ip, sf::Packet& packet):
		Event(),
		PacketEvent(packet),
		IpEvent(ip),
		ClientIdEvent(id){

	}

	virtual ~ClientPacketEvent(){

	}

};
