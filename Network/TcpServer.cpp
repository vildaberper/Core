#include "TcpServer.h"

TcpServer::TcpServer(const unsigned short& port): Server(port){

}

TcpServer::~TcpServer(){
	close();
}

std::vector<sf::IpAddress> TcpServer::getClients(){
	std::vector<sf::IpAddress> cs;

	mutex.lock();
	for(size_t i = 0; i < clients.size(); ++i){
		cs.push_back(clients[i]->getRemoteAddress());
	}
	mutex.unlock();

	return cs;
}

void TcpServer::handleIncomingClients(){
	sf::TcpSocket* client = new sf::TcpSocket();

	client = new sf::TcpSocket;
	client->setBlocking(false);

	mutex.lock();
	if(listener.accept(*client) == sf::Socket::Done){
		clients.push_back(client);
	}
	else{
		delete client;
	}
	mutex.unlock();
}

sf::Socket::Status TcpServer::send(const sf::IpAddress& ip, sf::Packet& packet){
	mutex.lock();
	for(size_t i = 0; i < clients.size(); ++i){
		if(clients[i]->getRemoteAddress() == ip){
			sf::Socket::Status status = clients[i]->send(packet);

			mutex.unlock();

			return status;
		}
	}
	mutex.unlock();
	return sf::Socket::Disconnected;
}

void TcpServer::sendToAllExcept(const sf::IpAddress& ip, sf::Packet& packet){
	mutex.lock();
	for(size_t i = 0; i < clients.size(); ++i){
		if(clients[i]->getRemoteAddress() != ip){
			clients[i]->send(packet);
		}
	}
	mutex.unlock();
}

void TcpServer::broadcast(sf::Packet& packet){
	mutex.lock();
	for(size_t i = 0; i < clients.size(); ++i){
		clients[i]->send(packet);
	}
	mutex.unlock();
}

sf::Socket::Status TcpServer::receive(const sf::IpAddress& ip, sf::Packet& packet){
	mutex.lock();
	for(size_t i = 0; i < clients.size(); ++i){
		if(clients[i]->getRemoteAddress() == ip){
			sf::Socket::Status status = clients[i]->receive(packet);

			mutex.unlock();

			return status;
		}
	}
	mutex.unlock();
	return sf::Socket::Disconnected;
}

void TcpServer::open(){
	mutex.lock();
	listener.listen(getPort());
	listener.setBlocking(false);
	mutex.unlock();
}

void TcpServer::close(){
	mutex.lock();
	listener.close();
	for(size_t i = 0; i < clients.size(); ++i){
		clients[i]->disconnect();
		delete clients[i];
	}
	clients.clear();
	mutex.unlock();
}
