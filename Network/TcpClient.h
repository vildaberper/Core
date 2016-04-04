#pragma once

#include "Network\Client.h"

#include "Network\TcpSocket.h"

class TcpClient:
	public Client{

private:

	TcpSocket* socket;

public:

	TcpClient(const sf::IpAddress& ip, const unsigned short& port, ClientListener* clientListener);

	virtual ~TcpClient();

	virtual bool isConnected();

	virtual void tick();

	virtual sf::Socket::Status send(sf::Packet& packet);

	virtual sf::Socket::Status receive(sf::Packet& packet);

	virtual bool connect(const sf::Time& timeout = sf::milliseconds(1000));

	virtual void disconnect();

};
