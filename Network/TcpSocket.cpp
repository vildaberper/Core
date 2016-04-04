#include "Network\TcpSocket.h"

#include "SFML\Network\TcpSocket.hpp"

TcpSocket::TcpSocket(const sf::IpAddress& ip, const unsigned short& port): Socket(ip, port){

}

TcpSocket::~TcpSocket(){
	disconnect();
}

void TcpSocket::lock(){
	mutex.lock();
}

void TcpSocket::unlock(){
	mutex.unlock();
}

sf::TcpSocket* TcpSocket::getSocket(){
	return socket;
}

void TcpSocket::setSocket(sf::TcpSocket* socket){
	TcpSocket::socket = socket;
}

bool TcpSocket::isConnected(){
	mutex.lock();

	bool connected = socket != nullptr;

	mutex.unlock();

	return connected;
}

sf::Socket::Status TcpSocket::send(sf::Packet& packet){
	mutex.lock();

	if(socket == nullptr){
		mutex.unlock();
		return sf::Socket::Status::Disconnected;
	}

	sf::Socket::Status status = socket->send(packet);

	mutex.unlock();

	return status;
}

sf::Socket::Status TcpSocket::receive(sf::Packet& packet){
	mutex.lock();

	if(socket == nullptr){
		mutex.unlock();
		return sf::Socket::Status::Disconnected;
	}

	sf::Socket::Status status = socket->receive(packet);

	if(status == sf::Socket::Disconnected){
		delete socket;
		socket = nullptr;
	}

	mutex.unlock();

	return status;
}

bool TcpSocket::connect(const sf::Time& timeout){
	mutex.lock();

	if(socket != nullptr){
		mutex.unlock();
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

	mutex.unlock();

	return success;
}

void TcpSocket::disconnect(){
	mutex.lock();

	if(socket != nullptr){
		socket->disconnect();
		delete socket;
		socket = nullptr;
	}

	mutex.unlock();
}
