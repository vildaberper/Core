#pragma once

#include "SFML\Network\IpAddress.hpp"
#include "SFML\Network\Packet.hpp"
#include "SFML\Network\Socket.hpp"

#include <vector>

#include "Network\ServerListener.h"
#include "Network\ClientId.h"

class Server{

protected:

	const unsigned short port;

	ServerListener* serverListener;

	Server(const unsigned short& port, ServerListener* serverListener):
		port(port){
		Server::serverListener = serverListener;
	}

public:

	virtual ~Server(){

	}

	unsigned short getPort(){
		return port;
	}

	virtual std::vector<ClientId> getClients() = 0;

	virtual void tick() = 0;

	virtual sf::Socket::Status send(const ClientId& id, sf::Packet& packet) = 0;

	virtual void sendToAllExcept(const ClientId& id, sf::Packet& packet) = 0;

	virtual void broadcast(sf::Packet& packet) = 0;

	virtual void open() = 0;

	virtual bool isOpen() = 0;

	virtual void close() = 0;

};
