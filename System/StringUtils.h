#pragma once

#include <algorithm>
#include <minmax.h>
#include <vector>
#include <string>

static std::string toLowercase(std::string s){
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
	return s;
}

static std::string toUppercase(std::string s){
	std::transform(s.begin(), s.end(), s.begin(), ::toupper);
	return s;
}

static bool contains(const std::string& s0, const std::string& s1, const size_t& index = 0){
	if(s0.length() < s1.length() || s0.length() - index < s1.length()) return false;

	bool equals = true;

	for(size_t i = 0; equals && i < s1.length(); ++i)
		if(s0[index + i] != s1[i]) equals = false;

	return equals || contains(s0, s1, index + 1);
}

static std::vector<std::string> splitAsCommand(const std::string& s){
	std::vector<std::string> v;
	v.push_back("");

	bool in = false;
	for(const char& c : s){
		if(c == '"'){
			in = !in;
			continue;
		}
		if(c == ' '){
			if(in){
				v[v.size() - 1] += c;
			}
			else{
				if(v[v.size() - 1].size() > 0) v.push_back("");
			}
		}
		else{
			v[v.size() - 1] += c;
		}
	}
	if(v[v.size() - 1].size() == 0) v.pop_back();
	return v;
}

static std::vector<std::string> split(const std::string& s, const char& c){
	std::vector<std::string> v;
	v.push_back("");

	for(const char& c_ : s){
		if(c_ == c){
			if(v[v.size() - 1].size() > 0) v.push_back("");
		}
		else{
			v[v.size() - 1] += c_;
		}
	}
	if(v[v.size() - 1].size() == 0) v.pop_back();
	return v;
}

static std::vector<std::string> splitIncludeEmpty(const std::string& s, const char& c){
	std::vector<std::string> v;
	v.push_back("");

	for(const char& c_ : s){
		if(c_ == c){
			v.push_back("");
		}
		else{
			v[v.size() - 1] += c_;
		}
	}
	if(v[v.size() - 1].size() == 0) v.pop_back();
	return v;
}

static bool startsWith(const std::string& s0, const std::string& s1){
	if(s1.length() > s0.length()) return false;
	for(size_t i = 0; i < s1.length(); ++i) if(s0[i] != s1[i]) return false;
	return true;
}

static bool endsWith(const std::string& s0, const std::string& s1){
	if(s1.length() > s0.length()) return false;
	for(size_t i = 1; i <= s1.length(); ++i) if(s0[s0.length() - i] != s1[s1.length() - i]) return false;
	return true;
}

static int compare(const std::string& s0, const std::string& s1){
	size_t n = min(s0.length(), s1.length());

	for(size_t i = 0; i < n; ++i){
		if(s0[i] != s1[i]) return int(s0[i]) - int(s1[i]);
	}

	return int(s0.length()) - int(s1.length());
}
static bool compareLess(const std::string& s0, const std::string& s1){
	return compare(s0, s1) < 0;
}
static bool compareLessOrEqual(const std::string& s0, const std::string& s1){
	return compare(s0, s1) <= 0;
}
static bool compareGreater(const std::string& s0, const std::string& s1){
	return !compareLessOrEqual(s0, s1);
}
static bool compareGreaterOrEqual(const std::string& s0, const std::string& s1){
	return !compareLess(s0, s1);
}
