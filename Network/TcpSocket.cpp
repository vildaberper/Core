#include "TcpSocket.h"

#include "SFML\Network\TcpSocket.hpp"

void TcpSocket::lock(){
	socketMutex.lock();
}

void TcpSocket::unlock(){
	socketMutex.unlock();
}

sf::TcpSocket* TcpSocket::getSocket(){
	return socket;
}

void TcpSocket::setSocket(sf::TcpSocket* socket){
	TcpSocket::socket = socket;
}

bool TcpSocket::isConnected(){
	socketMutex.lock();

	bool connected = socket != nullptr;

	socketMutex.unlock();

	return connected;
}

sf::Socket::Status TcpSocket::send(sf::Packet& packet){
	socketMutex.lock();

	if(socket == nullptr){
		socketMutex.unlock();
		return sf::Socket::Status::Disconnected;
	}

	sf::Socket::Status status = socket->send(packet);

	socketMutex.unlock();

	return status;
}

sf::Socket::Status TcpSocket::receive(sf::Packet& packet){
	socketMutex.lock();

	if(socket == nullptr){
		socketMutex.unlock();
		return sf::Socket::Status::Disconnected;
	}

	sf::Socket::Status status = socket->receive(packet);

	socketMutex.unlock();

	return status;
}

bool TcpSocket::connect(const sf::Time& timeout){
	socketMutex.lock();

	if(socket != nullptr){
		socketMutex.unlock();
		return true;
	}

	sf::Socket::Status status = (socket = new sf::TcpSocket())->connect(ip, port, timeout);

	if(status != sf::Socket::Done){
		delete socket;
		socket = nullptr;
	}
	else{
		socket->setBlocking(false);
	}

	bool success = socket != nullptr;

	socketMutex.unlock();

	return success;
}

void TcpSocket::disconnect(){
	socketMutex.lock();

	if(socket != nullptr){
		socket->disconnect();
		delete socket;
		socket = nullptr;
	}

	socketMutex.unlock();
}
