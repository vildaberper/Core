#pragma once

#include "Event\PacketEvent.h"
#include "Event\Event.h"

class ServerPacketEvent:
	public virtual Event,
	public virtual PacketEvent{

public:

	ServerPacketEvent(sf::Packet& packet):
		Event(),
		PacketEvent(packet){

	}

	virtual ~ServerPacketEvent(){

	}

};
