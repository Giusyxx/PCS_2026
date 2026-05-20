#pragma once
#include <map>
#include <set>
#include <limits>
#include "undirected_graph.hpp"
#include "undirected_edge.hpp"

//HO UTILIZZATO L'AI PER CAPIRE MEGLIO IL CODICE ED IMPLEMENTARE IL CICLO PRINCIPALE

template <typename T>
void dijkstra (const undirected_graph<T>& grafo, const T& nodo_sorgente, const std::map<undirected_edge<T>, double>& pesi, std::map<T, T>& pred, std::map<T, double>& dist) {
	
	std::set<T> nodi = grafo.all_nodes(); // set dei nodi del grafo
	
	for(const auto& nodo : nodi) { //inizializza le distanze. non serve inizializzare il predecessore 
		dist[nodo] = std::numeric_limits<double>::infinity();  
	}
	 
	dist[nodo_sorgente] = 0.0;
	pred[nodo_sorgente] = nodo_sorgente; // il predecssore del nodo sorgente è se stesso 
	
	std::set<std::pair<double, T>> PQ; //  creo la coda di priorità PQ
	
	// inizializzazione: inserisco tutti i nodi in PQ
	
	for (const auto& nodo : nodi) {
		PQ.insert({dist[nodo], nodo}); // le graffe {} creano una coppia std::pair temporanea 
	}
	
	// ciclo principale dell'algoritmo 
	
	while (!PQ.empty()) { // finchè la coda di priorità non è vuota
		auto minimo = *PQ.begin(); // estraggo il minimo, cioè il nodo con distanza minima, che corrisponde al primo elemento del set della coda di priorita
		PQ.erase(PQ.begin()); // rimuovo il minimo dal set (già visitato) 
		
		T nodo_corrente = minimo.second; // nodo corrente è il secondo elemento della coppia (distanza, nodo)
		double distanza_corrente = minimo.first; // distanza corrente è il primo elemento della coppia (distanza, nodo)
		
		for(const auto& vicino : grafo.neighbours(nodo_corrente)) { // scorro i vicini del nodo corrente
			undirected_edge<T> arco(nodo_corrente, vicino); // creo un arco tra il nodo corrente e il vicino
			double peso_arco = pesi.at(arco); // ottiene il peso dell'arco tra il nodo corrente e il vicino
			
			double nuova_distanza = distanza_corrente + peso_arco; // calcolo la nuova distanza dal nodo sorgente al vicino passando per il nodo corrente
			
			if (nuova_distanza < dist[vicino]) { // se la nuova distanza è minore di quella vecchia (cioè la distanza del vicino
				PQ.erase({dist[vicino], vicino}); //rimuovo la vecchia distanza dalla PQ
				
				dist[vicino] = nuova_distanza; // aggiorno la distanza più corta del vicino
				pred[vicino] = nodo_corrente; // aggiorno il predecessore del vicino
				
				PQ.insert({dist[vicino], vicino}); //inserisco il vicino nella coda di priorità con la nuova distanza
			}
		}
	}
}
	