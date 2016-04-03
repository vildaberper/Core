#pragma once

#include "Server.h"

#include "SFML\Network\TcpListener.hpp"
#include "SFML\Network\TcpSocket.hpp"

#include <vector>
#include <mutex>

class TcpServer: public Server{

private:

	std::vector<sf::TcpSocket*> clients;

	sf::TcpListener listener;

	std::mutex mutex;

public:

	TcpServer(const unsigned short& port);

	virtual ~TcpServer();

	virtual std::vector<sf::IpAddress> getClients();

	virtual void handleIncomingClients();

	virtual sf::Socket::Status send(const sf::IpAddress& ip, sf::Packet& packet);

	virtual void sendToAllExcept(const sf::IpAddress& ip, sf::Packet& packet);

	virtual void broadcast(sf::Packet& packet);

	virtual sf::Socket::Status receive(const sf::IpAddress& ip, sf::Packet& packet);

	virtual void open();

	virtual void close();

};
