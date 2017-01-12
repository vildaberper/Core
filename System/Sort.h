#pragma once

#include <vector>

template <typename T>
void sort_merge(vector<T>& v){
	size_t s = v.size();

	if(s < 2) return;

	size_t p = s / 2;

	vector<T> l(v.begin(), v.begin() + p);
	sort_merge(l);
	size_t li = 0;

	vector<T> r(v.begin() + p, v.end());
	sort_merge(r);
	size_t ri = 0;

	for(size_t i = 0; i < v.size(); ++i){
		if(li < l.size() && (ri == r.size() || l[li] <= r[ri])) v[i] = l[li++];
		else v[i] = r[ri++];
	}
}

template <typename T>
void sort_insertion(std::vector<T>& vec){
	for(size_t i = 1; i < vec.size(); ++i){
		for(size_t j = i; j > 0 && vec[j] < vec[j - 1]; --j){
			std::swap(vec[j], vec[j - 1]);
		}
	}
}

template <typename T>
void sort_bubble(std::vector<T>& vec){
	size_t end = vec.size();

	bool swapped;

	do{
		swapped = false;
		for(size_t i = 1; i < end; ++i){
			if(vec[i] < vec[i - 1]){
				std::swap(vec[i], vec[i - 1]);
				swapped = true;
			}
		}
		--end;
	} while(swapped);
}
