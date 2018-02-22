#pragma once

#include <algorithm>
#include <minmax.h>
#include <sstream>
#include <vector>
#include <string>

static std::string toLowercase(std::string string) {
	std::transform(string.begin(), string.end(), string.begin(), ::tolower);
	return string;
}

static std::string toUppercase(std::string string) {
	std::transform(string.begin(), string.end(), string.begin(), ::toupper);
	return string;
}

static bool contains(const std::string& string, const std::string& val, const size_t& index = 0) {
	return string.find(val, index) != std::string::npos;
}

static std::string replaceAll(const std::string& string, const std::string& toReplace, const std::string& replacement = "") {
	std::string result = string;
	size_t index = 0;

	while ((index = result.find(toReplace, index)) != std::string::npos) {
		result.replace(index, toReplace.size(), replacement);
		index += replacement.size();
	}

	return result;
}

static std::vector<std::string> splitAsCommand(const std::string& string, const char& splitChar = ' ') {
	std::vector<std::string> v = { " " };

	bool in = false;
	for (const char& c : string) {
		if (c == '"') {
			in = !in;
			continue;
		}
		if (c == splitChar) {
			if (in) {
				v[v.size() - 1] += c;
			}
			else {
				if (v[v.size() - 1].size() > 0) v.push_back("");
			}
		}
		else {
			v[v.size() - 1] += c;
		}
	}
	if (v[v.size() - 1].size() == 0) v.pop_back();
	return v;
}
static std::vector<std::string> split(const std::string& string, const char& splitChar = ' ') {
	std::vector<std::string> v;
	v.push_back("");

	for (const char& c_ : string) {
		if (c_ == splitChar) {
			if (v[v.size() - 1].size() > 0) v.push_back("");
		}
		else {
			v[v.size() - 1] += c_;
		}
	}
	if (v[v.size() - 1].size() == 0) v.pop_back();
	return v;
}
static std::vector<std::string> splitIncludeEmpty(const std::string& string, const char& splitChar = ' ') {
	std::vector<std::string> v;
	v.push_back("");

	for (const char& c_ : string) {
		if (c_ == splitChar) {
			v.push_back("");
		}
		else {
			v[v.size() - 1] += c_;
		}
	}
	if (v[v.size() - 1].size() == 0) v.pop_back();
	return v;
}

static bool startsWith(const std::string& string, const std::string& val) {
	if (val.length() > string.length()) return false;
	for (size_t i = 0; i < val.length(); ++i) if (string[i] != val[i]) return false;
	return true;
}
static bool endsWith(const std::string& string, const std::string& val) {
	if (val.length() > string.length()) return false;
	for (size_t i = 1; i <= val.length(); ++i) if (string[string.length() - i] != val[val.length() - i]) return false;
	return true;
}

static std::string repeat(const std::string& string, const size_t& num) {
	std::stringstream ss;
	for (size_t i = 0; i < num; ++i) ss << string;
	return ss.str();
}

static size_t stripStartCount(std::string& string, const std::string& toStrip) {
	size_t num = 0;
	while (startsWith(string, toStrip)) {
		string = string.substr(toStrip.length());
		++num;
	}
	return num;
}
static std::string stripStart(std::string string, const std::string& toStrip) {
	stripStartCount(string, toStrip);
	return string;
}

static std::string trim(std::string string, const char& toRemove = ' ') {
	size_t i;
	for (i = 0; i < string.length() && string[i] == toRemove; ++i); string = string.substr(i);
	for (i = string.length() - 1; i >= 0 && string[i] == toRemove; --i); string = string.substr(0, i + 1);
	return string;
}

static int compare(const std::string& s0, const std::string& s1) {
	size_t n = min(s0.length(), s1.length());
	for (size_t i = 0; i < n; ++i) if (s0[i] != s1[i]) return int(s0[i]) - int(s1[i]);
	return int(s0.length()) - int(s1.length());
}
static bool compareLess(const std::string& s0, const std::string& s1) { return compare(s0, s1) < 0; }
static bool compareLessOrEqual(const std::string& s0, const std::string& s1) { return compare(s0, s1) <= 0; }
static bool compareGreater(const std::string& s0, const std::string& s1) { return !compareLessOrEqual(s0, s1); }
static bool compareGreaterOrEqual(const std::string& s0, const std::string& s1) { return !compareLess(s0, s1); }

static bool isdigits(const std::string& value, const size_t& begindex = 0, size_t endex = UINT_MAX) {
	if (endex > value.length()) endex = value.length();
	for (size_t i = begindex; i < endex; ++i) if (!isdigit(value[i])) return false;
	return true;
}
static bool isint(const std::string& value) {
	return !value.empty() && isdigits(value, value[0] == '-' ? 1 : 0);
}
static bool isfloat(const std::string& value) {
	size_t split = value.find_first_of('.');
	return split != std::string::npos && isdigits(value, value[0] == '-' ? 1 : 0, split) && isdigits(value, split + 1);
}
static bool isbool(const std::string& value) {
	return value == "true" || value == "false";
}
static bool isstring(const std::string& value) {
	return value.length() > 1 && value[0] == '"' && value[value.length() - 1] == '"';
}
static bool isvector(const std::string& value) {
	return value.length() > 1 && value[0] == '{' && value[value.length() - 1] == '}';
}
static bool stob(const std::string& string) {
	return string[0] == 't';
}
static std::string stos(const std::string& string) {
	return string.substr(1, string.length() - 2);
}

template <typename T> static std::string toString(const T& val) {
	std::stringstream ss;
	ss << val;
	return ss.str();
}
static std::string toString(const float& val) {
	return std::to_string(val);
}
static std::string toString(const bool& val) {
	return val ? "true" : "false";
}
static std::string toString(const std::string& val) {
	return '"' + val + '"';
}
template <typename T> static std::string toString(const std::vector<T>& vec, const std::string& separator = ", ", const std::string& prefix = "{", const std::string& suffix = "}") {
	std::stringstream ss;
	if (vec.empty()) ss << '(' << typeOfString<T>() << ')';
	ss << prefix;
	for (size_t i = 0; i < vec.size(); ++i) {
		if (i > 0) ss << separator;
		ss << toString(vec[i]);
	}
	ss << suffix;
	return ss.str();
}

template <typename T> static std::string typeOfString() { return "unknown"; }
template <> static std::string typeOfString<int>() { return "int"; }
template <> static std::string typeOfString<float>() { return "float"; }
template <> static std::string typeOfString<bool>() { return "bool"; }
template <> static std::string typeOfString<std::string>() { return "string"; }
