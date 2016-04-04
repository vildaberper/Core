#pragma once

#include "SFML\Network\Packet.hpp"

#include "Event\Event.h"

class PacketEvent:
	public virtual Event{

protected:

	sf::Packet packet;

	PacketEvent(sf::Packet& packet):
		Event(){
		PacketEvent::packet = packet;
	}

public:

	virtual ~PacketEvent(){

	}

	sf::Packet& getPacket(){
		return packet;
	}

};
