#include "Network\TcpServer.h"

#include <iterator>

TcpServer::TcpServer(const unsigned short& port, ServerListener* serverListener):
	Server(port, serverListener){
	listening = false;
}

TcpServer::~TcpServer(){
	close();
}

std::vector<ClientId> TcpServer::getClients(){
	std::vector<ClientId> cs;

	mutex.lock();
	for(auto &ent : clients){
		cs.push_back(ent.first);
	}
	mutex.unlock();

	return cs;
}

void TcpServer::tick(){
	mutex.lock();

	if(!listening){
		mutex.unlock();
		return;
	}

	/*
		Incoming connections
	*/
	sf::TcpSocket* client = new sf::TcpSocket();

	client->setBlocking(false);

	if(listener.accept(*client) == sf::Socket::Done){
		ClientId id = nextClientId();
		ClientConnectedEvent event = ClientConnectedEvent(id, client->getRemoteAddress());

		clients.insert(std::make_pair(id, client));

		mutex.unlock();
		serverListener->on(event);
		mutex.lock();

		if(event.isCancelled()){
			clients.erase(id);
			client->disconnect();
			delete client;
		}
	}
	else{
		delete client;
	}

	/*
		Incoming packets
	*/
	for(std::map<ClientId, sf::TcpSocket*>::iterator i = clients.begin(); i != clients.end();){
		sf::Packet packet;
		sf::Socket::Status status = i->second->receive(packet);

		if(status == sf::Socket::Disconnected){
			mutex.unlock();
			serverListener->on(ClientDisconnectedEvent(i->first, i->second->getRemoteAddress()));
			mutex.lock();

			delete i->second;
			i = clients.erase(i);
			continue;
		}
		else if(status == sf::Socket::Done){
			mutex.unlock();
			serverListener->on(ClientPacketEvent(i->first, i->second->getRemoteAddress(), packet));
			mutex.lock();
		}
		else{
			++i;
		}
	}

	mutex.unlock();
}

sf::Socket::Status TcpServer::send(const ClientId& id, sf::Packet& packet){
	mutex.lock();
	if(clients.count(id) > 0){
		sf::Socket::Status status = clients.at(id)->send(packet);
		
		mutex.unlock();

		return status;
	}
	mutex.unlock();
	return sf::Socket::Disconnected;
}

void TcpServer::sendToAllExcept(const ClientId& id, sf::Packet& packet){
	mutex.lock();
	for(auto &ent : clients){
		if(ent.first != id){
			ent.second->send(packet);
		}
	}
	mutex.unlock();
}

void TcpServer::broadcast(sf::Packet& packet){
	mutex.lock();
	for(auto &ent : clients){
		ent.second->send(packet);
	}
	mutex.unlock();
}

void TcpServer::open(){
	mutex.lock();
	if(!listening){
		listener.listen(getPort());
		listener.setBlocking(false);
		listening = true;
	}
	mutex.unlock();
}

bool TcpServer::isOpen(){
	mutex.lock();

	bool listening_ = listening;

	mutex.unlock();

	return listening_;
}

void TcpServer::close(){
	mutex.lock();
	if(listening){
		listener.close();
		listening = false;
	}
	for(auto &ent : clients){
		ent.second->disconnect();
		delete ent.second;
	}
	clients.clear();
	mutex.unlock();
}
