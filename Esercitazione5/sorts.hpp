#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath> // per il floor()


template<typename T>
void merge(std::vector<T>& vec, int s, int centro, int d)
{
	int n1 = centro - s + 1; // dimensione primo sotto-array di sinistra dopo aver splittato a metà
	int n2 = d - centro; // dimensione secondo sotto-array di destra
	
	std::vector<T> L(n1), R(n2);
	
	for (int i = 0; i < n1; i++) {
		L[i] = vec[s + i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = vec[centro + j + 1];
	}
	
	int i = 0, j = 0, k = s;
	
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			vec[k] = L[i];
			i++ ;
		}
		else {
			vec[k] = R[j];
			j++ ;
		}
		k++;
	}
	// copia i rimanenti elementi
	while (i < n1) {
		vec[k] = L[i];
		i++;
		k++;
	}
	
	while (j < n2) {
		vec[k] = R[j];
		j++;
		k++;
	}
}	 

template<typename T>
void merge_sort(std::vector<T>& vec,int s,int d) 
{
	if (s < d) {
		int centro = floor((s+d)/2);
		merge_sort(vec,s,centro);
		merge_sort(vec,centro + 1,d);
		merge(vec,s,centro,d);
	}
}

template<typename T>
int partition(std::vector<T>& vec, int s, int d) {
	T pivot = vec[d]; // scelgo l'ultimo elemento come pivot
	int i = s - 1;
	
	for (int j = s; j < d; j++) {
		if (vec[j] <= pivot) {
			i++;
			std::swap(vec[i], vec[j]);
		}
	}
	std::swap(vec[i+1], vec[d]);
	return i+1;
}

template<typename T>
void quick_sort(std::vector<T>& vec, int s, int d) {
	if (s < d) {
		int q = partition(vec, s, d);
		
		quick_sort(vec,s, q-1);
		quick_sort(vec, q+1, d);
	}
}

		
			