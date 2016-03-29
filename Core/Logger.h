#pragma once

#include <string>
#include <vector>

#include "SFML\System\Clock.hpp"

namespace logger{
	enum LogLevel{
		INFO,
		DEBUG,
		WARNING,
		FATAL,
		TIMING
	};

	extern sf::Clock clock;

	class LogEntry{
	public:
		LogEntry(const std::string& message){
			LogEntry::message = message;
			time = logger::clock.getElapsedTime();
		}

		~LogEntry(){ }

		std::string message;
		sf::Time time;
	};

	extern std::vector<LogEntry> history;
	extern size_t historyCount;

	void log(const std::string& message, const LogLevel& level);

	void info(const std::string& message);

	void debug(const std::string& message);

	void warning(const std::string& message);

	void fatal(const std::string& message);

	void timing(const std::string& message);
}
