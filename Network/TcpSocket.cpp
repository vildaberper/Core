#include "Network\TcpSocket.h"

#include "SFML\Network\TcpSocket.hpp"

TcpSocket::TcpSocket(const sf::IpAddress& ip, const unsigned short& port): Socket(ip, port){

}

TcpSocket::~TcpSocket(){
	disconnect();
}

bool TcpSocket::isConnected(){
	connectedMutex.lock();

	bool connected = TcpSocket::connected;

	connectedMutex.unlock();

	return connected;
}

sf::Socket::Status TcpSocket::send(sf::Packet& packet){
	if(!isConnected()){
		return sf::Socket::Status::Disconnected;
	}

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
	if(!isConnected()){
		return sf::Socket::Status::Disconnected;
	}

	mutex.lock();

	if(socket == nullptr){
		mutex.unlock();
		return sf::Socket::Status::Disconnected;
	}

	sf::Socket::Status status = socket->receive(packet);

	bool disconnected = status == sf::Socket::Disconnected;

	connectedMutex.lock();
	connected = !disconnected;
	connectedMutex.unlock();

	if(disconnected){
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

	bool connected = status == sf::Socket::Done;

	connectedMutex.lock();
	TcpSocket::connected = connected;
	connectedMutex.unlock();

	if(!connected){
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
