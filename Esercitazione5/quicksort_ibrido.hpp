#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include "sorts.hpp"

template<typename T>
void insertion_sort_ibrido (std::vector<T>& v, int s, int d) {
	for (int j = s + 1; j <= d; j++) {
		T key = v[j];
		int i = j - 1;
		
		while (i >= s && v[i] > key) {
			v[i+1] = v[i];
			i = i - 1;
		}
		
		v[i+1] = key;
	}
}


template<typename T>
void quick_sort_ibrido(std::vector<T>& vec, int s, int d) {
	
	if (s >= d) return;
	
	int n = d - s + 1; // calcoliamo quanti elementi ci sono tra 's' e 'd'
	
	if (n <= 20) { // usiamo l'algoritmo quadratico
		insertion_sort_ibrido(vec, s, d);
		return;
	}
	
	int q = partition(vec, s, d);
	quick_sort_ibrido(vec,s, q-1);
	quick_sort_ibrido(vec, q+1, d);
	
}

		
			