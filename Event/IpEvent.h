#pragma once

#include "SFML\Network\IpAddress.hpp"

#include "Event\Event.h"

class IpEvent:
	public virtual Event{

protected:

	const sf::IpAddress ip;

	IpEvent(const sf::IpAddress& ip):
		ip(ip),
		Event(){

	}

public:

	virtual ~IpEvent(){

	}

	sf::IpAddress getIp() const{
		return ip;
	}

};
