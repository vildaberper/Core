#pragma once

#include "SFML\Network\IpAddress.hpp"
#include "SFML\Network\Packet.hpp"
#include "SFML\Network\Socket.hpp"

#include <vector>

class Server{

protected:

	const unsigned short port;

	Server(const unsigned short& port):
		port(port){

	}

public:

	virtual ~Server(){

	}

	unsigned short getPort(){
		return port;
	}

	virtual std::vector<sf::IpAddress> getClients() = 0;

	virtual void handleIncomingClients() = 0;

	virtual sf::Socket::Status send(const sf::IpAddress& ip, sf::Packet& packet) = 0;

	virtual void sendToAllExcept(const sf::IpAddress& ip, sf::Packet& packet) = 0;

	virtual void broadcast(sf::Packet& packet) = 0;

	virtual sf::Socket::Status receive(const sf::IpAddress& ip, sf::Packet& packet) = 0;

	virtual void open() = 0;

	virtual void close() = 0;

};
