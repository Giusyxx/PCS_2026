#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

#include "timecounter.h"
#include "randfiller.h"
#include "sorts.hpp"
#include "sorts.h"
#include "quicksort_ibrido.hpp"

int main(void)
{
	randfiller rf;
	timecounter tc;
	
	int soglia = -1;
	
	for (int n = 4; n <= 100; n++) { // Proviamo dimensioni piccole per trovare la soglia
		int num_vettori = 100;
		
		std::vector<std::vector<int>> box_vecs(num_vettori, std::vector<int>(n));
		for (int i = 0; i < num_vettori; i++) {
			rf.fill(box_vecs[i], -1000, 1000);
		}
		
		std::vector<std::vector<int>> vb = box_vecs; //bubble
		std::vector<std::vector<int>> vi = box_vecs; //insertion
		std::vector<std::vector<int>> vs = box_vecs; //selection
		std::vector<std::vector<int>> vm = box_vecs; //merge
		std::vector<std::vector<int>> vq = box_vecs; //quick
		std::vector<std::vector<int>> vq_ibrido = box_vecs; //quicksort ibrido
		std::vector<std::vector<int>> v = box_vecs; //sort
		
		// BUBBLE
		tc.tic();
		for(int i = 0; i < num_vettori; i++) {
			bubble_sort(vb[i]);
		}
		double secs_bubble = tc.toc();
		double media_secs_bubble = secs_bubble / num_vettori;
		
		// INSERTION
		tc.tic();
		for(int i = 0; i < num_vettori; i++) {
			insertion_sort(vi[i]);
		}
		double secs_insertion = tc.toc();
		double media_secs_insertion = secs_insertion / num_vettori;
		
		// SELECTION
		tc.tic();
		for(int i = 0; i < num_vettori; i++) {
			selection_sort(vs[i]);
		}
		double secs_selection = tc.toc();
		double media_secs_selection = secs_selection / num_vettori;
		
		// MERGE
		tc.tic();
		for(int i = 0; i < num_vettori; i++) {
			merge_sort(vm[i], 0, n-1);
		}
		double secs_merge = tc.toc();
		double media_secs_merge = secs_merge / num_vettori; 
		
		// QUICK
		tc.tic();
		for(int i = 0; i < num_vettori; i++) {
			quick_sort(vq[i], 0 , n-1);
		}
		double secs_quick = tc.toc();
		double media_secs_quick = secs_quick / num_vettori;
		
		//QUICK IBRIDO
		tc.tic();
		for(int i = 0; i < num_vettori; i++) {
			quick_sort_ibrido(vq_ibrido[i], 0 , n-1);
		}
		double secs_quick_ibrido = tc.toc();
		double media_secs_quick_ibrido = secs_quick_ibrido / num_vettori;
		
		// STD::SORT
		tc.tic();
		for(int i = 0; i < num_vettori; i++) {
			std::sort( v[i].begin(), v[i].end());
		}
		double secs_sort = tc.toc();
		double media_secs_sort = secs_sort / num_vettori;
		
		std::cout << "n = " << n << "\n" 	<< "Bubble: " << media_secs_bubble << "\n"
											<< "Insertion: " << media_secs_insertion << "\n"
											<< "Selection: " << media_secs_selection << "\n"
											<< "Merge: " << media_secs_merge<< "\n"
											<< "Quick: " << media_secs_quick << "\n"
											<< "Quick Ibrido: " << media_secs_quick_ibrido << "\n"
											<< "std::sort:" << media_secs_sort << "\n";
										
		// troviamo la soglia. la soglia è il più piccolo n tale che insertion sort (consideriamo solo insertion perchè bubble e selection quasi mai vincono) smette di essere più veloce di quicksort (e/o mergesort)
		if ( soglia == -1 && media_secs_quick < media_secs_insertion) {
			soglia = n;
		}
	}
	
	if (soglia != -1) {
		std::cout << "la soglia stimata è n = " << soglia << " ,cioè al di sotto di questa dimensione gli algoritmi quadratici (Bubblesort, Selectionsort ed Insertionsort) sono piu veloci di quelli logaritmici (Quicksort e Mergesort) " << "\n" ;
	}

	return 0;
}
		