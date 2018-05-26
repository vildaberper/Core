#pragma once

#include <map>
#include <vector>

class ConfigurationNode;

class ConfigurationSection {

private:

	ConfigurationSection(ConfigurationNode* root);

protected:

	ConfigurationNode* root_;

public:

	ConfigurationSection();

	~ConfigurationSection();

	std::map<std::string, ConfigurationSection> children(const std::string& path = "");

	bool hasSection(const std::string& path) const;

	ConfigurationSection getSection(const std::string& path);

	bool remove(const std::string& path);

	template<typename T> inline const T& get(const std::string& path, const T& default) const;

	const int& getInt(const std::string& path, const int& default = 0) const;
	const float& getFloat(const std::string& path, const float& default = 0.f) const;
	const bool& getBool(const std::string& path, const bool& default = false) const;
	const std::string& getString(const std::string& path, const std::string& default = "") const;
	const std::vector<int>& getVectorInt(const std::string& path, const std::vector<int>& default = {}) const;
	const std::vector<float>& getVectorFloat(const std::string& path, const std::vector<float>& default = {}) const;
	const std::vector<bool>& getVectorBool(const std::string& path, const std::vector<bool>& default = {}) const;
	const std::vector<std::string>& getVectorString(const std::string& path, const std::vector<std::string>& default = {}) const;

	bool unset(const std::string& path);

	void set(const std::string& path, const int& v);
	void set(const std::string& path, const float& v);
	void set(const std::string& path, const bool& v);
	void set(const std::string& path, const std::string& v);
	void set(const std::string& path, const char* v);
	void set(const std::string& path, const std::vector<int>& v);
	void set(const std::string& path, const std::vector<float>& v);
	void set(const std::string& path, const std::vector<bool>& v);
	void set(const std::string& path, const std::vector<std::string>& v);

};
