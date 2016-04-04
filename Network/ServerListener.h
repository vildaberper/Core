#pragma once

#include "Event\ClientDisconnectedEvent.h"
#include "Event\ClientConnectedEvent.h"
#include "Event\ClientPacketEvent.h"

class ServerListener{

protected:

	ServerListener(){

	}

public:

	virtual ~ServerListener(){

	}

	virtual void on(ClientConnectedEvent& event){

	}

	virtual void on(ClientDisconnectedEvent& event){

	}

	virtual void on(ClientPacketEvent& event){

	}

};
