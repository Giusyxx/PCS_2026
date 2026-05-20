#pragma once
#include "undirected_graph.hpp"
#include <set>

template <typename T> // T tipo nodo per sorgente 
void recursive_dfs(const undirected_graph<T>& grafo, const T& nodo_sorgente, std::set<T>& visitati,  undirected_graph<T>& dfs_tree) {
	
	//albero dfs ricorsivo
	//credo un set per i visitati
	visitati.insert(nodo_sorgente); //inserisco al set dei visitati il nodo sorgente
	
	for (const auto& vicino : grafo.neighbours(nodo_sorgente)){ // scorro i vicini del nodo sorgente 
		if(visitati.find(vicino) == visitati.end()) { //se il vicino non è stato visitato 
			dfs_tree.add_edge(nodo_sorgente, vicino); // aggiungo l'arco all'albero
			
			//applico chiamata ricorsiva a vicino  
			recursive_dfs(grafo, vicino, visitati, dfs_tree);
		}
	}  

}