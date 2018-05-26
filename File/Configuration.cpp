#include "File\Configuration.h"

#include <fstream>
#include <iostream>

#include "File\ConfigurationSection.cpp"

Configuration::Configuration() { root_ = new ConfigurationNode(); }

Configuration::Configuration(const File& file) {
	root_ = new ConfigurationNode();
	load(file);
}

Configuration::~Configuration() { delete root_; }

void Configuration::clear() { delete root_; root_ = new ConfigurationNode(); }

void err_parse(const std::string& message, const size_t& num, const std::string& line, const std::string& level = "error") {
	outc << "Parse " << level << ": line " << num << " [" << message << "] (" << line << ')' << std::endl;
}

bool Configuration::in(std::istream& stream, const bool& clear) {
	if (clear) Configuration::clear();
	bool success = true;
	size_t num = 0;
	std::string line;
	std::vector<ConfigurationNode*> cnode = { root_ };
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

	if (!in(ifs, clear)) {
		outc << "In file: " << file.path() << std::endl;
		return false;
	}

	return true;
}

void out_(std::ostream& ofs, ConfigurationNode& node, const std::string& name, const size_t& depth = 0) {
	for (size_t i = 0; i < depth; ++i) ofs << FILE_INDENT;
	ofs << name << VALUE_INDICATOR;
	if (node.hasValue()) ofs << ' ' << node.str();
	ofs << ENDL;
	for (auto& child : node.children()) out_(ofs, child.second, child.first, depth + 1);
}

void Configuration::out(std::ostream& stream) const {
	for (auto& child : root_->children()) out_(stream, child.second, child.first);
}

bool Configuration::save(const File& file) const {
	std::ofstream ofs;
	ofs.open(file.path().data(), std::ios_base::out | std::ios_base::trunc);
	if (!ofs.is_open()) return false;

	out(ofs);

	return true;
}