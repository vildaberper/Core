#include "Network\ClientId.h"

#include <mutex>

ClientId current = 0;

std::mutex mutex;

ClientId nextClientId(){
	mutex.lock();

	ClientId id = current++;

	mutex.unlock();

	return id;
}
