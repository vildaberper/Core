#pragma once

#include "SFML\Network\TcpListener.hpp"
#include "SFML\Network\TcpSocket.hpp"

#include "Socket.h"

#include <mutex>

class TcpSocket: public Socket{

private:

	sf::TcpSocket* socket = nullptr;
	std::mutex socketMutex;

public:

	void lock();

	void unlock();

	sf::TcpSocket* getSocket();

	void setSocket(sf::TcpSocket* socket);

	virtual bool isConnected();

	virtual sf::Socket::Status send(sf::Packet& packet);

	virtual sf::Socket::Status receive(sf::Packet& packet);

	virtual bool connect(const sf::Time& timeout = sf::milliseconds(1000));

	virtual void disconnect();

};
