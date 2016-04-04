#include "File\Configuration.h"

#include <sstream>
#include <map>

static const char PATH_SEPARATOR = '.';
static const unsigned char INDENT_WIDTH = 2;

static bool isDigits(const std::string& value){
	for(size_t i = 0; i < value.length(); ++i){
		if(!isdigit(value.at(i))){
			return false;
		}
	}

	return true;
}

static bool isInt(const std::string& value){
	if(value.length() == 0){
		return false;
	}

	size_t i = value.at(0) == '-' ? 1 : 0;

	for(; i < value.length(); ++i){
		if(!isdigit(value.at(i))){
			return false;
		}
	}

	return true;
}

static bool isFloat(const std::string& value){
	size_t index = value.find_first_of('.');

	if(index == std::string::npos || index == 0 || index == value.length()){
		return false;
	}

	if(!isInt(value.substr(0, index)) || !isDigits(value.substr(index + 1))){
		return false;
	}

	return true;
}

static int h(std::string& s){
	if(s.length() == 0){
		return 0;
	}

	std::string::size_type i = s.find_first_not_of(' ');

	if(i == std::string::npos){
		s = "";
		return 0;
	}

	s = s.substr(i);

	return i / INDENT_WIDTH;
}

enum Type{
	TYPEUNDEFINED,
	TYPEBOOL,
	TYPESTRING,
	TYPEFLOAT,
	TYPEINT,
	TYPEVECTORSTRING,
	TYPEVECTORFLOAT,
	TYPEVECTORINT
};

class ConfigurationNode{
public:
	static const char SEPARATOR = ',';

	Type type = TYPEUNDEFINED;
	void* value = nullptr;

	std::map<std::string, ConfigurationNode*> nodes;

	ConfigurationNode(){

	}

	~ConfigurationNode(){
		unset();
		for(const auto &ent : nodes){
			delete ent.second;
		}
	}

	void ConfigurationNode::unset(){
		switch(type){
		case TYPEBOOL:
			delete (bool*) value;
			break;

		case TYPESTRING:
			delete (std::string*) value;
			break;

		case TYPEFLOAT:
			delete (float*) value;
			break;

		case TYPEINT:
			delete (int*) value;
			break;

		case TYPEVECTORSTRING:
			delete (std::vector<std::string>*) value;
			break;

		case TYPEVECTORFLOAT:
			delete (std::vector<float>*) value;
			break;

		case TYPEVECTORINT:
			delete (std::vector<int>*) value;
			break;

		default:
			return;
		}

		type = TYPEUNDEFINED;
		value = nullptr;
	}

	void ConfigurationNode::set(const bool& value){
		unset();
		type = TYPEBOOL;
		ConfigurationNode::value = new bool(value);
	}

	void ConfigurationNode::set(const std::string& value){
		unset();
		type = TYPESTRING;
		ConfigurationNode::value = new std::string(value);
	}

	void ConfigurationNode::set(const float& value){
		unset();
		type = TYPEFLOAT;
		ConfigurationNode::value = new float(value);
	}

	void ConfigurationNode::set(const int& value){
		unset();
		type = TYPEINT;
		ConfigurationNode::value = new int(value);
	}

	void ConfigurationNode::set(const std::vector<std::string> &value){
		unset();
		type = TYPEVECTORSTRING;
		ConfigurationNode::value = new std::vector<std::string>(value);
	}

	void ConfigurationNode::set(const std::vector<float> &value){
		unset();
		type = TYPEVECTORFLOAT;
		ConfigurationNode::value = new std::vector<float>(value);
	}

	void ConfigurationNode::set(const std::vector<int> &value){
		unset();
		type = TYPEVECTORINT;
		ConfigurationNode::value = new std::vector<int>(value);
	}

	bool ConfigurationNode::boolValue(const bool& default_ = false) const{
		if(type != TYPEBOOL){
			return default_;
		}

		return *(bool*) value;
	}

	std::string ConfigurationNode::stringValue(const std::string& default_ = "") const{
		if(type != TYPESTRING){
			return default_;
		}

		return *(std::string*) value;
	}

	float ConfigurationNode::floatValue(const float& default_ = 0.0f) const{
		if(type != TYPEFLOAT){
			return default_;
		}

		return *(float*) value;
	}

	int ConfigurationNode::intValue(const int& default_ = 0) const{
		if(type != TYPEINT){
			return default_;
		}

		return *(int*) value;
	}

	std::vector<std::string> ConfigurationNode::stringVector(const std::vector<std::string>& default_ = {}) const{
		if(type != TYPEVECTORSTRING){
			return default_;
		}

		return *(std::vector<std::string>*) value;
	}

	std::vector<float> ConfigurationNode::floatVector(const std::vector<float>& default_ = {}) const{
		if(type != TYPEVECTORFLOAT){
			return default_;
		}

		return *(std::vector<float>*) value;
	}

	std::vector<int> ConfigurationNode::intVector(const std::vector<int>& default_ = {}) const{
		if(type != TYPEVECTORINT){
			return default_;
		}

		return *(std::vector<int>*) value;
	}

	bool hasValue() const{
		return type != TYPEUNDEFINED;
	}

	std::string toString() const{
		switch(type){

		case TYPEBOOL:
			return boolValue() ? "true" : "false";

		case TYPESTRING:
			return '"' + stringValue() + '"';

		case TYPEFLOAT:
			return std::to_string(floatValue());

		case TYPEINT:
			return std::to_string(intValue());

		case TYPEVECTORSTRING:
		{
			std::stringstream stream;
			std::vector<std::string> vector = stringVector();

			stream << '{';
			for(size_t i = 0; i < vector.size(); ++i){
				if(i > 0){
					stream << SEPARATOR;
				}
				stream << '"' << vector[i] << '"';
			}
			stream << '}';

			return stream.str();
		}

		case TYPEVECTORFLOAT:
		{
			std::stringstream stream;
			std::vector<float> vector = floatVector();

			stream << '{';
			for(size_t i = 0; i < vector.size(); ++i){
				if(i > 0){
					stream << SEPARATOR;
				}
				stream << std::to_string(vector[i]);
			}
			stream << '}';

			return stream.str();
		}

		case TYPEVECTORINT:
		{
			std::stringstream stream;
			std::vector<int> vector = intVector();

			stream << '{';
			for(size_t i = 0; i < vector.size(); ++i){
				if(i > 0){
					stream << SEPARATOR;
				}
				stream << std::to_string(vector[i]);
			}
			stream << '}';

			return stream.str();
		}
		}

		return "";
	}

	bool parse(const std::string& value){
		// TYPEBOOL
		if(value == "true" || value == "false"){
			set(value == "true");
		}

		// TYPESTRING
		else if(value.at(0) == '"' && value.at(value.length() - 1) == '"'){
			set(value.substr(1, value.length() - 2));
		}

		// TYPEINT
		else if(isInt(value)){
			set(stoi(value));
		}

		// TYPEFLOAT
		else if(isFloat(value)){
			set(stof(value));
		}

		// VECTOR
		else if(value.at(0) == '{' && value.at(value.length() - 1) == '}'){
			std::string val = value.substr(1, value.length() - 2);
			size_t index;

			// TYPEVECTORSTRING
			if(value.at(1) == '"' && value.at(value.length() - 2) == '"'){
				std::vector<std::string> vector;

				while((index = val.find_first_of(',')) != std::string::npos){
					vector.push_back(val.substr(1, index - 2));
					val = val.substr(index + 1);
					h(val);
				}

				vector.push_back(val.substr(1, val.length() - 2));
				set(vector);
			}
			else{
				std::string test = val;

				index = val.find_first_of(',');
				if(index != std::string::npos){
					test = val.substr(0, index);
				}

				// TYPEVECTORINT
				if(isInt(test)){
					std::vector<int> vector;

					while((index = val.find_first_of(',')) != std::string::npos){
						vector.push_back(stoi(val.substr(0, index)));
						val = val.substr(index + 1);
						h(val);
					}

					vector.push_back(stoi(val));
					set(vector);
				}

				// TYPEVECTORFLOAT
				else if(isFloat(test)){
					std::vector<float> vector;

					while((index = val.find_first_of(',')) != std::string::npos){
						vector.push_back(stof(val.substr(0, index)));
						val = val.substr(index + 1);
						h(val);
					}

					vector.push_back(stof(val));
					set(vector);
				}

				else{
					return false;
				}
			}
		}

		else{
			return false;
		}

		return true;
	}

	std::vector<std::string> children() const{
		std::vector<std::string> children;

		for(auto const &node : nodes){
			children.push_back(node.first);
		}

		return children;
	}

	bool containsNode(const std::string& path) const{
		size_t index;

		if((index = path.find_first_of(PATH_SEPARATOR)) != std::string::npos){
			std::string sub = path.substr(0, index);

			if(nodes.count(sub) > 0){
				return nodes.at(sub)->containsNode(path.substr(index + 1));
			}
			else{
				return false;
			}
		}

		return nodes.count(path) > 0;
	}

	ConfigurationNode& node(const std::string& path){
		size_t index;

		if((index = path.find_first_of(PATH_SEPARATOR)) != std::string::npos){
			std::string sub = path.substr(0, index);

			if(nodes.count(sub) == 0){
				nodes[sub] = new ConfigurationNode();
			}

			return nodes[sub]->node(path.substr(index + 1));
		}

		if(nodes.count(path) == 0){
			nodes[path] = new ConfigurationNode();
		}

		return *nodes[path];
	}

	void remove(const std::string& path){
		size_t index;

		if((index = path.find_first_of(PATH_SEPARATOR)) != std::string::npos){
			std::string sub = path.substr(0, index);

			if(nodes.count(sub) == 0){
				return;
			}

			return nodes[sub]->remove(path.substr(index + 1));
		}

		delete nodes[path];
		nodes[path] = nullptr;
		nodes.erase(path);
	}

	std::vector<std::string> contents(const std::string& ind){
		std::vector<std::string> lines;

		for(std::string n : children()){
			lines.push_back(ind + n + ":" + (node(n).hasValue() ? (" " + node(n).toString()) : ""));

			std::vector<std::string> next = node(n).contents(ind + "  ");

			lines.insert(lines.end(), next.begin(), next.end());
		}

		return lines;
	}
};

ConfigurationNode* root;

Configuration::Configuration(){
	root = new ConfigurationNode();
}

Configuration::~Configuration(){
	delete root;
}

bool Configuration::load(const File& file){
	delete root;
	root = new ConfigurationNode();

	if(!file.isFile()){
		return false;
	}

	std::vector<std::string> lines = file.readTextFile();
	int indent = -1;
	std::string curPath = "";
	bool success = true;
	for(size_t i = 0; i < lines.size(); ++i){
		std::string line = lines[i];
		int curIndent = h(line);

		if(line.length() == 0 || line.at(0) == '#'){
			continue;
		}

		size_t colIndex = line.find_first_of(":");
		std::string node = line.substr(0, colIndex);
		std::string val;

		if(indent < curIndent){
			curPath += (curPath.length() > 0 ? "." : "") + node;
		}
		else{
			for(int s = 0; s <= indent - curIndent; ++s){
				size_t index = curPath.find_last_of('.');

				if(index != std::string::npos){
					curPath = curPath.substr(0, index);
				}
				else{
					curPath = "";
					break;
				}
			}
			curPath += (curPath.length() > 0 ? "." : "") + node;
		}
		if(line.length() > colIndex + 1){
			val = line.substr(colIndex + 1);
			h(val);
			if(val.length() == 0 || val.at(0) == '#'){
				continue;
			}
			if(!root->node(curPath).parse(val)){
				printf((
					"Failed to parse file (" + file.path() + "): line " + std::to_string(i + 1) + " - " + line + "\n"
					).data());
				success = false;
				break;
			}
		}
		indent = curIndent;
	}

	return success;
}

bool Configuration::save(const File& file) const{
	return file.writeTextFile(root->contents(""));
}

std::vector<std::string> Configuration::children(const std::string& path, const bool& fullPath) const{
	std::vector<std::string> children;

	if(root->containsNode(path)){
		children = root->node(path).children();
	}
	else if(path.length() == 0){
		children = root->children();
	}
	if(path.length() > 0 && fullPath){
		for(size_t i = 0; i < children.size(); i++){
			children[i] = path + PATH_SEPARATOR + children[i];
		}
	}

	return children;
}

bool Configuration::hasValue(const std::string& path) const{
	return root->containsNode(path) && root->node(path).hasValue();
}

Configuration& Configuration::remove(const std::string& path){
	if(root->containsNode(path)){
		root->remove(path);
	}

	return *this;
}

Configuration& Configuration::unset(const std::string& path){
	if(root->containsNode(path)){
		root->node(path).unset();
	}

	return *this;
}

Configuration& Configuration::set(const std::string& path, const bool& value){
	root->node(path).set(value);
	return *this;
}
Configuration& Configuration::set(const std::string& path, const std::string& value){
	root->node(path).set(value);
	return *this;
}
Configuration& Configuration::set(const std::string& path, const float& value){
	root->node(path).set(value);
	return *this;
}
Configuration& Configuration::set(const std::string& path, const int& value){
	root->node(path).set(value);
	return *this;
}
Configuration& Configuration::set(const std::string& path, const std::vector<std::string> &value){
	root->node(path).set(value);
	return *this;
}
Configuration& Configuration::set(const std::string& path, const std::vector<float> &value){
	root->node(path).set(value);
	return *this;
}
Configuration& Configuration::set(const std::string& path, const std::vector<int> &value){
	root->node(path).set(value);
	return *this;
}

bool Configuration::boolValue(const std::string& path, const bool& default_) const{
	if(root->containsNode(path)){
		return root->node(path).boolValue(default_);
	}

	return default_;
}
std::string Configuration::stringValue(const std::string& path, const std::string& default_) const{
	if(root->containsNode(path)){
		return root->node(path).stringValue(default_);
	}

	return default_;
}
float Configuration::floatValue(const std::string& path, const float& default_) const{
	if(root->containsNode(path)){
		return root->node(path).floatValue(default_);
	}

	return default_;
}
int Configuration::intValue(const std::string& path, const int& default_) const{
	if(root->containsNode(path)){
		return root->node(path).intValue(default_);
	}

	return default_;
}
std::vector<std::string> Configuration::stringVector(const std::string& path, const std::vector<std::string>& default_) const{
	if(root->containsNode(path)){
		return root->node(path).stringVector(default_);
	}

	return default_;
}
std::vector<float> Configuration::floatVector(const std::string& path, const std::vector<float>&  default_) const{
	if(root->containsNode(path)){
		return root->node(path).floatVector(default_);
	}

	return default_;
}
std::vector<int> Configuration::intVector(const std::string& path, const std::vector<int>&  default_) const{
	if(root->containsNode(path)){
		return root->node(path).intVector(default_);
	}

	return default_;
}
