#pragma once
#include <vector>

template<typename T>
bool is_sorted(const std::vector<T>& v)
{
	if (v.size() == 0) {
		return true;
	}
	for (size_t i = 0; i < v.size() - 1; i++) {
		if (v[i+1] < v[i]) {
			return false;
		}
	}
	return true;
}
		
		

