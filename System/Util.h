#pragma once

template <typename T> inline static T* cast(void* ptr) { return reinterpret_cast<T*>(ptr); }

template <typename K, typename V> static std::vector<K> keys(const std::map<K, V>& map) {
	std::vector<K> keys;
	keys.reserve(map.size());
	for (const auto& elem : map) keys.push_back(elem.first);
	return keys;
}

template <typename K, typename V> static std::vector<K> values(const std::map<K, V>& map) {
	std::vector<K> values;
	values.reserve(map.size());
	for (const auto& elem : map) values.push_back(elem.first);
	return values;
}
