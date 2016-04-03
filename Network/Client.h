#pragma once

#include "SFML\Network\IpAddress.hpp"
#include "SFML\Network\Packet.hpp"
#include "SFML\Network\Socket.hpp"
#include "SFML\System\Time.hpp"

class Client{

protected:

	Client(){

	}

public:

	virtual ~Client(){
		
	}

	virtual bool isConnected() = 0;

	virtual sf::Socket::Status send(sf::Packet& packet) = 0;

	virtual sf::Socket::Status receive(sf::Packet& packet) = 0;

	virtual bool connect(const sf::Time& timeout = sf::milliseconds(1000)) = 0;

	virtual void disconnect() = 0;

};
