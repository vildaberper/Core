#pragma once

#include <vector>

template <typename T>
static void sort_quick(vector<T>& v, const size_t& low = 0, size_t high = 0){

	static auto partition = [](vector<T>& v, const size_t& low, const size_t& high){
		size_t p = high - 1;

		if(p - low == 1){
			if(v[low] > v[p]) swap(v[low], v[p]);
			return p;
		}

		for(size_t i = low; i < p;){
			if(v[i] > v[p]){
				swap(v[p], v[--p]);
				if(i < p) swap(v[p + 1], v[i]);
			}
			else ++i;
		}
		return p;
	};

	if(!high) high = v.size();

	if(high - low < 2) return;

	size_t p = partition(v, low, high);

	quicksort(v, low, p);
	quicksort(v, p, high);
}

template <typename T>
static void sort_merge(vector<T>& v){
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
static void sort_insertion(std::vector<T>& vec){
	for(size_t i = 1; i < vec.size(); ++i){
		for(size_t j = i; j > 0 && vec[j] < vec[j - 1]; --j){
			std::swap(vec[j], vec[j - 1]);
		}
	}
}

template <typename T>
static void sort_bubble(std::vector<T>& vec){
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
