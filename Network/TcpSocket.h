#pragma once

#include "Network\Socket.h"

#include "SFML\Network\TcpListener.hpp"
#include "SFML\Network\TcpSocket.hpp"

#include <mutex>

class TcpSocket:
	public Socket{

private:

	bool connected = false;
	std::mutex connectedMutex;

	sf::TcpSocket* socket = nullptr;
	std::mutex mutex;

public:

	TcpSocket(const sf::IpAddress& ip, const unsigned short& port);

	virtual ~TcpSocket();

	virtual bool isConnected();

	virtual sf::Socket::Status send(sf::Packet& packet);

	virtual sf::Socket::Status receive(sf::Packet& packet);

	virtual bool connect(const sf::Time& timeout = sf::milliseconds(1000));

	virtual void disconnect();

};
