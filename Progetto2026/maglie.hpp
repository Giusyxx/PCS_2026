#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <limits>
#include "undirected_edge.hpp"
#include "undirected_graph.hpp"
#include "visite.hpp"
#include "lifo.hpp"
#include "dijkstra.hpp"

//findpath

template<typename T>
bool findpath(const undirected_graph<T>& tree, const T& u, const T& v, std::vector<T>& path, std::set<T>& visited) {
	visited.insert(u);
	path.push_back(u);
	if (u == v) {
		return true;
	}
	
	for (const auto& n : tree.neighbours(u)) {
		if (visited.find(n) == visited.end()) { // se n non è stato visitato
			if (findpath(tree, n, v, path, visited)) {
				return true;
			}
		}
	}
	
	path.pop_back();
	return false;
}

//dfs

template<typename T>
std::vector<std::vector<T>> maglie_dfs(const undirected_graph<T>& grafo) {
	std::vector<std::vector<T>> maglie; 
	std::set<T> nodi = grafo.all_nodes();
	T nodo1 = *nodi.begin(); // gli diciamo di prendere il primo nnodo del grafo come nodo di partenza 
	lifo<T> stack;
	undirected_graph<T> tree = graph_visit(grafo,nodo1, stack);
	undirected_graph<T> coalbero = grafo - tree; // calcolo il coalbero
	std::set<undirected_edge<T>> archi_coalbero = coalbero.all_edges();
	
	for (const auto& arco : archi_coalbero) {
		T u = arco.from();
		T v = arco.to();
		
		std::vector<T> path;
		std::set<T> visited;
		
		if (findpath (tree, u, v, path, visited)) {
			path.push_back(u);
			maglie.push_back(path);
		}
	}
	
	return maglie;
}

//de pina

template<typename T>
std::vector<std::vector<T>> de_pina(const undirected_graph<T>& grafo) { // restituisce un vettore di vettori
	
	//creo un vettore di archi
	std::vector<undirected_edge<T>> archi_vector; 
	for (const auto& arco : grafo.all_edges()) {
		archi_vector.push_back(arco);
	}
	
	std::sort(archi_vector.begin(), archi_vector.end()); 
	
	// CALCOLO ALBERO E COALBERO
	std::set<T> nodi = grafo.all_nodes();
	int N = *nodi.rbegin(); 
	
	T u = *nodi.begin(); 
	lifo<T> stack;
	undirected_graph<T> tree = graph_visit(grafo,u, stack);
	undirected_graph<T> coalbero = grafo - tree; // calcolo il coalbero
	
	std::vector<undirected_edge<T>> archi_coalbero;
	for (const auto& arco_c : coalbero.all_edges()) {
		archi_coalbero.push_back(arco_c);
	}
	
	std::vector<std::vector<T>> lista_maglie; 
	
	int m = archi_vector.size(); // numero totale di archi nel grafo |E|
	int k = archi_coalbero.size(); // numero di archi nel coalbero
	
	
	// COSTRUZIONE MATRICE S
	std::vector<std::vector<int>> S;
	for (int j = 0; j < k; j++) { // j è l'indice con cui scorro gli archi del coalbero
		std::vector<int> S_j(m,0); // inizializzo i vettori Sj con gli 0
		for (int i = 0; i < m; i++) { // con i scorro gli archi del grafo
			if ( archi_vector[i] == archi_coalbero[j]) { 
				S_j[i] = 1;
				break;
			}
		}
		
		S.push_back(S_j); // aggiungo il vettore S_j a S 
	}

	
	// CREAZIONE G' GRAFO AUSILIARIO
	
	for (int j = 0; j < k; j++) {
		
		undirected_graph<int> grafo2; 
		
		for (int i = 0; i < m; i++) {
			int u_piu = archi_vector[i].from();
			int u_meno = u_piu + N;
			int v_piu = archi_vector[i].to();
			int v_meno = v_piu + N;
			
			if (S[j][i] == 1) { // arco attivo (presente nel coalbero) 
				grafo2.add_edge(u_piu, v_meno); // colleghiamo u+ e v- (v- = u + N) 
				grafo2.add_edge(u_meno, v_piu); // colleghiamo u- con v+
			} else {
				grafo2.add_edge(u_piu, v_piu); // colleghiamo + con +
				grafo2.add_edge(u_meno, v_meno); // colleghiamo - con -
			}
		}
		
		// TROVIAMO CAMMINO MINIMO MIGLIORE CON DIJKSTRA
		// assegnamo tutti i pesi uguali a 1 perche dobbiamo torvare i cicli minimi, cioe quelli con minor numero di archi, non in base ai pesi
		
		// ASSEGNAZIONE DEI PESI FISSI A 1.0
		// Creiamo la mappa dei pesi per gli archi di grafo2
		std::map<undirected_edge<int>, double> pesi_grafo2;
		for (const auto& arco: grafo2.all_edges()) { 
			pesi_grafo2[arco] = 1.0;
		}
		
		std::vector<int> cammino_scelto; // inizializziamo il miglior cammino trovato finora come vuoto
		double distanza_minima = std::numeric_limits<double>::infinity(); // distanza migliore = infinito

		for (const auto& nodo : nodi) { // scorriamo tutti i nodi reali del ciclo: per ogni nodo cerchiamo il cammino tra v- (v + N) e v+ (v)
			int nodo_sorgente = nodo + N; // v-
			int destinazione = nodo; // v+

			std::map<int, int> pred;
			std::map<int, double> dist;

			dijkstra(grafo2, nodo_sorgente, pesi_grafo2, pred, dist);

			if (dist[destinazione] == std::numeric_limits<double>::infinity()) {
				continue;
			} // se destinazione non è raggiungibile, salta questo nodo e passa al successivo
			
			// ricostruiamo il cammino minimo torvato iterando all'indietro la mappa dei predecessori
			std::vector<int> cammino;
			int corrente = destinazione;

			while (corrente != nodo_sorgente) {
				cammino.push_back(corrente);
				corrente = pred[corrente];
			}
			cammino.push_back(nodo_sorgente); // risalendo la mappa al contrario, otteniamo il cammino da destinazione a sorgente
			std::reverse(cammino.begin(), cammino.end()); // reverse serve per riordinare il cammino nell'ordine giusto: sorgente--> destinazione
			
			// se il cammino appena trovato è più corto del migliore trovato finora, lo aggiorniamo  come cammino migliore
			if (dist[destinazione] < distanza_minima) {
				distanza_minima = dist[destinazione];
				cammino_scelto = cammino;
			}
		} 
		
		// se non è stato trovato nessun cammino valido, salta al passo successivo
		if (cammino_scelto.empty()) {
			continue;
		}
		
		//ABBIAMO TROVATO TUTTI I POSSIBILI CAMMINI DA V- A V+ NEL GRAFO G' E SCELTO QUELLO MIGLIORE (QUELLO PIU CORTO)
		
		// CONVERTO I NODI SDOPPIATI DEL CAMMINO SCELTO IN NODI VERI E LI INSERISCO NEL VETTORE DELLA MAGLIA
		
		std::vector<T> maglia_nodi_veri;
		for (int nodo: cammino_scelto) {
			int nodo_vero;
			if (nodo > N) {
				nodo_vero = nodo - N;
			} else {
				nodo_vero = nodo;
			}
		
			maglia_nodi_veri.push_back(nodo_vero);
		}
		
					
		//VETTORE D'INCIDENZA 
		std::vector<int> C_i (m, 0);
		for (size_t p = 0; p < cammino_scelto.size() -1; p++) {
			
			int u_vero;
			if (cammino_scelto[p] > N) {
				u_vero = cammino_scelto[p] - N;
			} else {
				u_vero = cammino_scelto[p];
			}
			int v_vero;
			if (cammino_scelto[p+1] > N){
				 v_vero = cammino_scelto[p+1] - N;
			} else {
				v_vero = cammino_scelto[p+1];
			}
			
			// creiamo l'arco tra i nodi originali e cerchiamo a quale indice corrispondono 
			undirected_edge<T> arco_originale (u_vero, v_vero); 
			
			
			// cerchiamo in quale posizione si trova quest'arco in archi_vector
			int id = -1; // inizializziamo indice id = -1 
			for (int i = 0; i < m; i++) { // scorriamo gli archi del grafo
				if (archi_vector[i] == arco_originale) { // se lo trovaimo
					id = i; // aggiorniamo id con l'indice dell'arco
					break;
				}
			}
			if (id == -1) { // se non lo troviamo, id resta = -1 e lo saltiamo
				continue;
			}
				
			C_i[id] = !C_i[id]; // inverto il valore booleano 
					
		}
		
		//PASSAGGIO PER OTTENERE MAGLIE INDIPENDENTI
		
		for (int riga_succ = j + 1; riga_succ < k; riga_succ++) {
			// Calcolo il prodotto scalare <C_i, S_j> modificato modulo 2
			int prodscalare = 0;
			for (int i = 0; i < m; i++) {
				prodscalare = (prodscalare + C_i[i] * S[riga_succ][i]) % 2;
			}

			// Se il prodotto scalare è pari a 1 
			if (prodscalare  == 1) {
				// S_j+1 = S_j+1 XOR S_j
				for (int i = 0; i < m; i++) {
					S[riga_succ][i] = S[riga_succ][i] ^ S[j][i];
				}
			}
		}
		
		//SALVIAMO LA MAGLIA TROVATA NELLA LISTA FINALE DELLE MAGLIE
		lista_maglie.push_back(maglia_nodi_veri);
		
		}
	return lista_maglie;
};
