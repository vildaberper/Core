#pragma once

#include "Event\ServerPacketEvent.h"

class ClientListener{

protected:

	ClientListener(){

	}

public:

	virtual ~ClientListener(){

	}

	virtual void on(ServerPacketEvent& event){

	}

};
