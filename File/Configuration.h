#pragma once

#include <string>
#include <vector>

#include "File\File.h"

class Configuration{

public:

	Configuration();

	~Configuration();

	// Load from file
	bool load(const File& file);

	// Save to file
	bool save(const File& file) const;

	// Children of a node (parent.child1, parent.child2)
	std::vector<std::string> children(const std::string& path, const bool& fullPath = true) const;

	// Node has a value
	bool hasValue(const std::string& path) const;

	// Remove node (and all under it)
	Configuration& remove(const std::string& path);

	// Unset a value to node
	Configuration& unset(const std::string& path);

	// Set value to node
	Configuration& set(const std::string& path, const bool& value);

	// Set value to node
	Configuration& set(const std::string& path, const std::string& value);

	// Set value to node
	Configuration& set(const std::string& path, const float& value);

	// Set value to node
	Configuration& set(const std::string& path, const int& value);

	// Set value to node
	Configuration& set(const std::string& path, const std::vector<std::string>& value);

	// Set value to node
	Configuration& set(const std::string& path, const std::vector<float>& value);

	// Set value to node
	Configuration& set(const std::string& path, const std::vector<int>& value);

	// Get bool value from a node
	bool boolValue(const std::string& path, const bool& default_ = false) const;

	// Get string value from a node
	std::string stringValue(const std::string& path, const std::string& default_ = "") const;

	// Get float value from a node
	float floatValue(const std::string& path, const float& default_ = 0.0f) const;

	// Get int value from a node
	int intValue(const std::string& path, const int& default_ = 0) const;

	// Get string vector from a node
	std::vector<std::string> stringVector(const std::string& path, const std::vector<std::string>& default_ = {}) const;

	// Get float vector from a node
	std::vector<float> floatVector(const std::string& path, const std::vector<float>& default_ = {}) const;

	// Get int vector from a node
	std::vector<int> intVector(const std::string& path, const std::vector<int>& default_ = {}) const;

};
