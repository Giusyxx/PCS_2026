#pragma once
#include <set>
#include "undirected_graph.hpp"

template <typename T,typename Container>
undirected_graph<T> graph_visit(const undirected_graph<T>& grafo, const T& nodo_sorgente, Container& container) { // restituisce un grafo, const serve per non modificarlo
	undirected_graph<T> albero_visita; // crea un nuovo grafo che conterrà l'albero risultante della visita
	std::set<T> visitati; // set dei visitati
	
	// Inizializzazione della visita
	container.put(nodo_sorgente); // inserisce il nodo sorgente nel contenitore 
	visitati.insert(nodo_sorgente); // inserisce il nodo sorgente nel sei dei visitati
	
	while(!container.empty()) { // finchè il container non è vuoto
		T nodo_corrente = container.get(); // estrae un nodo (il primo se è Fifo, l'ultimo se è Lifo)
		for (const auto& vicino : grafo.neighbours(nodo_corrente)) { // scorro i vicini del nodo corrente con il metodo neighbours
			if (visitati.find(vicino) == visitati.end()) { // se il vicino non è stato ancora visitato
				visitati.insert(vicino); // lo inserisce nei visitati
				container.put(vicino); // lo inserisce nel contenitore
				albero_visita.add_edge(nodo_corrente,vicino);  // aggiunge l'arco tra il nodo corrente e il vicino all'albero risultante
			}
		}
	}
	
	return albero_visita; 
}
