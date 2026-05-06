#pragma once
#include <vector>
#include <algorithm>

template<typename T>
void bubble_sort(std::vector<T>& v)
{
	if (v.size() < 2) return;
	
	for (size_t i = 0; i < v.size() -1; i++) {
		for (size_t j = 0; j < v.size() -1 -i; j++) {
			if (v[j] > v[j+1]) {
				std::swap(v[j], v[j+1]);
			}
		}
	}
}


template<typename T> 
void insertion_sort(std::vector<T>& v) //void perchè non restituisce un valore ma modifica solo un array
{
	for (size_t j = 1; j < v.size(); j++) {
		
		T key = v[j];
		int i = j - 1; // size_t non va bene perchè è sempre >= 0
		
		while (i >=0 && v[i] > key) {
			
			v[i+1] = v[i];
			i = i-1;
		}
		
		v[i+1] = key;
	}
}

template<typename T> 
void selection_sort(std::vector<T>& v)
{
	if (v.size() < 2) return;
	
	for( size_t i = 0; i < (v.size() -1); i++) {
		size_t min_pos = i;
		
		for (size_t j = i + 1; j < v.size(); j++) {
			if (v[j] < v[min_pos]) {
				min_pos = j;
			}
		}
		
		std::swap(v[i],v[min_pos]);
	}
}
				