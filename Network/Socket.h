#pragma once

#include "SFML\Network\IpAddress.hpp"
#include "SFML\Network\Packet.hpp"
#include "SFML\Network\Socket.hpp"
#include "SFML\System\Time.hpp"

class Socket{

protected:

	const sf::IpAddress ip;
	const unsigned short port;

	Socket(const sf::IpAddress& ip, const unsigned short& port):
		ip(ip),
		port(port){

	}

public:

	virtual ~Socket(){

	}

	sf::IpAddress getIp() const{
		return ip;
	}

	unsigned short getPort() const{
		return port;
	}

	virtual bool isConnected() = 0;

	virtual sf::Socket::Status send(sf::Packet& packet) = 0;

	virtual sf::Socket::Status receive(sf::Packet& packet) = 0;

	virtual bool connect(const sf::Time& timeout = sf::milliseconds(1000)) = 0;

	virtual void disconnect() = 0;

};
