#include <iostream>
#include <map>
#include <vector>
#include <set>
#include "fifo.hpp"
#include "lifo.hpp"
#include "visite.hpp"
#include "recursive_dfs.hpp"
#include "undirected_graph.hpp"
#include "undirected_edge.hpp"
#include "dijkstra.hpp"

// HO UTILIZZATO L'INTELLIGENZA ARTIFICIALE PER VISUALIZZARE LE IMMAGINI DEI DUE GRAFI VISITA (BFS E DFS) SU "EDOTOR.NET"

int main() {
	
	// creo un grafo non orientato 
	undirected_graph<int> grafo;
	
	// inserisco gli archi con il metodo add.edge()
	grafo.add_edge(1,2);
	grafo.add_edge(1,3);
	grafo.add_edge(1,4);
	grafo.add_edge(1,6);
	grafo.add_edge(2,4);
	grafo.add_edge(2,5);
	grafo.add_edge(2,7);
	grafo.add_edge(3,6);
	grafo.add_edge(4,6);
	grafo.add_edge(4,7);
	grafo.add_edge(5,7);
	grafo.add_edge(6,7);
	grafo.add_edge(6,8);
	grafo.add_edge(7,9);
	grafo.add_edge(8,9);
	
	
	
	// eseguo visita in ampiezza BFS "Fifo"
	fifo<int> q; // crea la coda
	undirected_graph<int> bfsG = graph_visit(grafo, 1, q);
	
	std::cout << "Archi dell'albero BFS risultante:" << std::endl;
	for (const auto& arco : bfsG.all_edges()) {
		std::cout << "  " << arco << std::endl; 
	}
	
	
	// eseguo visita in profondita DFS "Lifo"
	lifo<int> s; // crea lo stack
	undirected_graph<int> dfsG = graph_visit(grafo, 1, s); 
	
	std::cout << "Archi dell'albero DFS risultante:" << std::endl;
	for (const auto& arco : dfsG.all_edges()) {
		std::cout << "  " << arco << std::endl;
	}
	
	//eseguo la visita in profondità con DFS ricorsivo 
	std::set<int> visitati; 
	undirected_graph<int> dfs_tree;
	recursive_dfs(grafo, 1, visitati, dfs_tree);
	
	std::cout << "Archi dell'albero DFS ricorsivo:" << std::endl;
	for (const auto& arco : dfs_tree.all_edges()) {
		std::cout << "  " << arco << std::endl;
	}
	
	// mappa dei pesi
	std::map<undirected_edge<int>, double> pesi;
	
	pesi[undirected_edge<int>(1, 2)] = 2.0;
	pesi[undirected_edge<int>(1, 3)] = 5.0;
	pesi[undirected_edge<int>(1, 4)] = 9.0;
	pesi[undirected_edge<int>(1, 6)] = 12.0;
	
	pesi[undirected_edge<int>(2, 4)] = 4.0;
	pesi[undirected_edge<int>(2, 5)] = 3.0;
	pesi[undirected_edge<int>(2, 7)] = 8.0;
	
	pesi[undirected_edge<int>(3, 6)] = 4.0;
	
	pesi[undirected_edge<int>(4, 6)] = 3.0;
	pesi[undirected_edge<int>(4, 7)] = 1.0; 
	
	pesi[undirected_edge<int>(5, 7)] = 6.0;
	
	pesi[undirected_edge<int>(6, 7)] = 2.0;
	pesi[undirected_edge<int>(6, 8)] = 5.0;
	
	pesi[undirected_edge<int>(7, 9)] = 3.0;
	
	pesi[undirected_edge<int>(8, 9)] = 1.0;
	
	// mappa predecessori e distanze
	std::map<int, int> predecessori;
	std::map<int, double> distanze;
	
	// eseguo dijkstra
	dijkstra(grafo, 1, pesi, predecessori, distanze);
	
	std::cout << "RICOSTRUZIONE DEL CAMMINO OTTIMO DA 1 A 9" << std::endl;
	
	int destinazione = 9;
	int corrente = destinazione;
	std::vector<int> cammino;
	
	// Risaliamo la catena dei predecessori all'indietro fino a tornare alla sorgente (1)
	while (corrente != 1) {
		cammino.push_back(corrente);
		corrente = predecessori[corrente];
	}
	cammino.push_back(1); // Aggiungiamo la sorgente alla fine del vettore
	
	// Stampiamo il vettore al contrario per leggerlo nel verso giusto (da 1 a 9)
	std::cout << "Percorso ideale calcolato: ";
	for (int i = cammino.size() - 1; i >= 0; --i) {
		std::cout << cammino[i];
		if (i > 0) std::cout << " -> ";
	}
	
	std::cout << "\nCosto totale del percorso: " << distanze[destinazione] << std::endl;
	
	return 0;
}