#pragma once

#include <vector>

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
