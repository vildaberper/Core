#pragma once

#include "File\File.h"
#include "File\ConfigurationSection.h"

class Configuration : public ConfigurationSection {

public:

	Configuration();

	Configuration(const File& file);

	~Configuration();

	void clear();

	bool in(std::istream& stream, const bool& clear = true);

	bool load(const File& file, const bool& clear = true);

	void out(std::ostream& stream) const;

	bool save(const File& file) const;

};