#pragma once

#include "Event\ConsoleInputEvent.h"

class ConsoleListener{

protected:

	ConsoleListener(){

	}

public:

	~ConsoleListener(){

	}

	virtual void on(ConsoleInputEvent& event){

	}

};
