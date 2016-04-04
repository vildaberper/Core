#include "Network\TcpClient.h"

TcpClient::TcpClient(const sf::IpAddress& ip, const unsigned short& port, ClientListener* clientListener):
	Client(ip, port, clientListener){
	socket = new TcpSocket(ip, port);
}

TcpClient::~TcpClient(){
	delete socket;
}

void TcpClient::tick(){
	/*
		Incoming packets
	*/
	bool received = false;

	do{
		sf::Packet packet;

		if(received = receive(packet) == sf::Socket::Done){
			clientListener->on(ServerPacketEvent(packet));
		}
	} while(received);
}

bool TcpClient::isConnected(){
	return socket->isConnected();
}

sf::Socket::Status TcpClient::send(sf::Packet& packet){
	return socket->send(packet);
}

sf::Socket::Status TcpClient::receive(sf::Packet& packet){
	return socket->receive(packet);
}

bool TcpClient::connect(const sf::Time& timeout){
	return socket->connect(timeout);
}

void TcpClient::disconnect(){
	socket->disconnect();
}
