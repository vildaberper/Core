#pragma once

#include "Network\Server.h"

#include "SFML\Network\TcpListener.hpp"
#include "SFML\Network\TcpSocket.hpp"

#include <map>
#include <mutex>

class TcpServer:
	public Server{

private:

	std::map<ClientId, sf::TcpSocket*> clients;

	sf::TcpListener listener;

	std::mutex mutex;

	bool listening;

public:

	TcpServer(const unsigned short& port, ServerListener* serverListener);

	virtual ~TcpServer();

	virtual std::vector<ClientId> getClients();

	virtual void tick();

	virtual sf::Socket::Status send(const ClientId& id, sf::Packet& packet);

	virtual void sendToAllExcept(const ClientId& id, sf::Packet& packet);

	virtual void broadcast(sf::Packet& packet);

	virtual void open();

	virtual bool isOpen();

	virtual void close();

};
