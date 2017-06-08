#include "File\Configuration.h"

#include <fstream>
#include <iostream>

#include "System\Util.h"
#include "System\Output.h"
#include "System\StringUtils.h"

const std::string FILE_INDENT = "  ";
const char PATH_SEPARATOR = '.';
const char VALUE_INDICATOR = ':';
const char COMMENT_INDICATOR = '#';
const char ENDL = '\n';

enum Type { INT, FLOAT, BOOL, STRING, VINT, VFLOAT, VBOOL, VSTRING };

class ConfigurationNode {

private:

	Type type_;
	void* data_;

	std::map<std::string, ConfigurationNode> children_;

	std::vector<std::string> buildvec(const std::string& string) {
		std::vector<std::string> elems = { "" };
		bool inquote = false;
		for (size_t i = 1; i < string.length() - 1; ++i) {
			if (string[i] == '"') inquote = !inquote;
			if (!inquote && string[i] == ',') elems.push_back("");
			else if (inquote || string[i] != ' ') elems[elems.size() - 1] += string[i];
		}
		if (elems.size() == 1 && elems[0].empty()) elems.clear();
		return elems;
	}

public:

	ConfigurationNode() { data_ = nullptr; }

	~ConfigurationNode() { unset(); children_.clear(); }

	bool hasChildren() const { return !children_.empty(); }

	const std::map<std::string, ConfigurationNode>& children() const { return children_; }

	ConfigurationNode* getNode(const std::string& path) {
		if (path.empty()) return this;

		size_t i = path.find_first_of(PATH_SEPARATOR);
		if (i == std::string::npos) {
			if (children_.count(path)) return &children_[path];
			return nullptr;
		}
		std::string sub = path.substr(0, i);
		if (children_.count(sub)) return children_[sub].getNode(path.substr(i + 1));
		return nullptr;
	}

	ConfigurationNode* createNode(const std::string& path) {
		if (path.empty()) return this;

		size_t i = path.find_first_of(PATH_SEPARATOR);
		if (i == std::string::npos) return &children_[path];
		return children_[path.substr(0, i)].createNode(path.substr(i + 1));
	}

	bool removeNode(const std::string& path) {
		size_t i = path.find_first_of(PATH_SEPARATOR);
		if (i == std::string::npos) return children_.erase(path) > 0;
		else {
			std::string sub = path.substr(0, i);
			if (children_.count(sub)) return children_[sub].removeNode(path.substr(i + 1));
		}
		return false;
	}

	inline bool hasValue() const { return data_ != nullptr; }

	template <typename T> inline const T& get() const { return *cast<T>(data_); }

	inline bool unset() {
		if (data_) {
			switch (type_) {
			case INT: delete cast<int>(data_); break;
			case FLOAT: delete cast<float>(data_); break;
			case BOOL: delete cast<bool>(data_); break;
			case STRING: delete cast<std::string>(data_); break;
			case VINT: delete cast<std::vector<int>>(data_); break;
			case VFLOAT: delete cast<std::vector<float>>(data_); break;
			case VBOOL: delete cast<std::vector<bool>>(data_); break;
			case VSTRING: delete cast<std::vector<std::string>>(data_); break;
			}
			data_ = nullptr;
			return true;
		}
		return false;
	}

	void set(const int& v) { unset(); type_ = INT; data_ = new int(v); }
	void set(const float& v) { unset(); type_ = FLOAT; data_ = new float(v); }
	void set(const bool& v) { unset(); type_ = BOOL; data_ = new bool(v); }
	void set(const std::string& v) { unset(); type_ = STRING; data_ = new std::string(v); } void set(const char* v) { set(std::string(v)); }
	void set(const std::vector<int>& v) { unset(); type_ = VINT; data_ = new std::vector<int>(v); }
	void set(const std::vector<float>& v) { unset(); type_ = VFLOAT; data_ = new std::vector<float>(v); }
	void set(const std::vector<bool>& v) { unset(); type_ = VBOOL; data_ = new std::vector<bool>(v); }
	void set(const std::vector<std::string>& v) { unset(); type_ = VSTRING; data_ = new std::vector<std::string>(v); }

	std::string str() const {
		std::string result;
		if (!data_) return result;
		switch (type_) {
		case INT: return toString(get<int>());
		case FLOAT: return toString(get<float>());
		case BOOL: return toString(get<bool>());
		case STRING: return toString(get<std::string>());
		case VINT: return toString(get<std::vector<int>>());
		case VFLOAT: return toString(get<std::vector<float>>());
		case VBOOL: return toString(get<std::vector<bool>>());
		case VSTRING: return toString(get<std::vector<std::string>>());
		}
		return result;
	}

	bool parse(std::string string) {
		string = trim(string);
		if (isint(string)) set(stoi(string));
		else if (isfloat(string)) set(stof(string));
		else if (isbool(string)) set(stob(string));
		else if (isstring(string)) set(stos(string));
		else {
			Type type = INT;
			if (string.length() > 2 && string[0] == '(') {
				size_t typeindex = string.find_first_of(')');
				if (typeindex != std::string::npos) {
					std::string tmp = string.substr(1, typeindex - 1);
					string = string.substr(typeindex + 1);
					if (tmp == "int") type = VINT;
					else if (tmp == "float") type = VFLOAT;
					else if (tmp == "bool") type = VBOOL;
					else if (tmp == "string") type = VSTRING;
				}
			}
			if (isvector(string)) {
				std::vector<std::string> elems = buildvec(string);
				if (type < VINT) {
					if (elems.empty()) return false;
					else if (isint(elems[0])) type = VINT;
					else if (isfloat(elems[0])) type = VFLOAT;
					else if (isbool(elems[0])) type = VBOOL;
					else if (isstring(elems[0])) type = VSTRING;
				}

				switch (type) {
				case VINT: {
					std::vector<int> v;
					for (const std::string& s : elems) v.push_back(stoi(s));
					set(v);
					break;
				}
				case VFLOAT: {
					std::vector<float> v;
					for (const std::string& s : elems) v.push_back(stof(s));
					set(v);
					break;
				}
				case VBOOL: {
					std::vector<bool> v;
					for (const std::string& s : elems) v.push_back(stob(s));
					set(v);
					break;
				}
				case VSTRING: {
					std::vector<std::string> v;
					for (const std::string& s : elems) v.push_back(stos(s));
					set(v);
					break;
				}
				default: return false;
				}
			}
			else return false;
		}
		return true;
	}

};

Configuration::Configuration() { root = new ConfigurationNode(); }

Configuration::~Configuration() { delete root; }

const std::map<std::string, ConfigurationNode> Configuration::children(const std::string& path) const {
	ConfigurationNode* n = root->getNode(path);
	if (n) return n->children();
	return{};
}

void Configuration::clear() { delete root; root = new ConfigurationNode(); }

bool Configuration::remove(const std::string& path) { return root->removeNode(path); }

template<typename T> inline const T& Configuration::get(const std::string& path, const T& default) const {
	ConfigurationNode* n = root->getNode(path);
	if (n && n->hasValue()) return n->get<T>();
	return default;
}

const int& Configuration::getInt(const std::string& path, const int& default) const { return get<int>(path, default); }
const float& Configuration::getFloat(const std::string& path, const float& default) const { return get<float>(path, default); }
const bool& Configuration::getBool(const std::string& path, const bool& default) const { return get<bool>(path, default); }
const std::string& Configuration::getString(const std::string& path, const std::string& default) const { return get<std::string>(path, default); }
const std::vector<int>& Configuration::getVectorInt(const std::string& path, const std::vector<int>& default) const { return get<std::vector<int>>(path, default); }
const std::vector<float>& Configuration::getVectorFloat(const std::string& path, const std::vector<float>& default) const { return get<std::vector<float>>(path, default); }
const std::vector<bool>& Configuration::getVectorBool(const std::string& path, const std::vector<bool>& default) const { return get<std::vector<bool>>(path, default); }
const std::vector<std::string>& Configuration::getVectorString(const std::string& path, const std::vector<std::string>& default) const { return get<std::vector<std::string>>(path, default); }

bool Configuration::unset(const std::string& path) {
	ConfigurationNode* n = root->getNode(path);
	if (n) return n->unset();
	return false;
}

void Configuration::set(const std::string& path, const int& v) { root->createNode(path)->set(v); }
void Configuration::set(const std::string& path, const float& v) { root->createNode(path)->set(v); }
void Configuration::set(const std::string& path, const bool& v) { root->createNode(path)->set(v); }
void Configuration::set(const std::string& path, const std::string& v) { root->createNode(path)->set(v); }
void Configuration::set(const std::string& path, const char* v) { set(path, std::string(v)); }
void Configuration::set(const std::string& path, const std::vector<int>& v) { root->createNode(path)->set(v); }
void Configuration::set(const std::string& path, const std::vector<float>& v) { root->createNode(path)->set(v); }
void Configuration::set(const std::string& path, const std::vector<bool>& v) { root->createNode(path)->set(v); }
void Configuration::set(const std::string& path, const std::vector<std::string>& v) { root->createNode(path)->set(v); }

void err_parse(const std::string& message, const size_t& num, const std::string& line, const std::string& level = "error") {
	outc << "Parse " << level << ": line " << num << " [" << message << "] (" << line << ')' << std::endl;
}

bool Configuration::in(std::istream& stream) {
	bool success = true;
	size_t num = 0;
	std::string line;
	std::vector<ConfigurationNode*> cnode = { root };
	size_t cdepth = 0;
	while (std::getline(stream, line)) {
		++num;

		size_t depth = stripStartCount(line, FILE_INDENT) + 1;
		size_t value_index = line.find_first_of(VALUE_INDICATOR);
		size_t comment_index = line.find_first_not_of(' ');

		if (comment_index == std::string::npos || line[comment_index] == COMMENT_INDICATOR) continue;

		if (value_index == std::string::npos) {
			err_parse("no value inducator found", num, line);
			return false;
		}

		std::string name = trim(line.substr(0, value_index));
		std::string value = trim(line.substr(value_index + 1));

		if (depth > cdepth && depth != ++cdepth) {
			err_parse("bad indentation", num, line);
			return false;
		}
		else if (depth < cdepth) cdepth = depth;

		ConfigurationNode* node = cnode[cdepth - 1]->createNode(name);
		if (cnode.size() <= cdepth) cnode.push_back(node);
		else cnode[cdepth] = node;
		if (!value.empty() && value[0] != COMMENT_INDICATOR && !node->parse(value)) {
			err_parse("bad value", num, line, "warning");
			success = false;
		}
	}
	return success;
}

bool Configuration::load(const File& file, const bool& clear) {
	std::ifstream ifs;
	ifs.open(file.path().data(), std::ios_base::in);
	if (!ifs.is_open()) return false;
	if (clear) Configuration::clear();

	if (!in(ifs)) {
		outc << "In file: " << file.path() << std::endl;
		return false;
	}

	return true;
}

void out_(std::ostream& ofs, const ConfigurationNode& node, const std::string& name, const size_t& depth = 0) {
	for (size_t i = 0; i < depth; ++i) ofs << FILE_INDENT;
	ofs << name << VALUE_INDICATOR;
	if (node.hasValue()) ofs << ' ' << node.str();
	ofs << ENDL;
	for (auto const& child : node.children()) out_(ofs, child.second, child.first, depth + 1);
}

void Configuration::out(std::ostream& stream) const {
	for (auto const& child : root->children()) out_(stream, child.second, child.first);
}

bool Configuration::save(const File& file) const {
	std::ofstream ofs;
	ofs.open(file.path().data(), std::ios_base::out | std::ios_base::trunc);
	if (!ofs.is_open()) return false;

	out(ofs);

	return true;
}